#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>

namespace Ui {
class AdminWindow;
}

class TicketOffice;
class Station;
class Train;

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminWindow(TicketOffice *TO);
    ~AdminWindow();

    //返回搜索区域的信息
    QString origin();//始发站选中的文本
    QString destination();//终点站选中的文本
    QString number();//填入的车次
    int trainType();//选中的列车类型
    int spotType();//选中的位子类型

    void setStations(QList<Station *> &stationList);//设置车站下拉列表

    void clearTrainInfo();//清空搜索结果
    void showTrainInfo(QList<Train *> *searchResult);//显示搜索结果

    QString currentNumber();

    void closeEvent(QCloseEvent *event);
private:
    Ui::AdminWindow *ui;

    TicketOffice *m_TO;
};

#endif // ADMINWINDOW_H
