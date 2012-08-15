#-------------------------------------------------
#
# Project created by QtCreator 2012-07-30T19:09:19
#
#-------------------------------------------------

QT       += core gui network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Ember-MM-cpp
TEMPLATE = app

#LIBS = -ldl

INCLUDEPATH += deps/boost \
    deps/sqlite3

SOURCES += main.cpp\
        mainwindow.cpp \
    settings.cpp \
    splashscreen.cpp \
    loadingthread.cpp \
    filedownloader.cpp \
    deps/sqlite3/sqlite3.c \
    emptydatabaseinitializer.cpp \
    factory.cpp \
    movie.cpp \
    tvshows.cpp \
    tvseason.cpp \
    tvepisodes.cpp

HEADERS  += mainwindow.h \
    settings.h \
    databasemovie.h \
    splashscreen.h \
    loadingthread.h \
    settingsitem.h \
    filedownloader.h \
    deps/sqlite3/sqlite3.h \
    emptydatabaseinitializer.h \
    factory.h \
    movie.h \
    tvshows.h \
    tvseason.h \
    tvepisodes.h

FORMS    += mainwindow.ui \
    splashscreen.ui

RESOURCES += \
    resources.qrc
