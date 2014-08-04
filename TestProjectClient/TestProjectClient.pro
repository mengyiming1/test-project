#-------------------------------------------------
#
# Project created by QtCreator 2014-07-29T12:18:39
#
#-------------------------------------------------

QT       += core
QT       += network
QT       -= gui

TARGET = TestProjectClient
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    sensordata.cpp \
    sensorclient.cpp \
    xrfsensordata.cpp

HEADERS += \
    sensordata.h \
    sensorclient.h \
    xrfsensordata.h
