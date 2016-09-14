#include "passenger.h"
#include <QVariant>

Passenger* Passenger::newPass(const QString new_name, const QString new_id)
{
    Passenger* res = new Passenger(new_name,new_id);
    return res;
}

void Passenger::resetPass(QString new_name, const QString new_id)
{
    name = new_name;
    id = new_id;
}

QString Passenger::Name()
{
    return name;
}

QString Passenger::ID()
{
    return id;
}

int Passenger::index()
{
    QSqlQuery query;
    query.prepare("select idx from passengers where name=:name and id=:id");
    query.bindValue(":name",name);
    query.bindValue(":id",id);
    query.exec();

    int res = query.value(0).toInt();
    return res;
}
