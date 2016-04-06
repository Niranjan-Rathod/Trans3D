#-------------------------------------------------
#
# Project created by QtCreator 2016-03-07T04:14:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Graphics_mini_project
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    computation.cpp \
    matrix.cpp \
    threed_point.cpp \
    point3d.cpp

HEADERS  += mainwindow.h \
    computation.h \
    matrix.h \
    threed_point.h \
    point3d.h

FORMS    += mainwindow.ui
