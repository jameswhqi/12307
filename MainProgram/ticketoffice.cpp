#include "ticketoffice.h"
#include <QSqlQuery>
#include <QVariant>
#include <QtMath>
#include <QByteArray>

TicketOffice::TicketOffice()
{
    //读入Stations表
    QSqlQuery query("SELECT (idx, name) FROM stations");
    while (query.next()) {
        Station *temp = new Station(query.value(0).toInt(), query.value(1).toString());
        m_stationList.append(temp);
    }

    updateSpots();

    //生成LoginDialog
    m_loginDialog = new LoginDialog(this);
    m_loginDialog->show();
}

void TicketOffice::updateSpots()
{
    query.exec("SELECT date FROM modified_date");
    query.next();
    QDate original = QDate::fromString(query.value(0).toString());
    if (original != QDate::currentDate()) {
        int diff = QDate::currentDate().toJulianDay() - original.toJulianDay();
        query.exec("SELECT (idx, spottype, spots) FROM trains");
        int bytesPerDay;//一个车次每天的座位空占数据占的字节数
        QByteArray old, valid;
        QSqlQuery query2;
        while (query.next()) {
            if (query.value(1).toInt() == 2) {
                bytesPerDay = qCeil(BED_COUNT / 8.0);
            }
            else {
                bytesPerDay = qCeil(SEAT_COUNT / 8.0);
            }
            old = query.value(2).toByteArray();
            if (SALE_PERIOD <= diff) {
                valid.fill(0, SALE_PERIOD * bytesPerDay);
            }
            else {
                valid = old.right(bytesPerDay * (SALE_PERIOD - diff));
                valid.leftJustified(SALE_PERIOD * bytesPerDay, 0);
            }
            query2.prepare("UPDATE trains SET spots=? WHERE idx=?");
            query2.addBindValue(valid);
            query2.addBindValue(query.value(0));
            query2.exec();
        }
        query.prepare("UPDATE modified_date SET date=?");
        query.addBindValue(QDate::currentDate().toString(Qt::ISODate));
        query.exec();
    }
}

void TicketOffice::signIn() {
    int mode = m_loginDialog->mode();
    QString username = m_loginDialog->username();
    QString password = m_loginDialog->password();
    QSqlQuery query;
    if (mode) {
        query.prepare("SELECT idx FROM admin WHERE username=? AND password=?");
        query.addBindValue(username);
        query.addBindValue(password);
    }
}
