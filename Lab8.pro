#-------------------------------------------------
#
# Project created by QtCreator 2016-11-19T12:32:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lab8
TEMPLATE = app

DEFINES += QT_NO_OPENGL
LIBS = -L/home/emironenko/ $$[LIBS]
SOURCES += main.cpp\
        painterwindow.cpp \
    triangleitem.cpp

HEADERS  += painterwindow.h \
    triangleitem.h

FORMS    += painterwindow.ui
