#-------------------------------------------------
#
# Project created by QtCreator 2016-06-03T17:28:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SerialControl
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    button.cpp \
    serial.cpp \
    frmmessagebox.cpp \
    iconhelper.cpp

HEADERS  += mainwindow.h \
    serial.h \
    myhelper.h \
    frmmessagebox.h \
    iconhelper.h

FORMS    += mainwindow.ui \
    frmmessagebox.ui
