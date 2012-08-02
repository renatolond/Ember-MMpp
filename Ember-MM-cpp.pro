#-------------------------------------------------
#
# Project created by QtCreator 2012-07-30T19:09:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Ember-MM-cpp
TEMPLATE = app

INCLUDEPATH += deps/boost

SOURCES += main.cpp\
        mainwindow.cpp \
    settings.cpp \
    splashscreen.cpp \
    loadingthread.cpp

HEADERS  += mainwindow.h \
    settings.h \
    databasemovie.h \
    splashscreen.h \
    loadingthread.h

FORMS    += mainwindow.ui \
    splashscreen.ui

RESOURCES += \
    resources.qrc
