#include "user.h"

//构造函数，用于登陆
User::User()
{

}

//析构函数，用于登出
User::~User()
{

}

 //重置密码
 void User::Reset_Password()
 {


 }

 //重置手机号
 void User::Reset_Phone()
 {

 }

 //重置邮箱
 void User::Reset_Email()
 {

 }

 //重置姓名
 void User::Reset_Name()
 {

 }

 //重置性别
 void User::Reset_Sex()
 {

 }

 //充值
 void User::Charge(double charge_money)
 {

 }

 //查看余额
 double User::Balance()
 {
     return balance;
 }

 //增加一个新乘客
void Add_Passenger()
{

}

//修改一个乘客信息
void Reset_Passenger()
{

}

//删除一个乘客
void Delete_Passenger()
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
