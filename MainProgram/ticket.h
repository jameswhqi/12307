#ifndef TICKET_H
#define TICKET_H
#include "train.h"
#include "passenger.h"

//票类
class Ticket
{
public:
    Ticket(int index, Passenger &passenger, Train &train, Spot &spot);

    Passenger &passenger();//返回乘客引用
    Train &train();//返回车次引用
    Spot &spot();//返回位子引用
private:
    int m_index;//对应于数据库中的索引编号
    Passenger *m_passenger;//乘客
    Train *m_train;//车次
    Spot *m_spot;//座位/床位
};

#endif // TICKET_H
