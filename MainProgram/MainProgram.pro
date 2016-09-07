QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 12307
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logindialog.cpp \
<<<<<<< HEAD
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
=======
    user.cpp

HEADERS  += mainwindow.h \
    logindialog.h \
    user.h
>>>>>>> 77dd8a374de44f26803d92bbaa58cb855dbcbe56

FORMS    += mainwindow.ui \
    logindialog.ui

RESOURCES +=
<<<<<<< HEAD
=======

DISTFILES += \
    README.md \
    .gitignore \
    ui_flowchart.graffle \
    ui_flowchart.jpg
>>>>>>> 77dd8a374de44f26803d92bbaa58cb855dbcbe56
