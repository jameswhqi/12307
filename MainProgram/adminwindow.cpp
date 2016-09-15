#include "adminwindow.h"
#include "ui_adminwindow.h"
#include "ticketoffice.h"
#include "station.h"
#include "train.h"
#include <QCloseEvent>

AdminWindow::AdminWindow(TicketOffice *TO) :
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
    m_TO = TO;
    connect(ui->searchButton, SIGNAL(clicked()), TO, SLOT(adminSearchTrain()));
    connect(ui->modifyButton, SIGNAL(clicked(bool)), TO, SLOT(modifyTrain()));
    connect(ui->addButton, SIGNAL(clicked(bool)), TO, SLOT(addTrain()));
    connect(ui->deleteButton, SIGNAL(clicked(bool)), TO, SLOT(deleteTrain()));

    //设置车次类型和座位类型的下拉列表
    QStringList types;
    types.append(QString());
    types.append("特快");
    types.append("普快");
    types.append("高铁");
    ui->trainType->addItems(types);
    types.clear();
    types.append(QString());
    types.append("硬座");
    types.append("卧铺");
    ui->spotType->addItems(types);
}

AdminWindow::~AdminWindow()
{
    delete ui;
}

QString AdminWindow::origin()
{
    return ui->origin->currentText();
}
QString AdminWindow::destination()
{
    return ui->destination->currentText();
}
QString AdminWindow::number()
{
    return ui->trainNumber->text();
}
int AdminWindow::trainType()
{
    return ui->trainType->currentIndex() - 1;
}
int AdminWindow::spotType()
{
    if (ui->trainType->currentIndex() == 3) {
        return 1;
    } else if (ui->spotType->currentIndex() == 2) {
        return 2;
    } else {
        return ui->spotType->currentIndex() - 1;
    }
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


void AdminWindow::clearTrainInfo()
{
    for (int i = 0; i < ui->trainInfo->rowCount(); i++) {
        for (int j = 0; j < 8; j++) {
            delete ui->trainInfo->item(i,j);
        }
    }
    ui->trainInfo->setRowCount(0);
}

void AdminWindow::showTrainInfo(QList<Train *> *searchResult)
{
    int resultSize = searchResult->size();
    ui->trainInfo->setRowCount(resultSize);
    for (int i = 0; i < resultSize; i++) {
        Train *pointer = searchResult->at(i);
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setText(pointer->number());
        ui->trainInfo->setItem(i, 0, item);
        item = new QTableWidgetItem;
        item->setText(pointer->origin().name());
        ui->trainInfo->setItem(i, 1, item);
        item = new QTableWidgetItem;
        item->setText(pointer->destination().name());
        ui->trainInfo->setItem(i, 2, item);
        item = new QTableWidgetItem;
        item->setText(pointer->departureTime().toString());
        ui->trainInfo->setItem(i, 3, item);
        item = new QTableWidgetItem;
        item->setText(pointer->arrivalTime().toString());
        ui->trainInfo->setItem(i, 4, item);
        item = new QTableWidgetItem;
        item->setText(pointer->duration().toString());
        ui->trainInfo->setItem(i, 5, item);
        QString spotText = "";
        if (pointer->spotType() == Spot::BED) {
            spotText = "卧铺";
        }
        else if (pointer->spotType() == Spot::SEAT){
            spotText = "硬座";
        }
        item = new QTableWidgetItem;
        item->setText(spotText);
        ui->trainInfo->setItem(i, 6, item);
        item = new QTableWidgetItem;
        item->setText(pointer->price().toString(Price::symbolNumber));
        ui->trainInfo->setItem(i, 7, item);
    }
}

QString AdminWindow::currentNumber()
{
    int row = ui->trainInfo->currentRow();
    if (row == -1) {
        return QString();
    }
    return ui->trainInfo->item(row, 0)->text();
}

void AdminWindow::closeEvent(QCloseEvent *event)
{
    m_TO->showLoginDialog();
    event->accept();
}
