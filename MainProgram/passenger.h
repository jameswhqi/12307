#ifndef PASSENGER_H
#define PASSENGER_H

#include <QString>

class Passenger
{
public:
    //构造函数
    Passenger(QString new_name,QString new_id)
    {
        name = new_name;
        id = new_id;
    }
    ~Passenger(){}//析构函数
    Passenger* newPass(const QString new_name, const QString new_id);//创建新乘客
    void resetPass(QString new_name, const QString new_id);//修改乘客信息
    const QString Name();//返回姓名
    const QString ID();//返回身份证号

private:
    //乘客信息：姓名，身份证号
    QString name;
    QString id;
};

#endif // PASSENGER_H
