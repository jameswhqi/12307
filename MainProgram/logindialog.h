#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H
#include <QDialog>
#include <QString>

class TicketOffice;

namespace Ui {
class LoginDialog;
}


class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(TicketOffice *TO);
    ~LoginDialog();

    bool mode();//返回当前模式(0:乘客 1:管理员)
    QString username();//返回当前填入的用户名
    QString password();//返回当前填入的密码

public slots:
    void toggleHide(int mode);//当modeSelector切换到“管理员”时隐藏“注册”键

private slots:
    void on_signUpButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
