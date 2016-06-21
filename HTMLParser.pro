#-------------------------------------------------
#
# Project created by QtCreator 2016-06-20T13:56:10
#
#-------------------------------------------------

QT       += core gui
QT      += network

QMAKE_CXXFLAGS = -std=c++11
LIBS += -pthread

CONFIG += qt thread debug

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HTMLParser
TEMPLATE = app


SOURCES +=\
    ui/basewidget.cpp \
    ui/entitledwidget.cpp \
    ui/main.cpp \
    ui/mainwindow.cpp \
    ui/numwidget.cpp \
    ui/processdata.cpp \
    ui/textwidget.cpp \
    ui/urltable.cpp \
    core/htmldownloader.cpp \
    core/htmlparser.cpp \
    core/objectsthree.cpp

HEADERS  += \
    ui/basewidget.h \
    ui/entitledwidget.h \
    ui/mainwindow.h \
    ui/numwidget.h \
    ui/processdata.h \
    ui/textwidget.h \
    ui/urltable.h \
    core/htmldownloader.h \
    core/htmlparser.h \
    core/objectsthree.h
