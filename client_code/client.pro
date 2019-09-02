#-------------------------------------------------
#
# Project created by QtCreator 2019-08-25T16:12:18
#
#-------------------------------------------------

QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client
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
        widget.cpp \
    tinystr.cpp \
    tinyxml.cpp \
    tinyxmlerror.cpp \
    tinyxmlparser.cpp \
    choice.cpp \
    chat_room.cpp \
    socket_com.cpp \
    mythread.cpp \
    msgemiter.cpp

HEADERS += \
        widget.h \
    tinystr.h \
    tinyxml.h \
    choice.h \
    chat_room.h \
    socket_com.h \
    mythread.h \
    msgemiter.h

FORMS += \
        widget.ui \
    choice.ui \
    chat_room.ui
