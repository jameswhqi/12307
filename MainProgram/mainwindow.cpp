#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "user.h"

User* user;

MainWindow::MainWindow(bool mode, TicketOffice *TO)
    : ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->searchButton, SIGNAL(clicked()), TO, SLOT(searchTrain()));

    //删掉对user或admin没用的widget
    if (mode) {
        delete ui->orderButton;
        delete ui->bal_pb;
        delete ui->his_pb;
        delete ui->info_pb;
        delete ui->pass_pb;
        delete ui->history_stk;
        delete ui->money_stk;
        delete ui->pass_stk;
    }
    else {
        delete ui->modifyButton;
        delete ui->addButton;
        delete ui->deleteButton;
    }

    //把日期选择框设成系统日期
    ui->dateEdit->setDate(QDate::currentDate());

    //设置车次类型和座位类型的下拉列表
    QStringList types;
    types.append(QString());
    types.append("特快");
    types.append("普快");
    types.append("高铁");
    ui->trainType->addItems(types);
    types.clear();
    types.append(QString());
    types.append("硬座");
    types.append("卧铺");
    ui->spotType->addItems(types);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::origin()
{
    return ui->origin->currentText();
}
QString MainWindow::destination()
{
    return ui->destination->currentText();
}
QDate MainWindow::date()
{
    return ui->dateEdit->date();
}
QString MainWindow::number()
{
    return ui->trainNumber->text();
}
int MainWindow::trainType()
{
    return ui->trainType->currentIndex() - 1;
}
int MainWindow::spotType()
{
    if (ui->trainType->currentIndex() == 3) {
        return 1;
    }
    else if (ui->spotType->currentIndex() == 2) {
        return 2;
    }
    else {
        return ui->spotType->currentIndex() - 1;
    }
}

void MainWindow::setStations(QList<Station *> &stationList)
{
    QStringList stations;
    stations.append(QString());
    QList<Station *>::const_iterator i;
    for (i = stationList.constBegin(); i != stationList.constEnd(); i++) {
        stations.append((*i)->name());
    }
    ui->origin->addItems(stations);
    ui->destination->addItems(stations);
}

void MainWindow::clearTrainInfo()
{

}

void MainWindow::showTrainInfo(QList<Train *> *searchResult)
{
    int resultSize = searchResult->size();
    ui->trainInfo->setRowCount(resultSize);
    for (int i = 0; i < resultSize; i++) {

    }
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
