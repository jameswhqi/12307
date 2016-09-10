#ifndef STATION_H
#define STATION_H
#include <QString>

//车站类
class Station
{
public:
    Station(int index = 0, QString name = QString());

    int index() const;
    QString name() const;
    void setIndex(int index);
    void setName(const QString &name);
private:
    int m_index;//对应于数据库中的索引编号
    QString m_name;//车站名称
};

#endif // STATION_H
