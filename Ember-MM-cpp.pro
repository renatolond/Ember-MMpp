#-------------------------------------------------
#
# Project created by QtCreator 2012-07-30T19:09:19
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Ember-MM-cpp
TEMPLATE = app

INCLUDEPATH += deps/boost \
    deps/sqlite3

SOURCES += main.cpp\
        mainwindow.cpp \
    settings.cpp \
    splashscreen.cpp \
    loadingthread.cpp \
    filedownloader.cpp \
    deps/sqlite3/sqlite3.c

HEADERS  += mainwindow.h \
    settings.h \
    databasemovie.h \
    splashscreen.h \
    loadingthread.h \
    settingsitem.h \
    filedownloader.h \
    deps/sqlite3/sqlite3.h

FORMS    += mainwindow.ui \
    splashscreen.ui

RESOURCES += \
    resources.qrc
