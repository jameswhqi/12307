#include "logindialog.h"
#include "ui_logindialog.h"
#include "ticketoffice.h"

LoginDialog::LoginDialog(TicketOffice *TO) :
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    connect(ui->signInButton, SIGNAL(clicked()), TO, SLOT(signIn()));
    connect(ui->modeSelector, SIGNAL(currentChanged(int)), this, SLOT(toggleHide(int)));
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

bool LoginDialog::mode()
{
    return ui->modeSelector->currentIndex();
}
QString LoginDialog::username()
{
    if (ui->modeSelector->currentIndex()) {
        return ui->username_2->text();
    }
    else {
        return ui->username->text();
    }
}
QString LoginDialog::password()
{
    if (ui->modeSelector->currentIndex()) {
        return ui->password_2->text();
    }
    else {
        return ui->password->text();
    }
}

void LoginDialog::toggleHide(int mode)
{
    if (mode) {
        ui->signUpButton->hide();
    }
    else {
        ui->signUpButton->show();
    }
}
