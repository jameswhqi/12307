#include "train.h"

Train::Train(int index, QString number, TrainType trainType, Spot::SpotType spotType,
             Station &origin, Station &destination, Time departureTime,
             Time duration, Price price)
    : m_index(index), m_number(number), m_trainType(trainType), m_spotType(spotType),
      m_origin(&origin), m_destination(&destination), m_departureTime(departureTime),
      m_duration(duration), m_price(price)
{
    int spotCount;
    if (m_spotType == Spot::BED) {
        spotCount = BED_COUNT;
    }
    else {
        spotCount = SEAT_COUNT;
    }
    m_spots.reserve(spotCount);
    for (int i = 0; i < spotCount; i++) {
        m_spots.append(Spot(i, m_spotType));
    }
}

int Train::index() const
{
    return m_index;
}
void Train::setIndex(int index)
{
    m_index = index;
}
QString Train::number() const
{
    return m_number;
}
void Train::setNumber(const QString &number)
{
    m_number = number;
    switch (number[0].toLatin1()) {
    case 'T':
        m_trainType = T;
        break;
    case 'K':
        m_trainType = K;
        break;
    case 'G':
        m_trainType = G;
    }
}
Train::TrainType Train::trainType() const
{
    return m_trainType;
}
Spot::SpotType Train::spotType() const
{
    return m_spotType;
}
Station &Train::origin() const
{
    return *m_origin;
}
void Train::setOrigin(const Station &origin)
{
    m_origin = &origin;
}
Station &Train::destination() const
{
    return *m_destination;
}
void Train::setDestination(const Station &destination)
{
    m_destination = &destination;
}
Time Train::departureTime() const
{
    return m_departureTime;
}
Time Train::duration() const
{
    return m_duration;
}
Time Train::arrivalTime() const
{
    return m_departureTime.elapse(m_duration);
}
void Train::setDepartureTime(Time time)
{
    m_departureTime = time;
}
void Train::setDuration(Time duration)
{
    m_duration = duration;
}
Spot &Train::spot(int index)
{
    return m_spots[index];
}
int Train::occupiedCount()
{
    int count = 0, spotCount;
    if (m_spotType == Spot::BED) {
        spotCount = BED_COUNT;
    } else {
        spotCount = SEAT_COUNT;
    }
    for (int i = 0; i < spotCount; i++) {
        if (m_spots[i].booked()) {
            count++;
        }
    }
    return count;
}
int Train::vacantCount()
{
    if (m_spotType == Spot::BED) {
        return BED_COUNT - occupiedCount();
    } else {
        return SEAT_COUNT - occupiedCount();
    }
}
int Train::findVacant()
{
    int spotCount;
    if (m_spotType == Spot::BED) {
        spotCount = BED_COUNT;
    } else {
        spotCount = SEAT_COUNT;
    }
    for (int i = 0; i < SEAT_COUNT; i++) {
        if (!m_seats[i].booked()) {
            return i;
        }
    }
    return -1;
}


Price::Price(int dataFen)
    : m_dataFen(dataFen) {}

double Price::toReal() const
{
    return m_dataFen / 100.0;
}
int Price::dataFen() const
{
    return m_dataFen;
}
int Price::getYuan() const
{
    return m_dataFen / 100;
}
int Price::getSubYuan() const
{
    return m_dataFen % 100;
}
void Price::setDataFen(int dataFen)
{
    m_dataFen = dataFen;
}
void Price::setYuan(int yuan)
{
    m_dataFen = yuan * 100 + m_dataFen % 100;
}
void Price::setSubYuan(int subYuan)
{
    m_dataFen = m_dataFen / 100 * 100 + subYuan;
}
QString Price::toString(PriceFormat format, bool thousandSeparator) const
{
    QString number = QString::number(m_datafen);
    number.insert(number.size() - 2, '.');
    if (thousandSeparator) {
        for (int i = number.size() - 6; i > 0; i -= 3) {
            number.insert(i, ',');
        }
    }
    switch (format) {
    case numberOnly:
        return number;
    case numberYuan:
        number.append("元");
        return number;
    case symbolNumber:
        number.prepend("￥");
        return number;
    case RMBNumber:
        number.prepend("RMB");
        return number;
    }
}


Time::Time(int hour, int minute)
    : m_hour(hour), m_minute(minute), m_day(0) {}

int Time::hour()
{
    return m_hour;
}
int Time::minute()
{
    return m_minute;
}
int Time::day()
{
    return m_day;
}
void Time::setHour(int hour)
{
    m_hour = hour;
}
void Time::setMinute(int minute)
{
    m_minute = minute;
}
QString Time::toString()
{
    QString result = QString("%1:%2").arg(m_hour, 2, 10, '0').arg(m_minute, 2, 10, '0');
    if (m_day != 0) {
        result.append(QString("(第%1天)").arg(m_day + 1));
    }
    return result;
}
Time Time::elapse(const Time &duration)
{
    Time result;
    result.m_minute = m_minute + duration.m_minute;
    result.m_hour = m_hour + duration.m_hour;
    result.m_hour += result.m_minute / 60;
    result.m_minute = result.m_minute % 60;
    result.m_day += result.m_hour / 24;
    result.m_hour = result.m_hour % 24;
    return result;
}
