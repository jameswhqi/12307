#include "passdialog.h"
#include "ui_passdialog.h"
#include <QString>

PassDialog::PassDialog(User* new_user) :
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
    ui->label_4->setText("添加成功！");
}

void PassDialog::on_pushButton_2_clicked()
{
    this->reject();
}
