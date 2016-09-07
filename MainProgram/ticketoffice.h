#ifndef TICKETOFFICE_H
#define TICKETOFFICE_H
#include <ticket.h>
#include <train.h>
#include <station.h>
#include <QList>

class TicketOffice
{
public:
    TicketOffice();
public slots:
    void searchTrain();//根据用户输入的搜索条件在数据库中搜索车次，存入trainList
private:
    QList<Train &> trainList;//搜索到的车次表
    //QList<Ticket &> ticketList;
    //QList<Station &> stationList;
};


#endif // TICKETOFFICE_H
