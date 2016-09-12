#ifndef PASSDIALOG_H
#define PASSDIALOG_H

#include <QDialog>
#include "user.h"

namespace Ui {
class PassDialog;
}

class PassDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PassDialog(QWidget *parent = 0,User* new_user = NULL);
    ~PassDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::PassDialog *ui;
    User* user;
};

#endif // PASSDIALOG_H
