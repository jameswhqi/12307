#include "mainwindow.h"
#include "ticketoffice.h"
#include <QApplication>
#include <QSqlDatabase>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QCoreApplication::applicationDirPath() + "/12307.db");
    db.open();
    TicketOffice TO;
    return app.exec();
}
