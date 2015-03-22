#-------------------------------------------------
#
# Project created by QtCreator 2015-03-19T13:20:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dvdclient
TEMPLATE = app


SOURCES += main.cpp\
        dvdclient.cpp \
    common.cpp \
    logwindow.cpp

HEADERS  += dvdclient.h \
    common.h \
    logwindow.h

FORMS    += dvdclient.ui \
    logwindow.ui

LIBS+=-lmysqlclient
