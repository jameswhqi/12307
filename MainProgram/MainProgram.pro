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
    admin.cpp \
    chargedialoge.cpp \
    infodialog.cpp \
    passworddialog.cpp \
    passdialog.cpp

HEADERS  += mainwindow.h \
    logindialog.h \
    user.h \
    passenger.h \
    ticketoffice.h \
    train.h \
    ticket.h \
    station.h \
    spot.h \
    admin.h \
    chargedialoge.h \
    infodialog.h \
    passworddialog.h \
    passdialog.h

FORMS    += mainwindow.ui \
    logindialog.ui \
    chargedialoge.ui \
    infodialog.ui \
    passworddialog.ui \
    passdialog.ui

DISTFILES += \
    uml.qmodel
