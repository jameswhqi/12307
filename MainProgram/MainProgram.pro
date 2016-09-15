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
    chargedialoge.cpp \
    infodialog.cpp \
    passworddialog.cpp \
    passdialog.cpp \
    orderdialog.cpp \
    adminwindow.cpp \
    addtraindialog.cpp

HEADERS  += mainwindow.h \
    logindialog.h \
    user.h \
    passenger.h \
    ticketoffice.h \
    train.h \
    ticket.h \
    station.h \
    spot.h \
    chargedialoge.h \
    infodialog.h \
    passworddialog.h \
    passdialog.h \
    orderdialog.h \
    adminwindow.h \
    addtraindialog.h

FORMS    += mainwindow.ui \
    logindialog.ui \
    chargedialoge.ui \
    infodialog.ui \
    passworddialog.ui \
    passdialog.ui \
    orderdialog.ui \
    adminwindow.ui \
    addtraindialog.ui
