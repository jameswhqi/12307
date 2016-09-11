QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 12307
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logindialog.cpp \
    user.cpp \
    passenger.cpp \
    ticketoffice.cpp \
    train.cpp \
    ticket.cpp \
    station.cpp \
    spot.cpp \
    admin.cpp

HEADERS  += mainwindow.h \
    logindialog.h \
    user.h \
    passenger.h \
    ticketoffice.h \
    train.h \
    ticket.h \
    station.h \
    spot.h \
    admin.h

FORMS    += mainwindow.ui \
    logindialog.ui

RESOURCES +=

DISTFILES += \
    uml.qmodel
