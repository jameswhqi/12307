#include "adminwindow.h"
#include "ui_adminwindow.h"
#include "ticketoffice.h"
#include "station.h"

AdminWindow::AdminWindow(TicketOffice *TO) :
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
}

AdminWindow::~AdminWindow()
{
    delete ui;
}

void AdminWindow::setStations(QList<Station *> &stationList)
{
    QStringList stations;
    stations.append(QString());
    QList<Station *>::const_iterator i;
    for (i = stationList.constBegin(); i != stationList.constEnd(); i++) {
        stations.append((*i)->name());
    }
    ui->origin->addItems(stations);
    ui->destination->addItems(stations);
}
