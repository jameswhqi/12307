#include "logindialog.h"
#include "ui_logindialog.h"
#include "ticketoffice.h"
#include <QSqlQuery>

LoginDialog::LoginDialog(TicketOffice *TO) :
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    connect(ui->signInButton, SIGNAL(clicked()), TO, SLOT(signIn()));
    connect(ui->modeSelector, SIGNAL(currentChanged(int)), this, SLOT(toggleHide(int)));
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

bool LoginDialog::mode()
{
    return ui->modeSelector->currentIndex();
}
QString LoginDialog::username()
{
    if (ui->modeSelector->currentIndex()) {
        return ui->username_2->text();
    }
    else {
        return ui->username->text();
    }
}
QString LoginDialog::password()
{
    if (ui->modeSelector->currentIndex()) {
        return ui->password_2->text();
    }
    else {
        return ui->password->text();
    }
}

void LoginDialog::toggleHide(int mode)
{
    if (mode) {
        ui->signUpButton->hide();
    }
    else {
        ui->signUpButton->show();
    }
}

void LoginDialog::on_signUpButton_clicked()
{
    ui->login_stackedWidget->setCurrentIndex(1);
}

void LoginDialog::on_pushButton_2_clicked()
{
    ui->login_stackedWidget->setCurrentIndex(0);
}

void LoginDialog::on_pushButton_clicked()
{
    QString new_username = ui->lineEdit->text();
    QString new_password = ui->lineEdit_2->text();
    QString new_password2 = ui->lineEdit_3->text();


    if(new_password != new_password2)
    {
        ui->register_result->setText("错误，两次密码不一致！");
        return;
    }

    QSqlQuery query;
    query.prepare("insert into users (username,password) values (:username,:password)");
    query.bindValue(":username",new_username);
    query.bindValue(":password",new_password);
    bool res = query.exec();
    if(res)
    {
        ui->register_result->setText("注册成功！");
    }
    else if(!res)
    {
        ui->register_result->setText("用户名重复，注册失败！");
    }
}
