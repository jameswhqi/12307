#include "addtraindialog.h"
#include "ui_addtraindialog.h"
#include "ticketoffice.h"
#include "station.h"
#include "train.h"

AddTrainDialog::AddTrainDialog(TicketOffice *TO, bool modify) :
    ui(new Ui::AddTrainDialog)
{
    ui->setupUi(this);

    connect(ui->confirmButton, SIGNAL(clicked(bool)), TO, SLOT(confirmAdMoTrain()));

    //设置车次类型和座位类型的下拉列表
    QStringList types;
    types.append("特快");
    types.append("普快");
    types.append("高铁");
    ui->trainType->addItems(types);
    types.clear();
    types.append(QString());
    types.append("硬座");
    types.append("卧铺");
    ui->spotType->addItems(types);

    if (modify) {
        ui->trainNumber->setEnabled(false);
        ui->trainType->setEnabled(false);
        ui->spotType->setEnabled(false);
    }
}

AddTrainDialog::~AddTrainDialog()
{
    delete ui;
}

void AddTrainDialog::setStations(QList<Station *> &stationList)
{
    QStringList stations;
    QList<Station *>::const_iterator i;
    for (i = stationList.constBegin(); i != stationList.constEnd(); i++) {
        stations.append((*i)->name());
    }
    ui->origin->addItems(stations);
    ui->destination->addItems(stations);
}

void AddTrainDialog::displayTrainInfo(Train *currentTrain)
{
    ui->trainNumber->setText(currentTrain->number());
    ui->origin->setCurrentText(currentTrain->origin().name());
    ui->destination->setCurrentText(currentTrain->destination().name());
    ui->departureHour->setValue(currentTrain->departureTime().hour());
    ui->departureMinute->setValue(currentTrain->departureTime().minute());
    ui->durationHour->setValue(currentTrain->duration().hour());
    ui->durationMinute->setValue(currentTrain->duration().minute());
    ui->trainType->setCurrentIndex(currentTrain->trainType());
    if (currentTrain->spotType() == Spot::SEAT) {
        ui->spotType->setCurrentIndex(1);
    }
    else if (currentTrain->spotType() == Spot::BED) {
        ui->spotType->setCurrentIndex(2);
    }
    ui->price->setValue(currentTrain->price().toReal());
}

QString AddTrainDialog::number()
{
    return ui->trainNumber->text().toUpper();
}

QString AddTrainDialog::origin()
{
    return ui->origin->currentText();
}

QString AddTrainDialog::destination()
{
    return ui->destination->currentText();
}

int AddTrainDialog::trainType()
{
    return ui->trainType->currentIndex();
}

int AddTrainDialog::spotType()
{
    if (ui->trainType->currentIndex() == 2) {
        return 1;
    } else if (ui->spotType->currentIndex() == 2) {
        return 2;
    } else {
        return 0;
    }
}

Time AddTrainDialog::departureTime()
{
    return Time(ui->departureHour->value(), ui->departureMinute->value());
}

Time AddTrainDialog::duration()
{
    return Time(ui->durationHour->value(), ui->durationMinute->value());
}

Price AddTrainDialog::price()
{
    return Price((int)(ui->price->value() * 100));
}
