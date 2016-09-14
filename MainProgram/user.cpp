#include <cassert>
#include <QString>
#include <QVariant>
#include <QSqlQuery>

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
bool User::Charge(Price charge_money)
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
/*
//买票，给TicketOffice一个QList<Passenger*>*,一个balance,返回给我Ticket*或NULL
bool User::Buy_Ticket(TicketOffice &local)
{
    Ticket* res = local->Order_Ticket(&pass_to_buy,*Balance());
    pass_to_buy.clear();
    if(res == NULL) return false;
    else
    {
        Ticket *res;

        ticket_list.append(res);
    }
}
*/

//增加一个新的买票乘客
void User::Add_Pass_To_But(const int ref)
{
    if(pass_to_buy.indexOf(pass_list[ref]) == -1)//不重复插入
    {
        pass_to_buy.append(pass_list[ref]);
    }
}

//删除一个买票乘客
void User::Delete_Pass_To_Buy(const int ref)
{
    pass_to_buy.removeAt(ref);
}

//清空pass_to_buy列表
void User::Clear_Pass_To_Buy()
{
    pass_to_buy.clear();
}

//从数据库以及TO获取购票信息
void User::Query_Ticket()
{
    for(int i = 0;i<ticket_list.size();i++)
    {
        delete[] ticket_list[i];
    }
    ticket_list.clear();//首先清空ticket_list中的数据，并释放空间

    //从tickets表中找出对应的index(每张ticket对应的标示码)
    QSqlQuery query_idx;
    query_idx.prepare("select idx from tickets where user=:user");
    query_idx.bindValue(":user",idx);
    query_idx.exec();

    //从tickets表中找出passenger的index(每个乘客的标示码)
    QSqlQuery query_pass;
    query_pass.prepare("select passenger from tickets where user=:user");
    query_pass.bindValue(":user",idx);
    query_pass.exec();

    //利用乘客的index从passengers表中读出姓名，身份证号
    QSqlQuery query_name_id;
    while(query_pass.next())
    {
        query_name_id.prepare("select name,id from passengers where idx=:idx");
        query_name_id.bindValue(":idx",query_pass.value(0).toInt());
        query_name_id.exec();
    }

    //从tickets表中读出每张票的车次的index和乘车日期
    QSqlQuery query_train_date;
    query_train_date.prepare("select idx,date from tickets where=:user");
    query_train_date.bindValue(":user",idx);
    query_train_date.exec();

    //从tickets表中读出座位的index
    QSqlQuery query_spot;
    query_spot.prepare("select spot from tickets where user=:user");
    query_spot.bindValue(":user",idx);
    query_spot.exec();

    while(query_idx.next())
    {
        query_name_id.next();
        query_train_date.next();
        query_spot.next();

        //利用座位spot的index从trains表中获取列车类型和座位信息
        QSqlQuery query_spot_type;
        query_spot_type.prepare("select traintype from trains where idx=:idx");
        query_spot_type.bindValue(":idx",query_train_date.value(0).toInt());
        query_spot_type.exec();
        query_spot_type.next();//注意，要指向下一个

        //从数据库的结果集中构建乘客
        Passenger* new_pass = new Passenger(query_name_id.value(0).toString(),query_name_id.value(1).toString());
        //从数据库的结果集中构建车次，TicketOffice的接口函数是Train* trainForTicket(int idx,QString date)
        Train* new_train = locoal->trainForTicket(query_train_date.value(0).toInt(),query_train_date.value(1).toString());
        //从数据库的结果集中构建座位
        Spot* new_spot = new Spot(query_spot.value(0).toInt(), query_spot_type.value(0).toInt(), true);
        //用index、乘客、车次、座位构建车票
        Ticket* new_ticket = new Ticket(query_idx.value(0).toInt((),new_pass,new_train,new_spot);
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

//退票
//void User::Return_Ticket(TicketOffice &local)
//{

//}
