#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H
#include <QDialog>
#include <QString>
#include "ticketoffice.h"

namespace Ui {
class LoginDialog;
}


class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(TicketOffice *TO, QWidget *parent = 0);
    ~LoginDialog();

    bool mode();//返回当前模式(0:乘客 1:管理员)
    QString username();//返回当前填入的用户名
    QString password();//返回当前填入的密码

public slots:
    void toggleHide(int mode);//当modeSelector切换到“管理员”时隐藏“注册”键

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
