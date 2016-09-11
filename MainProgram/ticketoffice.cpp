#include "ticketoffice.h"
#include <QSqlQuery>
#include <QVariant>
#include <QtMath>
#include <QByteArray>
#include <QMessageBox>

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

void TicketOffice::signIn()
{
    bool mode = m_loginDialog->mode();
    QString username = m_loginDialog->username();
    QString password = m_loginDialog->password();
    QSqlQuery query;
    if (mode) {
        query.prepare("SELECT idx FROM admin WHERE username=? AND password=?");
    }
    else {
        query.prepare("SELECT idx FROM users WHERE username=? AND password=?");
    }
    query.addBindValue(username);
    query.addBindValue(password);
    query.exec();
    if (query.next()) {
        int idx = query.value(0);
        m_mainWindow = new MainWindow(mode, this);
        m_mainWindow->setStations(m_stationList);
        if (mode) {
            m_admin = new Admin(idx, m_mainWindow);
        }
        else {
            m_user = new User(idx, m_mainWindow);
        }
    }
    else {
        QMessageBox msg;
        msg.setText("用户名或密码错误！");
        msg.setDefaultButton(QMessageBox::Ok);
        msg.exec();
    }
}

//void TicketOffice::cancelSignIn() {}

void TicketOffice::searchTrain()
{
    m_mainWindow->clearTrainInfo();
    QList<Train *>::const_iterator i;
    for (i = m_searchResult.constBegin(); i != m_searchResult.constEnd(); i++) {
        if (m_cache.indexOf(*i) == -1) {
            m_cache.prepend(*i);
        }
    }
    m_searchResult.clear();

    QDate s_date(m_mainWindow->date());
    if (s_date < QDate::currentDate() || s_date.toJulianDay() - QDate::currentDate().toJulianDay() >= SALE_PERIOD) {
        QMessageBox msg;
        msg.setText("搜索日期不在预售期内！");
        msg.setDefaultButton(QMessageBox::Ok);
        msg.exec();
        return;
    }
    QString superQuery("(SELECT * FROM trains)");
    QString s_origin(m_mainWindow->origin()), s_destination(m_mainWindow->destination()), s_number(m_mainWindow->number());
    int s_trainType = m_mainWindow->trainType(), s_spotType = m_mainWindow->spotType();
    bool toSelect[5] = {0,0,0,0,0};
    if (!s_origin.isEmpty()) {
        superQuery.prepend("(SELECT * FROM ");
        superQuery.append(" WHERE origin=:origin)");
        toSelect[0] = true;
    }
    if (!s_destination.isEmpty()) {
        superQuery.prepend("(SELECT * FROM ");
        superQuery.append(" WHERE destination=:destination)");
        toSelect[1] = true;
    }
    if (!s_number.isEmpty()) {
        superQuery.prepend("(SELECT * FROM ");
        superQuery.append(" WHERE number=:number)");
        toSelect[2] = true;
    }
    if (s_trainType != -1) {
        superQuery.prepend("(SELECT * FROM ");
        superQuery.append(" WHERE traintype=:traintype)");
        toSelect[3] = true;
    }
    if (s_spotType != -1) {
        superQuery.prepend("(SELECT * FROM ");
        superQuery.append(" WHERE spottype=:spottype)");
        toSelect[4] = true;
    }
    superQuery.prepend("SELECT (idx, number, traintype, spottype, origin, destination, departuretime, duration, price, spots) FROM ");
    QSqlQuery query;
    query.prepare(superQuery);
    if (toSelect[0]) {
        query.bindValue(":origin", s_origin);
    }
    if (toSelect[1]) {
        query.bindValue(":destination", s_destination);
    }
    if (toSelect[2]) {
        query.bindValue(":number", s_number.toUpper());
    }
    if (toSelect[3]) {
        query.bindValue(":traintype", s_trainType);
    }
    if (toSelect[4]) {
        query.bindValue(":spottype", s_spotType);
    }
    query.exec();
    while (query.next()) {
        int idx = query.value(0).toInt();
        Train *pointer;
        QList<Train *>::const_iterator i;
        for (i = m_cache.constBegin(); i != m_cache.constEnd(); i++) {
            if ((*i)->index() == idx && (*i)->date() == s_date) {
                pointer = &(*i);
                break;
            }
        }
        if (pointer == nullptr) {
            QString d_number = query.value(1).toString();
            Train::TrainType d_trainType = Train::TrainType(query.value(2).toInt());
            Spot::SpotType d_spotType = Spot::SpotType(query.value(3).toInt());
            int d_originIdx = query.value(4).toInt();
            int d_destinationIdx = query.value(5).toInt();
            Station *d_origin, *d_destination;
            QList<Station *>::iterator i;
            bool foundOne = false;
            for (i = m_stationList.constBegin(); i != m_stationList.constEnd(); i++) {
                if ((*i)->index() == d_originIdx) {
                    d_origin = &(*i);
                    if (foundOne) {
                        break;
                    }
                    foundOne = true;
                }
                if ((*i)->index() == d_destinationIdx) {
                    d_destination = &(*i);
                    if (foundOne) {
                        break;
                    }
                    foundOne = true;
                }
            }
            Time d_departureTime = Time::fromString(query.value(6).toString());
            Time d_duration = Time::fromString(query.value(7).toString());
            Price d_price(query.value(8).toInt());
            QByteArray d_spots = query.value(9).toByteArray();
            pointer = new Train(idx, d_number, Train::TrainType(d_trainType), Spot::SpotType(d_spotType), *d_origin, *d_destination, d_departureTime, d_duration, d_price, false);
            int bytesPerDay, spotCount;
            if (int(d_spotType) == 2) {
                spotCount = BED_COUNT;
                bytesPerDay = qCeil(BED_COUNT / 8.0);
            }
            else {
                spotCount = SEAT_COUNT;
                bytesPerDay = qCeil(SEAT_COUNT / 8.0);
            }
            QByteArray thisDay = d_spots.mid((s_date.toJulianDay() - QDate::currentDate().toJulianDay()) * bytesPerDay, bytesPerDay);
            for (int i = 0; i < spotCount; i++) {
                char eightSpots = thisDay.at(i / 8);
                if (eightSpots && (eightSpots >> (7 - i % 8)) % 2) {
                    pointer->spot(i).book();
                }
            }
        }
        m_searchResult.append(pointer);
    }
    m_mainWindow->showTrainInfo(m_searchResult);
}
