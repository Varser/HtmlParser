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


SOURCES += main.cpp\
        mainwindow.cpp \
    htmlparser.cpp \
    objectsthree.cpp \
    htmldownloader.cpp

HEADERS  += mainwindow.h \
    htmlparser.h \
    objectsthree.h \
    htmldownloader.h
