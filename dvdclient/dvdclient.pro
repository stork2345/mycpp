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
    logwindow.cpp \
    recharge.cpp \
    admin.cpp

HEADERS  += dvdclient.h \
    common.h \
    logwindow.h \
    recharge.h \
    admin.h

FORMS    += dvdclient.ui \
    logwindow.ui \
    recharge.ui \
    admin.ui

LIBS+=-lmysqlclient

OTHER_FILES +=

RESOURCES +=
