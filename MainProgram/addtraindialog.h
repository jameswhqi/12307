#ifndef ADDTRAINDIALOG_H
#define ADDTRAINDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class AddTrainDialog;
}

class Time;
class Price;
class Station;
class Train;
class TicketOffice;

class AddTrainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddTrainDialog(TicketOffice *TO, bool modify);
    ~AddTrainDialog();

    void setStations(QList<Station *> &stationList);//设置车站下拉列表
    void displayTrainInfo(Train *currentTrain);

    QString number();
    QString origin();
    QString destination();
    int trainType();
    int spotType();
    Time departureTime();
    Time duration();
    Price price();

private:
    Ui::AddTrainDialog *ui;
};

#endif // ADDTRAINDIALOG_H
