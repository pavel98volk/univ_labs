#-------------------------------------------------
#
# Project created by QtCreator 2017-03-16T09:39:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Editor
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    mygl.cpp \
    Figures/Ico.cpp \
    Figures/shape.cpp \
    Figures/cone.cpp \
    Figures/cylinder.cpp

HEADERS  += mainwindow.h \
    mygl.h \
    Figures/Ico.h \
    Figures/vertex.h \
    Figures/shape.h \
    Figures/cone.h \
    Figures/cylinder.h

FORMS    += mainwindow.ui

LIBS+= -lOpengl32

