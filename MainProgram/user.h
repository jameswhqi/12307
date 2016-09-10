#ifndef USER_H
#define USER_H
#include <QString>
#include <QList>
#include "passenger.h"
#include "ticketoffice.h"
#include "ticket.h"
#include "order.h"

class User
{
public:
    User();//构造函数，用于登陆
    ~User();//析构函数，用于登出

    //管理核心信息的方法
    void Reset_Password();
    void Reset_Phone();
    void Reset_Email();

    //管理基本信息的方法
    void Reset_Name();
    void Reset_Sex();

    //管理账户余额的方法
    void Charge(double charge_money);//充值
    double Blance();//查看余额

    //管理乘客信息的方法
    void Add_Passenger();//增加一个新乘客
    void Reset_Passenger();//修改一个乘客信息
    void Delete_Passenger();//删除一个乘客

    //管理票务信息的方法
    bool Order_Ticket(TicketOffice &local, int target_index);//向TicketOffice提交订票请求
    const Passenger& Choose_Pass();
    bool Buy_Ticket(TicketOffice &local, int target_index, const Passenger& target);//订票，选人，买票
    void Return_Ticker(TicketOffice &local);//退票

private:
    //账户核心信息：用户名，密码，手机号，电子邮箱
    QString account;
    QString password;
    QString phone;
    QString email;

    //账户基本信息：姓名，性别
    QString name;

    //账户余额
    double balance;


    //账户所管理的乘客信息
    QList<Passenger> pass_list;

    //账户所管理的火车票
    QList<Ticket> ticket_head;

    //账户所管理的临时订票单
    Order temp;
};


#endif // USER_H
