#ifndef PASSDIALOG_H
#define PASSDIALOG_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class PassDialog;
}

class PassDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PassDialog(User* new_user = NULL);
    ~PassDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::PassDialog *ui;
    User* user;
};

#endif // PASSDIALOG_H
