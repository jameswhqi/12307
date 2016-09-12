#include "passworddialog.h"
#include "ui_passworddialog.h"


PasswordDialog::PasswordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PasswordDialog)
{
    ui->setupUi(this);
}

PasswordDialog::~PasswordDialog()
{
    delete ui;
}

void PasswordDialog::on_confirm_clicked()
{
    int res = parent->user->Update_Password(ui->old->text(),ui->new1->text(),ui->new2->text());
    if(res < 0)
    {
        ui->result->setText("密码错误！");
    }
    else if(res > 0)
    {
        ui->result->setText("两次输入密码不一致！");
    }
    else if(res == 0)
    {
        ui->result->setText("修改成功！");
    }
}

void PasswordDialog::on_cancel_clicked()
{

}
