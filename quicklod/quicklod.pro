#-------------------------------------------------
#
# Project created by QtCreator 2013-12-22T15:41:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# The application version
VERSION_APP = 1.00
# Define the preprocessor macro to get the application version in our application.
DEFINES += APP_VERSION=\\\"$$VERSION_APP\\\"

TARGET = quicklod
TEMPLATE = app


SOURCES += main.cpp\
        gui.cpp

HEADERS  += gui.h

FORMS    += gui.ui

QMAKE_CXXFLAGS_RELEASE += -O3 -ffast-math -ftracer
