/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_left;
    QWidget *mpv_container;
    QSlider *horizontalSlider;
    QFrame *frame;
    QPushButton *btn1FrameBack;
    QPushButton *btnNSecBack;
    QPushButton *btn_play;
    QPushButton *btnNSecForward;
    QPushButton *btn1FrameForward;
    QPushButton *btnMark;
    QVBoxLayout *verticalLayout_right;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *btn_set_mark;
    QPushButton *btn_del_mark;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(850, 640);
        MainWindow->setMinimumSize(QSize(850, 200));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_left = new QVBoxLayout();
        verticalLayout_left->setSpacing(6);
        verticalLayout_left->setObjectName(QStringLiteral("verticalLayout_left"));
        mpv_container = new QWidget(centralWidget);
        mpv_container->setObjectName(QStringLiteral("mpv_container"));

        verticalLayout_left->addWidget(mpv_container);

        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        verticalLayout_left->addWidget(horizontalSlider);

        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setMaximumSize(QSize(16777215, 40));
        frame->setStyleSheet(QStringLiteral("background-color: rgb(211, 215, 207);"));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Raised);
        btn1FrameBack = new QPushButton(frame);
        btn1FrameBack->setObjectName(QStringLiteral("btn1FrameBack"));
        btn1FrameBack->setGeometry(QRect(10, 8, 80, 25));
        btnNSecBack = new QPushButton(frame);
        btnNSecBack->setObjectName(QStringLiteral("btnNSecBack"));
        btnNSecBack->setGeometry(QRect(110, 8, 80, 25));
        btn_play = new QPushButton(frame);
        btn_play->setObjectName(QStringLiteral("btn_play"));
        btn_play->setGeometry(QRect(210, 8, 80, 25));
        btnNSecForward = new QPushButton(frame);
        btnNSecForward->setObjectName(QStringLiteral("btnNSecForward"));
        btnNSecForward->setGeometry(QRect(310, 8, 80, 25));
        btn1FrameForward = new QPushButton(frame);
        btn1FrameForward->setObjectName(QStringLiteral("btn1FrameForward"));
        btn1FrameForward->setGeometry(QRect(410, 8, 80, 25));
        btnMark = new QPushButton(frame);
        btnMark->setObjectName(QStringLiteral("btnMark"));
        btnMark->setGeometry(QRect(550, 8, 80, 25));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        btnMark->setFont(font);

        verticalLayout_left->addWidget(frame);


        horizontalLayout_2->addLayout(verticalLayout_left);

        verticalLayout_right = new QVBoxLayout();
        verticalLayout_right->setSpacing(6);
        verticalLayout_right->setObjectName(QStringLiteral("verticalLayout_right"));
        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setMaximumSize(QSize(120, 16777215));

        verticalLayout_right->addWidget(listWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        btn_set_mark = new QPushButton(centralWidget);
        btn_set_mark->setObjectName(QStringLiteral("btn_set_mark"));
        btn_set_mark->setMaximumSize(QSize(50, 16777215));

        horizontalLayout->addWidget(btn_set_mark);

        btn_del_mark = new QPushButton(centralWidget);
        btn_del_mark->setObjectName(QStringLiteral("btn_del_mark"));
        btn_del_mark->setMaximumSize(QSize(50, 16777215));

        horizontalLayout->addWidget(btn_del_mark);


        verticalLayout_right->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout_right);

        horizontalLayout_2->setStretch(0, 1);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 850, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0));
#ifndef QT_NO_TOOLTIP
        actionOpen->setToolTip(QApplication::translate("MainWindow", "Open a file", 0));
#endif // QT_NO_TOOLTIP
        actionOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0));
        actionSave->setText(QApplication::translate("MainWindow", "Save", 0));
        actionSave->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0));
        btn1FrameBack->setText(QApplication::translate("MainWindow", "-1 frame", 0));
        btnNSecBack->setText(QApplication::translate("MainWindow", "-3 sec", 0));
        btn_play->setText(QApplication::translate("MainWindow", "Pause", 0));
        btnNSecForward->setText(QApplication::translate("MainWindow", "+3 sec", 0));
        btn1FrameForward->setText(QApplication::translate("MainWindow", "+1 frame", 0));
        btnMark->setText(QApplication::translate("MainWindow", "Mark", 0));
        btn_set_mark->setText(QApplication::translate("MainWindow", "Set", 0));
        btn_del_mark->setText(QApplication::translate("MainWindow", "Del", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
