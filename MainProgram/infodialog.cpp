#include "infodialog.h"
#include "ui_infodialog.h"

InfoDialog::InfoDialog(MainWindow *parent) :
    ui(new Ui::InfoDialog)
{
    MW = parent;
    ui->setupUi(this);
    //ui->username->setText(user->Username());
    ui->name->setText(MW->user->Name());
    ui->sex->setText((MW->user->Sex()==0)?"男":"女");
    ui->phone->setText(MW->user->Phone());
    ui->email->setText(MW->user->Email());
}

InfoDialog::~InfoDialog()
{
    delete ui;
}

void InfoDialog::on_confirm_clicked()
{
    QString new_name = ui->name->text();
    int new_sex = (ui->sex->text()=="男")? 0:1;
    QString new_phone = ui->phone->text();
    QString new_email = ui->email->text();

    if(MW->user->Update_Info(new_name,new_sex,new_phone,new_email))
    {
        ui->result->setText("修改成功");
    }
    else
    {
        ui->result->setText("修改失败");
    }
}

void InfoDialog::on_cancel_clicked()
{
    this->reject();
}
