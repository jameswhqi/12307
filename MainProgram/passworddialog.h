#ifndef PASSWORDDIALOG_H
#define PASSWORDDIALOG_H

#include <QDialog>
#include "mainwindow.h"


namespace Ui {
class PasswordDialog;
}

class PasswordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PasswordDialog(MainWindow *parent = 0);
    ~PasswordDialog();

private slots:
    void on_confirm_clicked();

    void on_cancel_clicked();

private:
    Ui::PasswordDialog *ui;
    MainWindow *MW;
};

#endif // PASSWORDDIALOG_H
