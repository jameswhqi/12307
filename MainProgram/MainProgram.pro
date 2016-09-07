QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 12307
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logindialog.cpp \
    user.cpp \
    order.cpp \
    passenger.cpp

HEADERS  += mainwindow.h \
    logindialog.h \
    user.h \
    order.h \
    passenger.h

FORMS    += mainwindow.ui \
    logindialog.ui

RESOURCES +=

DISTFILES += \
    README.md \
    .gitignore \
    ui_flowchart.graffle \
    ui_flowchart.jpg
