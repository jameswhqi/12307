#ifndef SPOT_H
#define SPOT_H
#include <QString>

//座位/床位基类
class Spot
{
public:
    Spot();
    bool isOccupied();//返回是否被预订
protected:
    int index;//座位/床位编号，在1~120内取值
    bool occupied;//是否被预订
    int row;//第几排
};

//座位类
class Seat :public Spot {
public:
    QString print();//按标准格式打印
private:
    Column column;//第几列
};

//床位类
class Bed :public Spot {
public:
    QString print();//按标准格式打印
private:
    Level level;//上中下铺
};

//座位的列
enum Column {
    A, B, C, D, E, F
};

//床位的上中下铺
enum Level {
    Bottom, Middle, Top
};

#endif // SPOT_H
