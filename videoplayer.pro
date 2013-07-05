#-------------------------------------------------
#
# Project created by QtCreator 2013-07-04T21:34:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = videoplayer
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    qmpwidget.cpp \
    mainwindow.cpp \
    menubar.cpp \
    controlbar.cpp \
    picturepushbutton.cpp

HEADERS  += widget.h \
    qmpwidget.h \
    mainwindow.h \
    menubar.h \
    controlbar.h \
    picturepushbutton.h \
    config.h
