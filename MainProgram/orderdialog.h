#ifndef ORDERDIALOG_H
#define ORDERDIALOG_H

#include <QDialog>
#include <QString>
#include "user.h"

namespace Ui {
class OrderDialog;
}

class User;

class OrderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OrderDialog(User *new_user = NULL);
    ~OrderDialog();

    void displayTrainInfo(QString info);
    void Show_Passenger();//显示乘客

private:
    Ui::OrderDialog *ui;
    User* user;
};

#endif // ORDERDIALOG_H
