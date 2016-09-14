#include "orderdialog.h"
#include "ui_orderdialog.h"
#include "user.h"

OrderDialog::OrderDialog(User *user) :
    ui(new Ui::OrderDialog)
{
    ui->setupUi(this);
}

OrderDialog::~OrderDialog()
{
    delete ui;
}

void OrderDialog::displayTrainInfo(QString info)
{
    ui->trainInfoLabel->setText(info);
}
