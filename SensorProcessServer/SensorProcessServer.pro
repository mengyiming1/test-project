#-------------------------------------------------
#
# Project created by QtCreator 2014-07-26T21:38:16
#
#-------------------------------------------------

QT       += core
QT       += network
QT       -= gui

TARGET = SensorProcessServer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    testsensorserver.cpp \
    sensordataparser.cpp

HEADERS += \
    testsensorserver.h \
    sensordataparser.h
