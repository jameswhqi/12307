#include "chargedialoge.h"
#include "ui_chargedialoge.h"

ChargeDialoge::ChargeDialoge(MainWindow *parent) :
    ui(new Ui::ChargeDialoge)
{
    ui->setupUi(this);
    MW = parent;
}

ChargeDialoge::~ChargeDialoge()
{
    delete ui;
}

void ChargeDialoge::on_money_yes_clicked()
{
    int money = (int)ui->input_money->text().toDouble()*100;
    if(MW->user->Charge(Price(money)))
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
    this->reject();
}
