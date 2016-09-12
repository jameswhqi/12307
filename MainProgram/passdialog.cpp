#include "passdialog.h"
#include "ui_passdialog.h"
#include "QString.h"
#include "user.h"

PassDialog::PassDialog(QWidget *parent,User* new_user) :
    QDialog(parent),
    ui(new Ui::PassDialog)
{
    ui->setupUi(this);
    user = new_user;
}

PassDialog::~PassDialog()
{
    delete ui;
}

void PassDialog::on_pushButton_clicked()
{
    QString new_name = ui->lineEdit->text();
    QString new_id = ui->lineEdit_2->text();
    user->Add_Passenger(new_name,new_id);
}
