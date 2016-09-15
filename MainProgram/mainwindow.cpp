#include "chargedialoge.h"
#include "passworddialog.h"
#include "infodialog.h"
#include "passdialog.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "ticketoffice.h"
#include <QCloseEvent>

MainWindow::MainWindow(TicketOffice *TO, User *newuser)
    : ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    user = newuser;

    m_TO = TO;
    connect(ui->searchButton, SIGNAL(clicked()), TO, SLOT(searchTrain()));
    connect(ui->orderButton, SIGNAL(clicked()), TO, SLOT(order()));

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
    delete user;
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
    } else if (ui->spotType->currentIndex() == 2) {
        return 2;
    } else {
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
    for (int i = 0; i < ui->trainInfo->rowCount(); i++) {
        for (int j = 0; j < 8; j++) {
            delete ui->trainInfo->item(i,j);
        }
    }
    ui->trainInfo->setRowCount(0);
}

void MainWindow::showTrainInfo(QList<Train *> *searchResult)
{
    int resultSize = searchResult->size();
    ui->trainInfo->setRowCount(resultSize);
    for (int i = 0; i < resultSize; i++) {
        Train *pointer = searchResult->at(i);
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setText(pointer->number());
        ui->trainInfo->setItem(i, 0, item);
        item = new QTableWidgetItem;
        item->setText(pointer->origin().name());
        ui->trainInfo->setItem(i, 1, item);
        item = new QTableWidgetItem;
        item->setText(pointer->destination().name());
        ui->trainInfo->setItem(i, 2, item);
        item = new QTableWidgetItem;
        item->setText(pointer->departureTime().toString());
        ui->trainInfo->setItem(i, 3, item);
        item = new QTableWidgetItem;
        item->setText(pointer->arrivalTime().toString());
        ui->trainInfo->setItem(i, 4, item);
        item = new QTableWidgetItem;
        item->setText(pointer->duration().toString());
        ui->trainInfo->setItem(i, 5, item);
        item = new QTableWidgetItem;
        item->setText(QString::number(pointer->vacantCount()));
        ui->trainInfo->setItem(i, 6, item);
        item = new QTableWidgetItem;
        item->setText(pointer->price().toString(Price::symbolNumber));
        ui->trainInfo->setItem(i, 7, item);
    }
}

QString MainWindow::currentNumber()
{
    int row = ui->trainInfo->currentRow();
    if (row == -1) {
        return QString();
    }
    return ui->trainInfo->item(row, 0)->text();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    m_TO->showLoginDialog();
    event->accept();
}



void MainWindow::on_train_btm_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_user_btm_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

    int pass_size = user->Pass_Size();
    ui->passinfo->setRowCount(pass_size);
    ui->passinfo->setColumnCount(2);

    for(int i = 0;i<pass_size;i++)
    {
        ui->passinfo->setItem(i,0,new QTableWidgetItem(user->Pass_Name(i)));
        ui->passinfo->setItem(i,1,new QTableWidgetItem(user->Pass_ID(i)));
    }
    ui->passinfo->show();
    on_info_query_btn_clicked();
}

void MainWindow::on_info_pb_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);

    on_info_query_btn_clicked();
}

void MainWindow::on_pass_pb_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
    ui->passinfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->passinfo->setSelectionBehavior(QAbstractItemView::SelectRows);

    on_refresh_pass_clicked();
}

void MainWindow::on_his_pb_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(2);
    on_refresh_btn_clicked();
}

void MainWindow::on_bal_pb_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(3);
    on_money_query_btn_clicked();
}

void MainWindow::on_money_query_btn_clicked()
{
    user->Query_Blance();
    ui->money_dis_lab->setText(user->Balance()->toString(Price::numberOnly,true));
}

void MainWindow::on_money_update_btn_clicked()
{
    ChargeDialoge* NewChargeDialoge = new ChargeDialoge(this);
    NewChargeDialoge->exec();
    on_money_query_btn_clicked();
}


void MainWindow::on_info_query_btn_clicked()
{
    user->Query_Info();

    ui->username_lab->setText(user->Username());
    ui->name_lab->setText(user->Name());
    ui->sex_lab->setText((user->Sex()==0)?"男":"女");
    ui->phone_lab->setText(user->Phone());
    ui->email_lab->setText(user->Email());
}

void MainWindow::on_info_updatebtn_clicked()
{
    InfoDialog* NewInfoDialog = new InfoDialog(this);
    NewInfoDialog->exec();
    on_info_query_btn_clicked();
}

void MainWindow::on_password_reset_clicked()
{
    PasswordDialog* NewPasswordDialog = new PasswordDialog(this);
    NewPasswordDialog->exec();
}

void MainWindow::on_refresh_pass_clicked()
{
    user->Query_User();//从数据库刷新

    int pass_size = user->Pass_Size();
    ui->passinfo->setRowCount(pass_size);
    //ui->passinfo->setColumnCount(2);

    for(int i = 0;i<pass_size;i++)
    {
        ui->passinfo->setItem(i,0,new QTableWidgetItem(user->Pass_Name(i)));
        ui->passinfo->setItem(i,1,new QTableWidgetItem(user->Pass_ID(i)));
    }
    ui->passinfo->show();
}

void MainWindow::on_refresh_btn_clicked()
{
    user->Query_Ticket();

    int ticket_size = user->Ticket_Size();
    ui->ticketinfo->setRowCount(ticket_size);

    for(int i = 0;i<ticket_size;i++)
    {
        ui->ticketinfo->setItem(i,0,new QTableWidgetItem(user->ticket(i)->passenger().Name()));             
        ui->ticketinfo->setItem(i,1,new QTableWidgetItem(user->ticket(i)->train().number()));
        ui->ticketinfo->setItem(i,2,new QTableWidgetItem(user->ticket(i)->spot().toString()));
        ui->ticketinfo->setItem(i,3,new QTableWidgetItem(user->ticket(i)->train().origin().name()));
        ui->ticketinfo->setItem(i,4,new QTableWidgetItem(user->ticket(i)->train().destination().name()));
        ui->ticketinfo->setItem(i,5,new QTableWidgetItem(user->ticket(i)->train().departureTime().toString()));
        ui->ticketinfo->setItem(i,6,new QTableWidgetItem(user->ticket(i)->train().arrivalTime().toString()));
        ui->ticketinfo->setItem(i,7,new QTableWidgetItem(user->ticket(i)->train().price().toString()));
    }
    ui->ticketinfo->show();
}

void MainWindow::on_add_pass_clicked()
{
    PassDialog* new_passdialog = new PassDialog(user);
    new_passdialog->exec();   
    on_refresh_pass_clicked();
}

void MainWindow::on_delete_pass_clicked()
{
    int ref = ui->passinfo->currentRow();
    user->Delete_Passenger(ref);
    on_refresh_pass_clicked();
}

void MainWindow::on_delete_btn_clicked()
{
    bool flag = user->Return_Ticker(ui->ticketinfo->currentRow());

    QString result;
    if(flag)    result = "退票成功！";
    else        result = "退票失败！";

    QMessageBox msg;
    msg.setText(result);
    msg.exec();
    on_refresh_btn_clicked();
}
