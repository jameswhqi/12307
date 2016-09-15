#include "passworddialog.h"
#include "ui_passworddialog.h"
#include <QMessageBox>

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
        QMessageBox msg;
        msg.setText("密码错误！");
        msg.setDefaultButton(QMessageBox::Ok);
        msg.exec();
    }
    else if(res > 0)
    {
        QMessageBox msg;
        msg.setText("两次输入密码不一致！");
        msg.setDefaultButton(QMessageBox::Ok);
        msg.exec();
    }
    else if(res == 0)
    {
        QMessageBox msg;
        msg.setText("修改成功！");
        msg.setDefaultButton(QMessageBox::Ok);
        msg.exec();
        this->accept();
    }
}

void PasswordDialog::on_cancel_clicked()
{
    this->reject();
}
