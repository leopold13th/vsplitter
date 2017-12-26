#include <clocale>
#include <sstream>
#include <stdexcept>
#include <fstream>

#include <QFileDialog>
#include <QMessageBox>

#if QT_VERSION >= 0x050000
#include <QJsonDocument>
#endif

#include <mpv/qthelper.hpp>
#include "utils.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

static void wakeup(void *ctx)
{
    // This callback is invoked from any mpv thread (but possibly also
    // recursively from a thread that is calling the mpv API). Just notify
    // the Qt GUI thread to wake up (so that it can process events with
    // mpv_wait_event()), and return as quickly as possible.
    MainWindow *mainwindow = (MainWindow *)ctx;
    emit mainwindow->mpv_events();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    mpv = mpv_create();
    if (!mpv)
        throw std::runtime_error("can't create mpv instance");

    ui->setupUi(this);

    ui->mpv_container->setAttribute(Qt::WA_DontCreateNativeAncestors);
    ui->mpv_container->setAttribute(Qt::WA_NativeWindow);
    // If you have a HWND, use: int64_t wid = (intptr_t)hwnd;
    int64_t wid = ui->mpv_container->winId();
    mpv_set_option(mpv, "wid", MPV_FORMAT_INT64, &wid);

    // Enable default bindings, because we're lazy. Normally, a player using
    // mpv as backend would implement its own key bindings.
    mpv_set_option_string(mpv, "input-default-bindings", "yes");

    // Enable keyboard input on the X11 window. For the messy details, see
    // --input-vo-keyboard on the manpage.
    mpv_set_option_string(mpv, "input-vo-keyboard", "yes");

    // Let us receive property change events with MPV_EVENT_PROPERTY_CHANGE if
    // this property changes.
    mpv_observe_property(mpv, 0, "time-pos", MPV_FORMAT_DOUBLE);
    mpv_observe_property(mpv, 0, "track-list", MPV_FORMAT_NODE);
    mpv_observe_property(mpv, 0, "chapter-list", MPV_FORMAT_NODE);

    // Request log messages with level "info" or higher.
    // They are received as MPV_EVENT_LOG_MESSAGE.
    mpv_request_log_messages(mpv, "info");

    // From this point on, the wakeup function will be called. The callback
    // can come from any thread, so we use the QueuedConnection mechanism to
    // relay the wakeup in a thread-safe way.
    connect(this, &MainWindow::mpv_events, this, &MainWindow::mpv_on_events,
            Qt::QueuedConnection);
    mpv_set_wakeup_callback(mpv, wakeup, this);

    if (mpv_initialize(mpv) < 0)
        throw std::runtime_error("mpv failed to initialize");

//    if (mpv) {
//        const char *args[] = {"loadfile", "test.mkv", NULL};
//        mpv_command_async(mpv, 0, args);
//    }

    marks << 8.16 << 35.0 << 85.23;
    for (int i = 0; i < marks.size(); ++i)
    {
        std::stringstream ss;
        ss << marks.at(i);
        new QListWidgetItem(secs2time(marks.at(i)), ui->listWidget);
    }
}

MainWindow::~MainWindow()
{
    if (mpv)
        mpv_terminate_destroy(mpv);
    delete ui;
}

void MainWindow::handle_mpv_event(mpv_event *event)
{
    switch (event->event_id) {
    case MPV_EVENT_PROPERTY_CHANGE: {
        mpv_event_property *prop = (mpv_event_property *)event->data;
        if (strcmp(prop->name, "time-pos") == 0) {
            if (prop->format == MPV_FORMAT_DOUBLE) {
                pos = *(double *)prop->data;
                std::stringstream ss;
                ss << "At: " << pos;
                statusBar()->showMessage(QString::fromStdString(ss.str()));
            } else if (prop->format == MPV_FORMAT_NONE) {
                // The property is unavailable, which probably means playback was stopped.
                statusBar()->showMessage("");
            }
        } else if (strcmp(prop->name, "chapter-list") == 0 ||
                   strcmp(prop->name, "track-list") == 0)
        {
            // Dump the properties as JSON for demo purposes.
#if QT_VERSION >= 0x050000
            if (prop->format == MPV_FORMAT_NODE) {
                QVariant v = mpv::qt::node_to_variant((mpv_node *)prop->data);
                // Abuse JSON support for easily printing the mpv_node contents.
                QJsonDocument d = QJsonDocument::fromVariant(v);
                // append_log("Change property " + QString(prop->name) + ":\n");
                // append_log(d.toJson().data());
            }
#endif
        }
        break;
    }
    case MPV_EVENT_VIDEO_RECONFIG: {
        // Retrieve the new video size.
        int64_t w, h;
        if (mpv_get_property(mpv, "dwidth", MPV_FORMAT_INT64, &w) >= 0 &&
            mpv_get_property(mpv, "dheight", MPV_FORMAT_INT64, &h) >= 0 &&
            w > 0 && h > 0)
        {
            // Note that the MPV_EVENT_VIDEO_RECONFIG event doesn't necessarily
            // imply a resize, and you should check yourself if the video
            // dimensions really changed.
            // mpv itself will scale/letter box the video to the container size
            // if the video doesn't fit.
            std::stringstream ss;
            ss << "Reconfig: " << w << " " << h;
            statusBar()->showMessage(QString::fromStdString(ss.str()));
        }
        break;
    }
    case MPV_EVENT_LOG_MESSAGE: {
        struct mpv_event_log_message *msg = (struct mpv_event_log_message *)event->data;
        std::stringstream ss;
        ss << "[" << msg->prefix << "] " << msg->level << ": " << msg->text;
        // append_log(QString::fromStdString(ss.str()));
        break;
    }
    case MPV_EVENT_SHUTDOWN: {
        mpv_terminate_destroy(mpv);
        mpv = NULL;
        break;
    }
    default: ;
        // Ignore uninteresting or unknown events.
    }
}

// This slot is invoked by wakeup() (through the mpv_events signal).
void MainWindow::mpv_on_events()
{
    // Process all events, until the event queue is empty.
    while (mpv) {
        mpv_event *event = mpv_wait_event(mpv, 0);
        if (event->event_id == MPV_EVENT_NONE)
            break;
        handle_mpv_event(event);
    }
}

// void MainWindow::on_file_open()
void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open file");
    if (mpv) {
        const QByteArray c_filename = filename.toUtf8();
        v_filename = c_filename.data();
        const char *args[] = {"loadfile", c_filename.data(), NULL};
        mpv_command_async(mpv, 0, args);
    }
}

void MainWindow::on_actionSave_triggered()
{
    // QString v_filename_path = v_filename.section('/', 0, -2);
    QString v_filename_only = v_filename.section('/', -1, -1);
    QString v_filename_nosuffix = v_filename_only.section('.', 0, -2);
    QString suffix = v_filename_only.section('.', -1, -1);

    std::stringstream ss;
    ss << "#!/bin/bash\n\n";
    double prev = 0;
    for (int i = 0; i < marks.size(); ++i)
    {
        ss << "ffmpeg -i " << v_filename.toUtf8().constData() << " -ss " << prev << " -t " << marks.at(i)-prev
           << " -c copy " << v_filename_nosuffix.toUtf8().constData() << "_part" << i+1 << "." << suffix.toUtf8().constData() << "\n";
        prev = marks.at(i);
    }
    ss << "ffmpeg -i " << v_filename.toUtf8().constData() << " -ss " << prev << " -t 100000000 -c copy "
       << v_filename_nosuffix.toUtf8().constData() << "_part" << marks.size()+1 << "." << suffix.toUtf8().constData() << "\n";

    std::ofstream fout;
    fout.open((v_filename+".sh").toUtf8().constData(), std::ios::out);
    fout << ss.str();
    fout.close();
    // QMessageBox::warning(this, v_filename_only, QString::fromStdString(ss.str()));
}

void MainWindow::on_btn_play_clicked()
{
    if (strcmp(mpv_get_property_string(mpv, "pause"), "yes") == 0)
    {
        mpv_set_property_string(mpv, "pause", "no");
        ui->btn_play->setText("Pause");
    }
    else
    {
        mpv_set_property_string(mpv, "pause", "yes");
        ui->btn_play->setText("Play");
    }
}

void MainWindow::on_btn1FrameBack_clicked()
{
    const char *args[] = {"frame-back-step", NULL};
    mpv_command_async(mpv, 0, args);
}

void MainWindow::on_btn1FrameForward_clicked()
{
    const char *args[] = {"frame-step", NULL};
    mpv_command_async(mpv, 0, args);
}

void MainWindow::on_btnNSecBack_clicked()
{
    const char *args[] = {"seek", "-3", NULL};
    mpv_command_async(mpv, 0, args);
}

void MainWindow::on_btnNSecForward_clicked()
{
    const char *args[] = {"seek", "3", NULL};
    mpv_command_async(mpv, 0, args);
}

void MainWindow::on_btnMark_clicked()
{
    double pos;
    mpv_get_property(mpv, "time-pos", MPV_FORMAT_DOUBLE, &pos);

    marks << pos; //QString::fromStdString(ss.str());
    std::sort(marks.begin(), marks.end());

    ui->listWidget->clear();
    for (int i = 0; i < marks.size(); ++i)
    {
        std::stringstream ss;
        ss << marks.at(i);
        new QListWidgetItem(secs2time(marks.at(i)), ui->listWidget);
    }
}

