#ifndef TICKETOFFICE_H
#define TICKETOFFICE_H
#include "mainwindow.h"
#include "logindialog.h"
#include "orderdialog.h"
#include "adminwindow.h"
#include "addtraindialog.h"
#include <QList>
#include <QObject>

const int SALE_PERIOD = 30;//预售期

class TicketOffice :public QObject
{
    Q_OBJECT
public:
    TicketOffice();

    void updateSpots();//根据数据库modified_date表的日期删除今天之前的spots信息，添加至当前预售期结束
    Train *trainForTicket(int idx, QString date);

    Ticket *createTicket(Passenger *passenger);
    //void clearCache(bool all = false);//当m_cache太大的时候进行清空，all为false时保留存在于Ticket中的Train指针
public slots:
    void searchTrain();
    void signIn();//接收用户点击LoginDialog中确认键的信号
    //void cancelSignIn();//接受LoginDialog的rejected()信号
    void order();//接收用户点击MainWindow中购买键的信号

    void adminSearchTrain();
    void modifyTrain();
    void addTrain();

    void confirmAdMoTrain();

    void showLoginDialog();
private:
    QList<Train *> m_searchResult;//搜索到的车次表
    QList<Train *> m_cache;//所有已经被读取过的Train的指针列表
    QList<Station *> m_stationList;//所有车站的列表
    User *m_user;//当前User的指针
    LoginDialog *m_loginDialog;//LoginDialog的指针
    MainWindow *m_mainWindow;//MainWindow的指针
    OrderDialog *m_orderDialog;//OrderDialog的指针
    AdminWindow *m_adminWindow;
    AddTrainDialog *m_addTrainDialog;
    Train *currentTrain;

    bool m_modifyMode;

    Station *findStation(QString name);//根据车站名查找车站
};


#endif // TICKETOFFICE_H
