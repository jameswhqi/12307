#include "chargedialoge.h"
#include "ui_chargedialoge.h"
#include <QMessageBox>

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
    int money = (int)(ui->input_money->value() * 100);
    if(MW->user->Charge(Price(money)))
    {
        QMessageBox msg;
        msg.setText("充值成功！");
        msg.setDefaultButton(QMessageBox::Ok);
        msg.exec();
        this->accept();
    }
    else
    {
        QMessageBox msg;
        msg.setText("充值失败！");
        msg.setDefaultButton(QMessageBox::Ok);
        msg.exec();
        this->reject();
    }
}

void ChargeDialoge::on_money_no_clicked()
{
    this->reject();
}
