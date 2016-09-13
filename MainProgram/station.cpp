#include "station.h"

Station::Station(int index, QString name)
    : m_index(index), m_name(name) {}

int Station::index() const
{
    return m_index;
}

QString Station::name() const
{
    return m_name;
}

void Station::setIndex(int index)
{
    m_index = index;
}

void Station::setName(const QString &name)
{
    m_name = name;
}
