#include "mainwindow.h"
#include "ticketoffice.h"
#include <QApplication>
#include <QSqlDatabase>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/Volumes/Adam/AdamGit/build-12307-Desktop_Qt_5_7_0_clang_64bit-Debug/12307.db");
    db.open();
    TicketOffice TO;
    return app.exec();
}
