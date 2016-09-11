#ifndef TICKETOFFICE_H
#define TICKETOFFICE_H
#include "ticket.h"
#include "train.h"
#include "station.h"
#include "user.h"
#include "admin.h"
#include "logindialog.h"
#include "mainwindow.h"
#include <QList>

const int SALE_PERIOD = 30;//预售期

class TicketOffice :public QObject
{
    Q_OBJECT
public:
    TicketOffice();

    void updateSpots();//根据数据库modified_date表的日期删除今天之前的spots信息，添加至当前预售期结束
    void searchTrain();//根据用户输入的搜索条件在数据库中搜索车次，存入trainList
public slots:
    void signIn();//接收用户点击LoginDialog中确认键的信号
    void cancelSignIn();//接受LoginDialog的reject()信号
private:
    QList<Train *> m_searchResult;//搜索到的车次表
    QList<Train *> m_usedByTickets;//被User里存的Ticket用到的Train指针列表
    QList<Station *> m_stationList;//所有车站的列表
    User *m_user;//当前User的指针
    Admin *m_admin;//当前Admin的指针
    LoginDialog *m_loginDialog;//LoginDialog的指针
    MainWindow *m_mainWindow;//MainWindow的指针
};


#endif // TICKETOFFICE_H
