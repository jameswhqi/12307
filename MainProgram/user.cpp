#include <cassert>
#include <QString>
#include <QVariant>
#include <QSqlQuery>
#include <QDebug>

#include "user.h"
#include "ticketoffice.h"


//构造函数，用于登陆
User::User(TicketOffice *new_local, int new_idx)
{
    idx = new_idx;
    local = new_local;
    Query_Password();
    Query_Info();
    Query_Blance();
    Query_User();

}

//析构函数，用于登出
//User::~User()
//{

//}

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
int User::Update_Password(QString old_password, QString new_password, QString new_password2)
{
    if(old_password != password)    return -1;
    if(new_password != new_password2) return 1;
    else
    {
        password = new_password;

        QSqlQuery query;
        query.prepare("update users set password=:password where idx=:idx");
        query.bindValue(":idx",idx);
        query.bindValue(":password",new_password);
        query.exec();

        return 0;
    }
}

//从数据库获取密码
void User::Query_Password()
{
    QSqlQuery query;
    query.prepare("select password from users where idx=:idx");
    query.bindValue(":idx",idx);
    query.exec();
    query.next();//默认指向结果集的上一个，要next()

    password = query.value(0).toString();
}

//向数据库更新基本信息
bool User::Update_Info(QString new_name,int new_sex, QString new_phone,QString new_email)
{
    name = new_name;
    sex = gender(new_sex);//enum有问题
    phone = new_phone;
    email = new_email;

    QSqlQuery query;
    query.prepare("update users set name=:name,sex=:sex,phone=:phone,email=:email where idx=:idx");
    query.bindValue(":idx",idx);
    query.bindValue(":name",name);
    query.bindValue(":sex",sex);
    query.bindValue(":phone",phone);
    query.bindValue(":email",email);
    query.exec();

    return true;
}

//从数据库获取基本信息
void User::Query_Info()
{
    QSqlQuery query;
    query.prepare("select username,name,sex,phone,email from users where idx=:idx");
    query.bindValue(":idx",idx);
    query.exec();
    query.next();

    username = query.value(0).toString();
    name = query.value(1).toString();
    sex = gender(query.value(2).toInt());
    phone = query.value(3).toString();
    email = query.value(4).toString();
}

//返回姓名
QString User::Name()
{
    return name;
}

//返回性别
User::gender User::Sex()
{
    return sex;
}

//返回联系方式
QString User::Phone()
{
    return phone;
}

//返回电子邮箱
QString User::Email()
{
    return email;
}

//充值
bool User::Charge(Price &charge_money)
{
    if(!charge_money.isValid())
    {
        return false;
    }
    else
    {
        balance += charge_money;

        QSqlQuery query;
        query.prepare("update users set balance=:balance where idx=:idx");
        query.bindValue(":idx",idx);
        query.bindValue(":balance",balance.dataFen());
        query.exec();

        return true;
    }
}

//扣费
void User::Pay(const Price &money)
{
    balance -= money;

    QSqlQuery query;
    query.prepare("update users set balance=:balance where idx=:idx");
    query.bindValue(":idx",idx);
    query.bindValue(":balance",balance.dataFen());
    query.exec();
}

//从数据库获取余额
void User::Query_Blance()
{
    QSqlQuery query;
    query.prepare("select balance from users where idx=:idx");
    query.bindValue(":idx",idx);
    query.exec();
    query.next();

    balance.setDataFen(query.value(0).toInt());
}

//返回余额
Price* User::Balance()
{
    return &balance;
}

bool User::Check_Balance()//余额检查
{
    if(balance.dataFen()>=current_train->price().dataFen())
    {
        return true;
    }
    else
    {
        return false;
    }
}

//从数据库获取乘客信息
void User::Query_User()
{
    /*for(int i = 0;i<pass_list.size();i++)
    {
        delete[] pass_list[i];
    }*/
    pass_list.clear();

    QSqlQuery query;
    query.prepare("select name,id from passengers where user=:user");
    query.bindValue(":user",idx);
    query.exec();
    while(query.next())
    {
        Passenger* newPass = Passenger::newPass(query.value(0).toString(),query.value(1).toString());
        pass_list.append(newPass);
    }
}

//增加一个新乘客
void User::Add_Passenger(const QString new_name, const QString new_id)
{
    Passenger* newPass = Passenger::newPass(new_name,new_id);
    pass_list.append(newPass);

    QSqlQuery query;
    query.prepare("insert into passengers (user,name,id) values (:user,:name,:id)");
    query.bindValue(":user",idx);
    query.bindValue(":name",new_name);
    query.bindValue(":id",new_id);
    query.exec();
}

//删除一个乘客
void User::Delete_Passenger(int ref)
{   
    QSqlQuery query;
    query.prepare("delete from passengers where user = :user and id = :id");
    query.bindValue(":user",idx);
    query.bindValue(":id",pass_list[ref]->ID());
    query.exec();

    //delete[] pass_list[ref];//要先释放这个空间
    pass_list.removeAt(ref);
}

//返回管理的乘客数
int User::Pass_Size()
{
    return pass_list.size();
}

//返回指定的姓名
const QString User::Pass_Name(int ref)
{
    return pass_list[ref]->Name();
}

//返回指定的身份证号
const QString User::Pass_ID(int ref)
{
    return pass_list[ref]->ID();
}

//乘客查重
bool User::Check_Duplicate(Passenger* tar_pass)
{
    QSqlQuery query;
    query.prepare("select passenger from tickets where train =:train and date=:date");
    query.bindValue(":train",current_train->index());
    query.bindValue(":date",current_train->date().toString());
    query.exec();

    while(query.next())
    {
        QSqlQuery id;
        id.prepare("select id from passengers where idx=:idx");
        id.bindValue(":idx",query.value(0).toInt());
        id.exec();
        id.first();

        if(id.value(0).toString() == tar_pass->ID())
        {
            return false;
        }
    }
    return true;
}

//买票，0－购票成功，1－余额不足，2-购票重复，其他－未知错误
int User::Buy_Ticket(int pass_ref)
{
    Passenger* tar_pass = pass_list[pass_ref];

    if(Check_Balance() == false)
    {
        return 1;
    }
    else if(Check_Duplicate(tar_pass) == false)
    {
        return 2;
    }
    else
    {
        Ticket* res = local->createTicket(tar_pass);
        Pay(res->train().price());
        ticket_list.append(res);

        return 0;
    }
}

bool User::Return_Ticker(int ticket_ref)//退票
{
    Ticket* tar_ticket = ticket_list[ticket_ref];
    local->deleteTicket(tar_ticket);
    tar_ticket->spot().cancel();
    Charge(tar_ticket->train().price());
    int tar_idx = tar_ticket->index();

    QSqlQuery query;
    query.prepare("delete from tickets where idx=:idx");
    query.bindValue(":idx",tar_idx);
    query.exec();

    delete[] ticket_list[ticket_ref];
    ticket_list.erase(ticket_ref);
}

//从数据库以及TO获取购票信息
void User::Query_Ticket()
{
    /*for(int i = 0;i<ticket_list.size();i++)
    {
        delete[] ticket_list[i];
    } */
    ticket_list.clear();//首先清空ticket_list中的数据，并释放空间

    //从tickets表中找出:
    //ticket_index
    //passenger_index
    //train_index
    //date
    //spot_index
    QSqlQuery query;
    query.prepare("select idx,passenger,train,date,spot from tickets where user=:user");
    query.bindValue(":user",idx);
    query.exec();

    for(query.first();query.isValid();query.next())
    {
        //利用passenger_index从passengers表中读出姓名，身份证号
        QSqlQuery query_name_id;
        query_name_id.prepare("select name,id from passengers where idx=:pass");
        query_name_id.bindValue(":pass",query.value(1).toInt());
        query_name_id.exec();
        query_name_id.first();//注意，要指向第一个

        //从数据库的结果集中构建乘客
        Passenger* new_pass = new Passenger(query_name_id.value(0).toString(),query_name_id.value(1).toString());
        //从数据库的结果集中构建车次，TicketOffice的接口函数是Train* trainForTicket(int idx,QString date)
        Train* new_train = local->trainForTicket(query.value(2).toInt(),query.value(3).toString());
        //从数据库的结果集中构建座位
        Spot* new_spot = &new_train->spot(query.value(4).toInt());
        //用index、乘客、车次、座位构建车票
        Ticket* new_ticket = new Ticket(query.value(0).toInt(),*new_pass,*new_train,*new_spot);
        //将构建的车票存入ticket_list
        ticket_list.append(new_ticket);
    }
}

//返回购票张数
int User::Ticket_Size()
{
    return ticket_list.size();
}

Ticket* User::ticket(int ref)
{
    return ticket_list[ref];
}

//设置当前订票的火车
void User::Set_Current_Train(Train* new_current_train)
{
    current_train = new_current_train;
}

