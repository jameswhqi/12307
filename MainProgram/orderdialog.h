#ifndef ORDERDIALOG_H
#define ORDERDIALOG_H

#include <QDialog>
#include <QString>
#include "user.h"

namespace Ui {
class OrderDialog;
}

class TicketOffice;
class User;

class OrderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OrderDialog(User *new_user, TicketOffice *TO);
    ~OrderDialog();

    void displayTrainInfo(QString info);
    void Show_Passenger();//显示乘客

private slots:
    void on_confirmButton_clicked();

private:
    Ui::OrderDialog *ui;
    User* user;
    TicketOffice *m_TO;
};

#endif // ORDERDIALOG_H
