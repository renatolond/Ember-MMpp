#-------------------------------------------------
#
# Project created by QtCreator 2012-07-30T19:09:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Ember-MM-cpp
TEMPLATE = app

INCLUDEPATH += libs/boost

SOURCES += main.cpp\
        mainwindow.cpp \
    settings.cpp

HEADERS  += mainwindow.h \
    settings.h \
    databasemovie.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
