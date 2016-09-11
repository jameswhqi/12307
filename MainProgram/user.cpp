#include <cassert>
#include <QString>
#include <QVariant>
#include <QSqlQuery>
#inlcude "train.h"
#include "user.h"

//构造函数，用于登陆
User::User(int new_idx)
{
    idx = new_idx;
    Query_Password();
    Query_Info();
    Query_Blance();
}

//析构函数，用于登出
User::~User()
{

}

//返回索引
int User::index()
{
    return idx;
}

//返回用户名
QString User::Username()
{
    return username;
}

//重置密码
int User::Reset_Password(QString old_password, QString new_password, QString new_password2)
{
    if(old_password != password)    return -1;
    if(new_password != new_password2) return 1;
    else
    {
        password = new_password;

        QSqlQuery query;
        query.prepare("update user set password=:password where idx=:idx");
        query.bindValue(":idx",account);
        query.bindValue(":password",new_password);
        query.exec();

        return 0;
    }
}

//从数据库获取密码
void User::Query_Password()
{
    QSqlQuery query;
    query.prepare("select password from user where idx=:idx");
    query.bindValue(":idx",idx);
    query.exec();
    query.next();//默认指向结果集的上一个，要next()

    password = query.value(0).toString;
}

//向数据库更新基本信息
bool User::Update_Info(QString new_name,int new_sex, QString new_phone,QString new_email)
{
    name = new_name;
    sex = new_sex;//enum有问题
    phone = new_phone;
    email = new_email;

    QSqlQuery query;
    query.prepare("update user set name=:name,sex=:sex,phone=:phone,email=:email where idx=:idx");
    query.bindValue(":name",name);
    query.bindValue(":sex",sex;
    query.bindValue(":phone",phone);
    query.bindValue(":email",email);
    query.exec();

    return true;
}

//从数据库获取基本信息
void User::UserQuery_Info()
{
    QSqlQuery query;
    query.prepare("select * from user where idx=:idx");
    query.bindValue(":idx",idx);
    query.exec();
    query.next();

    name = query.value(3).toString;
    sex = query.value(4);
    phone = query.value(5).toString;
    email = query.value(6).toString;
}

//返回姓名
QString User::Name()
{
    return name;
}

//返回性别
gender User::Sex()
{
    return sex;
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

//充值
bool User::Charge(const Price& charge_money)
{
    if(!charge_money.isValid());
    {
        return false;
    }
    else
    {
        balance ＝ balance + charge_money;

        QSqlQuery query;
        query.prepare("update user set balance=:balance where idx=:idx");
        query.bindValue(":idx",idx);
        query.bindValue(":balance",balance.dataFen());
        query.exec();

        return true;
    }
}

//从数据库获取余额
void User::Query_Blance()
{
    QSqlQuery query;
    query.prepare("select balance from user where idx=:idx");
    query.bindValue(":idx",idx);
    query.exec();
    query.next();

    balance.setDataFen(query.value(0));
}
//返回余额
Price* User::Balance()
{
    return &balance;
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
//bool User::Buy_Ticket(TicketOffice &local, int target_index)
//{

//}

//退票
//void User::Return_Ticket(TicketOffice &local)
//{

//}
