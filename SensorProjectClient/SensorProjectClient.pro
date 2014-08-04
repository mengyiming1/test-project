#-------------------------------------------------
#
# Project created by QtCreator 2014-07-30T14:45:02
#
#-------------------------------------------------

QT       += core
QT       += network
QT       -= gui

TARGET = SensorProjectClient
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    sensorclient.cpp \
    sensordata.cpp \
    xrfsensordata.cpp \
    emssensordata.cpp \
    libssensordata.cpp

HEADERS += \
    sensorclient.h \
    sensordata.h \
    xrfsensordata.h \
    emssensordata.h \
    libssensordata.h
