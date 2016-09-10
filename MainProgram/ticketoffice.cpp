#include "ticketoffice.h"
#include <QSqlQuery>
#include <QVariant>

TicketOffice::TicketOffice()
{
    //读入Stations表
    QSqlQuery query("SELECT (idx, name) FROM stations");
    while (query.next()) {
        Station *temp = new Station(query.value(0).toInt(), query.value(1).toString());
        m_stationList.append(temp);
    }

    //生成LoginDialog
    m_loginDialog = new LoginDialog(this);
    m_loginDialog->show();
}

void TicketOffice::signIn() {
    int mode = m_loginDialog->mode();
    QString username = m_loginDialog->username();
    QString password = m_loginDialog->password();
    QSqlQuery query;
    if (mode) {
        query.prepare("SELECT idx ");
    }
}
