#ifndef ORDER_H
#define ORDER_H
#include <QList>
#include "passenger.h"

class Order
{
public:
    Order();
    void Add_Passenger(const Passenger &new_pass);
    void Delete_Passenger(const int target);

private:
    int index;
    QList<Passenger> pass_list;
};

#endif // ORDER_H
