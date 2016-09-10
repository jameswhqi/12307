#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "user.h"

User* user;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_train_btm_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_user_btm_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_info_pb_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
}

void MainWindow::on_pass_pb_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}

void MainWindow::on_his_pb_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(2);
}

void MainWindow::on_bal_pb_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(3);
    ui->money_dis_lab->setText(user->balance().toString().sprintf("%.2lf"));// 有问题，user全局变量？
}

void MainWindow::on_money_query_btn_clicked()
{
    user->Query_Blance();
    ui->money_dis_lab->setText(user->balance().toString().sprintf("%.2lf"));// 有问题，user全局变量？
}
