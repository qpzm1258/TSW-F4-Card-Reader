#-------------------------------------------------
#
# Project created by QtCreator 2018-05-07T09:27:40
#
#-------------------------------------------------

QT       += core gui printsupport sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MultiCardReader
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp
#        sicardstatus.cpp

HEADERS  += mainwindow.h\
            pathdefine.h\
            version.h
#            sicardstatus.h

FORMS    += mainwindow.ui
#            sicardstatus.ui

TRANSLATIONS =zh_CN.ts
win32:RC_FILE += MultiCardReader_resource.rc

win32: LIBS += -L$$PWD/3rdparty/QCardProgressWidget/ -lQCardProgressWidget

INCLUDEPATH += $$PWD/3rdparty/QCardProgressWidget
DEPENDPATH += $$PWD/3rdparty/QCardProgressWidget
