#ifndef TICKETOFFICE_H
#define TICKETOFFICE_H
#include <QString>

class TicketOffice
{
public:
    TicketOffice();
};

//火车类型
enum TrainType {
    TSeat, TBed, KSeat, KBed, G
};

//车次类
class Train {
private:
    int m_index;//
    QString m_number;
    TrainType m_type;
};

#endif // TICKETOFFICE_H
