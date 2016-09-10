#ifndef USER_H
#define USER_H
#include <QString>
#include <QList>
#include "passenger.h"
#inclede "ticketoffice.h"
#include "ticket.h"

enum sex{男,女};

class User
{
public:
    User();//构造函数，用于登陆与刷新全部信息
    ~User();//析构函数，用于登出

     //管理核心信息的方法：
     QString Accout();//返回用户名
     bool Update_Password(QString old_password, QString new_password);//向数据库更新密码
     void Query_Password();//从数据库获取密码

     //管理基本信息的方法
     bool Update_Info(QString new_name,int new_sex,QString new_id,QString new_phone,QString new_email);//向数据库更新基本信息
     void Query_Info();//从数据库获取基本信息
     QString Name();//返回姓名
     sex Sex();//返回性别
     QString ID();//返回身份证号
     QString Phone();//返回联系方式
     QString Email();//返回电子邮箱

     //管理账户余额的方法
     bool Charge(double charge_money);//充值
     void Query_Blance();//从数据库获取余额
     Price balance();//返回余额

    //管理乘客信息的方法
    void Add_Passenger();//增加一个新乘客
    void Reset_Passenger();//修改一个乘客信息
    void Delete_Passenger();//删除一个乘客

    //管理票务信息的方法
    bool Buy_Ticket(TicketOffice &local, int target_index);//买票：包括订票，选人，买票，支付
    void Return_Ticker(TicketOffice &local);//退票

private:

    //账户核心信息：用户名，密码
    QString account;
    QString password;

    //账户基本信息：姓名，性别,身份证号，手机号，电子邮箱
    QString name;
    enum sex sex;
    QString id;
    QString phone;
    QString email;

    //账户余额
    Price balance;

    //账户所管理的乘客信息
    QList<Passenger*> pass_list;

    //账户所管理的火车票
    QList<Ticket*> ticket_list;
};


#endif // USER_H
