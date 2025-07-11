QT       += core gui widgets testlib
CONFIG   += console automoc uic
TEMPLATE = app
TARGET   = tst_mainwindow

INCLUDEPATH += ..

FORMS   += ../mainwindow.ui

SOURCES += \
    test_mainwindow.cpp \
    ../mainwindow.cpp

HEADERS += \
    test_mainwindow.h \
    ../mainwindow.h
