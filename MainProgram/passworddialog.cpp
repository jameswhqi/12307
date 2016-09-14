#include "passworddialog.h"
#include "ui_passworddialog.h"

PasswordDialog::PasswordDialog(MainWindow *parent) :
    ui(new Ui::PasswordDialog)
{
    ui->setupUi(this);
    MW = parent;
}

PasswordDialog::~PasswordDialog()
{
    delete ui;
}

void PasswordDialog::on_confirm_clicked()
{
    int res = MW->user->Update_Password(ui->old->text(),ui->new1->text(),ui->new2->text());
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
    this->reject();
}
