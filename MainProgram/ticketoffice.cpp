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

    //根据数据库modified_date表的日期删除今天之前的spots信息，添加至当前预售期结束
    query.exec("SELECT date FROM modified_date");
    query.next();
    QDate original = QDate::fromString(query.value(0).toString());
    int diff = QDate::currentDate().toJulianDay() - original.toJulianDay();
    query.exec("SELECT (spottype, spots) ")
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
        query.prepare("SELECT idx FROM ");
    }
}
