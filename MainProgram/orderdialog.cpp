#include "orderdialog.h"
#include "ui_orderdialog.h"
#include <QDebug>

OrderDialog::OrderDialog(User *new_user) :
    ui(new Ui::OrderDialog)
{
    ui->setupUi(this);
    user = new_user;
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
   ui->passengerSelector->show();//模态的bug？？
}
