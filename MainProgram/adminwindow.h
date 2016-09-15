#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>

namespace Ui {
class AdminWindow;
}

class TicketOffice;
class Station;

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminWindow(TicketOffice *TO);
    ~AdminWindow();

    void setStations(QList<Station *> &stationList);//设置车站下拉列表

private:
    Ui::AdminWindow *ui;
};

#endif // ADMINWINDOW_H
