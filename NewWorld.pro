#-------------------------------------------------
#
# Project created by QtCreator 2017-11-17T10:16:46
#
#-------------------------------------------------

QT       += core gui
QT       += sql
CONFIG += console
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NewWorld
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    connexionwindow.cpp

HEADERS  += mainwindow.h \
    connexionwindow.h

FORMS    += mainwindow.ui \
    connexionwindow.ui
