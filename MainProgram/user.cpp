#include <cassert>
#include <QString>
#include <QVariant>
#include <QSqlQuery>
#include "user.h"

//构造函数，用于登陆
User::User(QString new_account)
{
    account = new_account;
    Query_Password();
    Query_Info();
    Query_Blance();
}

//析构函数，用于登出
User::~User()
{

}

//返回用户名
QString User::Accout()
{
    return accout;
}

//重置密码
bool User::Reset_Password(QString old_password, QString new_password)
{
    if(old_password != password)    return false;
    else
    {
        password = new_password;

        QSqlQuery query;
        query.prepare("update user set password=:password where account=:account");
        query.bindValue(":account",account);
        query.bindValue(":password",new_password);
        query.exec();

        return true;
    }
}

//从数据库获取密码
void User::Query_Password()
{
    QSqlQuery query;
    query.prepare("select password from user where account=:account");
    query.bindValue(":account",account);
    query.exec();
    query.next();//默认指向结果集的上一个，要next()

    password = query.value(0).toString;
}

//向数据库更新基本信息
bool User::Update_Info(QString new_name,int new_sex,QString new_id,QString new_phone,QString new_email)
{
    name = new_name;
    sex = new_sex;//enum有问题
    id = new_id;
    phone = new_phone;
    email = new_email;

    QSqlQuery query;
    query.prepare("update user set name=:name,sex=:sex,id=:id,phone=:phone,email=:email where account=:account");
    query.bindValue(":account",account);
    query.bindValue(":name",name);
    query.bindValue(":sex",sex;
    query.bindValue(":id",id);
    query.bindValue(":phone",phone);
    query.bindValue(":email",email);
    query.exec();

    return true;
}

//从数据库获取基本信息
void User::UserQuery_Info()
{
    QSqlQuery query;
    query.prepare("select * from user where account=:account");
    query.bindValue(":account",account);
    query.exec();
    query.next();

    name = query.value(2).toString;
    sex = query.value(3);//enum sex型，不太对
    id = query.value(4).toString;
    phone = query.value(5).toString;
    email = query.value(6).toString;
}

//返回姓名
QString User::Name()
{
    return name;
}

//返回性别
sex User::Sex()
{
    return sex;
}

//返回身份证号
QString User::ID()
{
    return id;
}

//返回联系方式
QString User::Phone()
{
    return phone;
}

//返回电子邮箱
QString User::email()
{
    return email;
}

//充值//price类绝对要改
bool User::Charge(double charge_money)
{
    assert(charge_money >= 0);
    balance += charge_money;

    QSqlQuery query;
    query.prepare("update user set balance=:balance where account=:account");
    query.bindValue(":account",account);
    query.bindValue(":balance",balance);
    query.exec();

    return true;
}

//从数据库获取余额
void User::Query_Blance()
{
    QSqlQuery query;
    query.prepare("select balance from user where account=:account");
    query.bindValue(":account",account);
    query.exec();
    query.next();

    balance = query.value(7).toDouble;//price一定要改
}

//查看余额
double User::Balance()
{
    return balance;
}

//增加一个新乘客
void User::Add_Passenger()
{

}

//修改一个乘客信息
void User::Reset_Passenger()
{

}

//删除一个乘客
void User::Delete_Passenger()
{

}

//买票：包括生成订单，填写订单（填写乘客信息），支付
bool User::Buy_Ticket(TicketOffice &local, int target_index)
{

}

//退票
void User::Return_Ticket(TicketOffice &local)
{

}
