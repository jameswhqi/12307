#ifndef TICKET_H
#define TICKET_H
#include "spot.h"
#include "train.h"

//票类
class Ticket
{
public:
    Ticket();
private:
    int index;//对应于数据库中的索引编号
    Passenger &passenger;//乘客
    Train &train;//车次
    Spot spot;//座位/床位
};

#endif // TICKET_H
