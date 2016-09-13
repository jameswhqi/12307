#include "spot.h"

Spot::Spot(int index, SpotType type, bool booked)
    :m_index(index), m_type(type), m_booked(booked)
{
    switch (m_type) {
    case SEAT:
        break;
    case GSEAT:
        m_row = m_index / SEATS_IN_A_ROW + 1;
        m_column = Column(m_index % SEATS_IN_A_ROW);
        break;
    case BED:
        m_row = m_index / 3 + 1;
        m_level = Level(m_index % 3);
        break;
    }
}

int Spot::index() const
{
    return m_index;
}
void Spot::setIndex(int index)
{
    m_index = index;
    switch (m_type) {
    case SEAT:
        break;
    case GSEAT:
        m_row = index / SEATS_IN_A_ROW + 1;
        m_column = Column(index % SEATS_IN_A_ROW);
        break;
    case BED:
        m_row = index / 3 + 1;
        m_level = Level(index % 3);
    }
}
Spot::SpotType Spot::type() const
{
    return m_type;
}
void Spot::setType(SpotType type)
{
    m_type = type;
    this->setIndex(m_index);
}
bool Spot::booked() const
{
    return m_booked;
}
void Spot::book()
{
    m_booked = true;
}
void Spot::cancel()
{
    m_booked = false;
}
void Spot::toggle()
{
    m_booked = !m_booked;
}
QString Spot::toString() const
{
    switch (m_type) {
    case SEAT:
        return QString::number(m_index + 1).append("号");
    case GSEAT:
        switch (m_column) {
        case A:
            return QString::number(m_row).append('A');
        case B:
            return QString::number(m_row).append('B');
        case C:
            return QString::number(m_row).append('C');
        case D:
            return QString::number(m_row).append('D');
        case F:
            return QString::number(m_row).append('F');
        }
    case BED:
        switch (m_level) {
        case BOTTOM:
            return QString::number(m_row).append("下");
        case MIDDLE:
            return QString::number(m_row).append("中");
        case TOP:
            return QString::number(m_row).append("上");
        }
    }

}

int Spot::row()
{
    return m_row;
}
void Spot::setRow(int row)
{
    m_row = row;
    switch (m_type) {
    case SEAT:
        break;
    case GSEAT:
        m_index = (m_row - 1) * SEATS_IN_A_ROW + m_column;
        break;
    case BED:
        m_index = (m_row - 1) * 3 + m_level;
        break;
    }
}
Spot::Column Spot::column()
{
    return m_column;
}
void Spot::setColumn(Column column)
{
    m_column = column;
    m_index = (m_row - 1) * SEATS_IN_A_ROW + m_column;
}
Spot::Level Spot::level()
{
    return m_level;
}
void Spot::setLevel(Level level)
{
    m_level = level;
    m_index = (m_row - 1) * 3 + m_level;
}
