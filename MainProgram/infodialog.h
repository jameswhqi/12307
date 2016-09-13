#ifndef INFODIALOG_H
#define INFODIALOG_H
#include "mainwindow.h"
#include <QDialog>

namespace Ui {
class InfoDialog;
}

class InfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InfoDialog(MainWindow *parent = 0);
    ~InfoDialog();

private slots:
    void on_confirm_clicked();

    //void on_cancel_clicked();

private:
    Ui::InfoDialog *ui;

    MainWindow *MW;
};

#endif // INFODIALOG_H
