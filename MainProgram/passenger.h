#ifndef PASSENGER_H
#define PASSENGER_H

#include <QString>

class Passenger
{
public:
    //构造函数，用于创建新乘客
    Passenger(QString new_name,QString new_id)
    {
        name = new_name;
        id = new_id;
    }
    ~Passenger(){}//析构函数，用于删除乘客

private:
    //乘客信息：姓名，身份证号
    QString name;
    QString id;
};

#endif // PASSENGER_H
