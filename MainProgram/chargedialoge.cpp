#include "chargedialoge.h"
#include "ui_chargedialoge.h"
#include "user.h"

ChargeDialoge::ChargeDialoge(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChargeDialoge)
{
    ui->setupUi(this);
}

ChargeDialoge::~ChargeDialoge()
{
    delete ui;
}

void ChargeDialoge::on_money_yes_clicked()
{
    if(parent->user->Charge(ui->input_money->text()))
    {
        ui->charge_result->setText(" 充值成功！");
    }
    else
    {
        ui->charge_result->setText("充值失败！");
    }
}

void ChargeDialoge::on_money_no_clicked()
{

}
