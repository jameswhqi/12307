#ifndef TRAIN_H
#define TRAIN_H
#include "spot.h"
#include <QString>
#include <QVector>
#include <QtMath>

const int SEAT_COUNT = 120;//每个车次的座位/床位数

class Train {
public:
    Train();
    int occupiedCount();//返回已被预订的座位/床位数
    int vacantCount();//返回未被预订的座位/床位数
private:
    int index;//对应于数据库中的索引编号
    QString number;//车次编号
    TrainType type;//车次类型（特快/普快/高铁）
    Station &origin, &destination;//始发站、终点站
    Time departureTime, arrivalTime;//出发、到达时刻
    Price price;//票价
};

//硬座车类
class SeatTrain :public Train {
public:
    SeatTrain();
private:
    QVector<Seat> seats;//座位对象数组
};

//卧铺车类
class BedTrain :public Train {
public:
    BedTrain();
private:
    QVector<Bed> beds;//床位对象数组
};

//车次类型（特快/普快/高铁）
enum TrainType {
    T, K, G
};

//车站类
class Station {
private:
    int index;//对应于数据库中的索引编号
    QString stationName;//车站名称
};

//时刻类
class Time {
public:
    int getHour();
    int getMinute();
    QString print();//按标准格式打印
private:
    int hour, minute;
};

//价格类
class Price {
public:
    double getReal();//返回实型价格
    int getYuan();//返回价格的整数部分
    int getFen();//返回价格的小数部分，如12.34元返回34
    QString print();//按标准格式打印
private:
    int dataFen;//以分为单位的价格数据，如1234表示12.34元
};

#endif // TRAIN_H
