#-------------------------------------------------
#
# Project created by QtCreator 2014-12-26T12:21:24
#
#-------------------------------------------------

QT  += core gui
QT  += websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ClientClassique
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tetromino.cpp \
    animation.cpp \
    clientwebsocket.cpp \
    fifopieces.cpp

HEADERS  += mainwindow.h \
    tetromino.h \
    headergloabal.h \
    animation.h \
    clientwebsocket.h \
    fifopieces.h

FORMS    += mainwindow.ui
