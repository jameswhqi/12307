QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 12307
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logindialog.cpp \
    user.cpp \
    order.cpp \
    passenger.cpp \
    ticketoffice.cpp \
    train.cpp \
    ticket.cpp \
    spot.cpp \
    station.cpp

HEADERS  += mainwindow.h \
    logindialog.h \
    user.h \
    order.h \
    passenger.h \
    ticketoffice.h \
    train.h \
    ticket.h \
    spot.h \
    station.h

FORMS    += mainwindow.ui \
    logindialog.ui

RESOURCES +=
