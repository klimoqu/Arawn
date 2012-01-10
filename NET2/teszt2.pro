#-------------------------------------------------
#
# Project created by QtCreator 2011-12-30T21:05:03
#
#-------------------------------------------------

QT       += core

QT       += network

QT       -= gui

TARGET = teszt
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    teszt.cpp \
    Server.cpp \
    SenderThread.cpp \
    ListenThread.cpp \
    connection.cpp \
    command.cpp \
    clientthread.cpp \
    client.cpp

HEADERS += \
    teszt.h \
    client.h \
    Server.h \
    SenderThread.h \
    ListenThread.h \
    connection.h \
    command.hpp \
    clientthread.h \
    abstractNET.h