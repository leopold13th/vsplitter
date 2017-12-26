#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <mpv/client.h>

namespace Ui {
class MainWindow;
}

class QTextEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void mpv_on_events();

    void on_actionOpen_triggered();
    void on_btn_play_clicked();
    void on_btn1FrameBack_clicked();
    void on_btn1FrameForward_clicked();
    void on_btnNSecBack_clicked();
    void on_btnNSecForward_clicked();
    void on_btnMark_clicked();

    void on_actionSave_triggered();

signals:
    void mpv_events();

private:
    Ui::MainWindow *ui;

    mpv_handle *mpv;
    QString v_filename;
    QList<double> marks;
    double pos;
    // QTextEdit *log;

    void append_log(const QString &text);

    void create_player();
    void handle_mpv_event(mpv_event *event);
};

#endif // MAINWINDOW_H
