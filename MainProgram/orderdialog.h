#ifndef ORDERDIALOG_H
#define ORDERDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class OrderDialog;
}

class User;

class OrderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OrderDialog(User *user);
    ~OrderDialog();

    void displayTrainInfo(QString info);

private:
    Ui::OrderDialog *ui;
};

#endif // ORDERDIALOG_H
