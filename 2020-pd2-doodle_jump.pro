#-------------------------------------------------
#
# Project created by QtCreator 2017-04-20T19:17:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 2020-pd2-doodle_jump
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    bullet.cpp \
    platform_base.cpp \
    platform.cpp

HEADERS  += mainwindow.h \
    bullet.h \
    platform_base.h \
    platform.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc
