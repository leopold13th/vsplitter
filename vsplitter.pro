#-------------------------------------------------
#
# Project created by QtCreator 2017-12-20T17:26:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = vsplitter
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


# QT_CONFIG -= no-pkg-config
CONFIG += link_pkgconfig c++11 debug
PKGCONFIG += mpv


SOURCES += \
        main.cpp \
        mainwindow.cpp \
        utils.cpp

HEADERS += \
        mainwindow.h \
        utils.h \
        build_number.h

FORMS += \
        mainwindow.ui


#BUILDNO = $$(../vsplitter/build_number.sh)
#DEFINES += BUILD=$${BUILDNO}
build_nr.commands = ../vsplitter/build_number.sh
build_nr.depends = FORCE
QMAKE_EXTRA_TARGETS += build_nr
PRE_TARGETDEPS += build_nr
