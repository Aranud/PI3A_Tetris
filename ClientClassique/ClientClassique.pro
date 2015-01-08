#-------------------------------------------------
#
# Project created by QtCreator 2014-12-26T12:21:24
#
#-------------------------------------------------

QT  += core gui
QT  += network
QT  += websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ClientClassique
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    piecegetter.cpp \
    tetromino.cpp \
    animation.cpp

HEADERS  += mainwindow.h \
    piecegetter.h \
    tetromino.h \
    headergloabal.h \
    animation.h

FORMS    += mainwindow.ui
