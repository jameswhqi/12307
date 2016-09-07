#ifndef STATION_H
#define STATION_H
#include <QString>

//车站类
class Station
{
public:
    Station();
private:
    int index;//对应于数据库中的索引编号
    QString stationName;//车站名称
};

#endif // STATION_H
