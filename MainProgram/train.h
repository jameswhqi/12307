#ifndef TRAIN_H
#define TRAIN_H
#include "spot.h"
#include "station.h"
#include <QString>
#include <QVector>
#include <QDate>

const int SEAT_COUNT = 120;//每个硬座车次的座位数
const int BED_COUNT = 60;//每个卧铺车次的床位数

//车次类
class Train
{
public:
    Train(int index, QString number, TrainType trainType, Spot::SpotType spotType,
          Station &origin, Station &destination, Time departureTime,
          Time duration, Price price);

    int index() const;//返回索引编号
    void setIndex(int index);//设置索引编号
    QString number() const;//返回车次编号
    void setNumber(const QString &number);//设置车次编号
    TrainType trainType() const;//返回车次类型
    Spot::SpotType spotType() const;//返回位子类型
    Station &origin() const;//返回始发站引用
    void setOrigin(const Station &origin);//设置始发站
    Station &destination() const;//返回终点站引用
    void setDestination(const Station &destination);//设置终点站
    QDate date() const;//返回出发日期
    void setDate(QDate date);//设置出发日期
    Time departureTime() const;//返回出发时刻
    Time duration() const;//返回运行时间
    Time arrivalTime() const;//返回到达时刻
    void setDepartureTime(Time time);//设置出发时刻
    void setDuration(Time duration);//设置运行时间
    Price price() const;//返回票价
    void setPrice(Price price);//设置票价

    Spot &spot(int index);//返回编号对应的座位/床位引用

    int occupiedCount();//返回已被预订的座位/床位数
    int vacantCount();//返回未被预订的座位/床位数
    int findVacant();//找到一个未被预订的座位/床位并返回它的编号，如果找不到则返回-1

    enum TrainType { T, K, G };//车次类型（特快/普快/高铁）
private:
    int m_index;//对应于数据库中的索引编号
    QString m_number;//车次编号
    TrainType m_trainType;//车次类型（特快/普快/高铁）
    Spot::SpotType m_spotType;//位子类型（硬座/高铁/卧铺）
    Station *m_origin, *m_destination;//始发站、终点站
    QDate m_date;//出发日期
    Time m_departureTime, m_duration;//出发时刻、运行时间
    Price m_price;//票价
    QVector<Spot> m_spots;//座位/床位对象数组
};


//价格类
class Price
{
public:
    Price(int dataFen = 0);

    double toReal() const;//返回实型价格
    int dataFen() const;//返回以分为单位的价格数据
    int getYuan() const;//返回价格的整数部分
    int getSubYuan() const;//返回价格的小数部分，如12.34元返回34
    void setDataFen(int dataFen);//设置以分为单位的价格数据
    void setYuan(int yuan);//设置价格的整数部分
    void setSubYuan(int subYuan);//设置价格的小数部分
    QString toString(PriceFormat format = number, bool thousandSeparator = true) const;
        //按标准格式打印，thousandSeparator表示是否用","分隔千位

    enum PriceFormat {numberOnly, numberYuan, symbolNumber, RMBNumber};
        //打印格式，分别表示"12.34" "12.34元" "￥12.34" "RMB12.34"
private:
    int m_dataFen;//以分为单位的价格数据，如1234表示12.34元
};

//时间/时刻类
class Time
{
public:
    Time(int hour = 0, int minute = 0);

    int hour() const;//返回小时
    int minute() const;//返回分钟
    int day() const;//返回第几天
    void setHour(int hour);//设置小时
    void setMinute(int minute);//设置分钟

    QString toString();//按标准格式打印
    Time elapse(const Time &duration);//返回当前时刻之后duration长度的时刻
private:
    int m_hour, m_minute, m_day;//m_day用于表示elapse()的结果是否超过了当天，1表示第二天
};

#endif // TRAIN_H
