QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 12307
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logindialog.cpp \
    ticketoffice.cpp \
    train.cpp \
    ticket.cpp \
    spot.cpp

HEADERS  += mainwindow.h \
    logindialog.h \
    ticketoffice.h \
    train.h \
    ticket.h \
    spot.h

FORMS    += mainwindow.ui \
    logindialog.ui

RESOURCES +=
