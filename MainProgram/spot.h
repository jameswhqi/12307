#ifndef SPOT_H
#define SPOT_H
#include <QString>

const int SEATS_IN_A_ROW = 5;//高铁每排的座位数

//座位/床位类
class Spot
{
public:
    Spot(int index = 0, SpotType type = SEAT, bool booked = false);

    int index() const;//返回编号
    void setIndex(int index);//设置编号
    SpotType type() const;//返回位子类型
    void setType(SpotType type);//设置位子类型
    bool booked() const;//返回是否被预订
    void book();//预订
    void cancel();//取消预订（释放位子）
    void toggle();//改变预订状态
    QString toString() const;//按格式打印

    int row();//（高铁和卧铺）返回排数
    void setRow(int row);//（高铁和卧铺）设置排数
    Column column();//（高铁）返回列数
    void setColumn(Column column);//（高铁）设置列数
    Level level();//（卧铺）返回铺位
    void setLevel(Level level);//（卧铺）设置铺位

    enum SpotType { SEAT, GSEAT, BED };//硬座/高铁/卧铺
    enum Column { A, B, C, D, F };//高铁座位的列
    enum Level { BOTTOM, MIDDLE, TOP };//床位的上中下铺
private:
    int m_index;//座位/床位编号，从0开始
    SpotType m_type;//位子类型
    bool m_booked;//是否被预订
    int m_row;//（高铁和卧铺）第几排，从1开始
    Column m_column;//（高铁）第几列
    Level m_level;//（卧铺）上中下铺
};

#endif // SPOT_H
