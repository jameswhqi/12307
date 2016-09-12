#include "passenger.h"
#include <QString>

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

const QString Passenger::Name()
{
    return name;
}

const QString Passenger::ID()
{
    return id;
}
