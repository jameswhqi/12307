#ifndef USER_H
#define USER_H
#include <QString>
#include <QList>
#include "ticket.h"

class TicketOffice;
class User
{
public:
    enum gender{男,女};

    User(TicketOffice* new_local = NULL, int new_idx = -1);//构造函数，用于登陆与刷新全部信息
    //~User();//析构函数，用于登出

    //管理核心信息的方法：
    int index();//返回索引
    QString Username();//返回用户名
    int Update_Password(QString old_password, QString new_password, QString new_password2);//向数据库更新密码
    void Query_Password();//从数据库获取密码

    //管理基本信息的方法
    bool Update_Info(QString new_name,int new_sex, QString new_phone,QString new_email);//向数据库更新基本信息
    void Query_Info();//从数据库获取基本信息
    QString Name();//返回姓名
    gender Sex();//返回性别
    QString Phone();//返回联系方式
    QString Email();//返回电子邮箱

    //管理账户余额的方法
    bool Charge(Price charge_money);//充值
    void Query_Blance();//从数据库获取余额
    Price* Balance();//返回余额

    //管理乘客信息的方法
    void Add_Passenger(const QString new_name, const QString new_id);//增加一个新乘客
    void Delete_Passenger(const int ref);//删除一个乘客
    void Query_User();//从数据库获取乘客信息
    int Pass_Size();//返回管理的乘客数
    const QString Pass_Name(int ref);//返回指定的姓名
    const QString Pass_ID(int ref);//返回指定的身份证号

    //管理票务信息的方法
    //bool Buy_Ticket(TicketOffice &local);//买票：包括订票，选人，买票，支付
    //void Return_Ticker(TicketOffice &local);//退票
    int Ticket_Size();//返回购票张数
    void Add_Pass_To_But(const int ref);
    void Delete_Pass_To_Buy(const int ref);
    void Clear_Pass_To_Buy();
    void Query_Ticket();//从TO和数据库中更新ticket表，复杂，放在TO中为宜，因为不涉及批量操作
    Ticket* ticket(int ref);

private:
    //存储构造该user的TicketOffice的指针，用于买票
    TicketOffice* local;

    //账户核心信息：数据库中的索引编号，用户名，密码
    int idx;
    QString username;
    QString password;

    //账户基本信息：姓名，性别,手机号，电子邮箱
    QString name;
    gender sex;
    QString phone;
    QString email;

    //账户余额
    Price balance;

    //账户所管理的乘客信息
    QList<Passenger*> pass_list;

    //某笔订单订票的乘客信息
    QList<Passenger*> pass_to_buy;

    //账户所管理的火车票
    QList<Ticket*> ticket_list;
};


#endif // USER_H
