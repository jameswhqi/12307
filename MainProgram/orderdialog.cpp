#include "orderdialog.h"
#include "ui_orderdialog.h"
#include "ticketoffice.h"
#include <QDebug>
#include <QMessageBox>

OrderDialog::OrderDialog(User *new_user, TicketOffice *TO) :
    ui(new Ui::OrderDialog)
{
    ui->setupUi(this);
    user = new_user;
    m_TO = TO;
}

OrderDialog::~OrderDialog()
{
    delete ui;
}

void OrderDialog::displayTrainInfo(QString info)
{
    ui->trainInfoLabel->setText(info);
}

void OrderDialog::Show_Passenger()
{
    int pass_size = user->Pass_Size();
    ui->passengerSelector->setRowCount(pass_size);
    for(int i = 0;i<pass_size;i++)
    {
        ui->passengerSelector->setItem(i,0,new QTableWidgetItem(user->Pass_Name(i)));
        ui->passengerSelector->setItem(i,1,new QTableWidgetItem(user->Pass_ID(i)));
    }
    ui->passengerSelector->show();
}

void OrderDialog::on_confirmButton_clicked()
{
    int state = -1;//0－购票成功，1－余额不足，2－购票重复,其他－未知错误
    int pass_ref = ui->passengerSelector->currentRow();
    if (pass_ref == -1) {
        return;
    }
    state = user->Buy_Ticket(pass_ref);

    QString result;
    if(state == 1)
    {
        result = "余额不足！";
    }
    else if(state == 2)
    {
        result = "该乘客已购买该车次车票！";
    }
    else if(state == 0)
    {
        //user->Set_Current_Train(NULL);
        result  = "购票成功!";
    }
    else
    {
        result = "未知错误！";
    }
    QMessageBox msg;
    msg.setText(result);
    msg.exec();
    m_TO->searchTrain();
    this->reject();
}
