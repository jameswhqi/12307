#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <user.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0,User *newuser = NULL);
    ~MainWindow();
    User *user;

private slots:
    void on_train_btm_clicked();

    void on_user_btm_clicked();

    void on_info_pb_clicked();

    void on_pass_pb_clicked();

    void on_his_pb_clicked();

    void on_bal_pb_clicked();

    void on_money_query_btn_clicked();

    void on_money_update_btn_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
