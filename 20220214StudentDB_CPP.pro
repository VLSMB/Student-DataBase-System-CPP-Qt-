#-------------------------------------------------
#
# Project created by QtCreator 2022-05-14T21:04:46
#
#-------------------------------------------------

QT       += core gui
QT +=sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 20220214StudentDB_CPP
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


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    database.cpp \
    maingui.cpp \
    userwindow.cpp \
    baseinfo/resultwindow.cpp \
    baseinfo/studentwindow.cpp \
    search/resultinfowindow.cpp \
    search/studentinfowindow.cpp \
    settings/examkindswindow.cpp \
    settings/gradewindow.cpp \
    settings/subjectwindow.cpp \
    settings/classeswindow.cpp

HEADERS += \
        mainwindow.h \
    database.h \
    maingui.h \
    userwindow.h \
    baseinfo/resultwindow.h \
    baseinfo/studentwindow.h \
    search/resultinfowindow.h \
    search/studentinfowindow.h \
    settings/examkindswindow.h \
    settings/gradewindow.h \
    settings/subjectwindow.h \
    settings/classeswindow.h

FORMS += \
        main.ui \
    MainGui.ui \
    userwindow.ui \
    baseinfo/resultwindow.ui \
    baseinfo/studentwindow.ui \
    search/resultinfowindow.ui \
    search/studentinfowindow.ui \
    settings/examkindswindow.ui \
    settings/gradewindow.ui \
    settings/subjectwindow.ui \
    settings/classeswindow.ui

RESOURCES += \
    rc.qrc
