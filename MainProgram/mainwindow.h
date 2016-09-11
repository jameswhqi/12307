#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "train.h"
#include <QMainWindow>
#include <user.h>

namespace Ui {
class MainWindow;
}

class TicketOffice;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(bool mode, TicketOffice *TO, User *newuser = NULL);
    ~MainWindow();
    User *user;

    //返回搜索区域的信息
    QString origin();//始发站选中的文本
    QString destination();//终点站选中的文本
    QDate date();//选中的日期
    QString number();//填入的车次
    int trainType();//选中的列车类型
    int spotType();//选中的位子类型

    void setStations(QList<Station *> &stationList);//设置车站下拉列表

    void clearTrainInfo();//清空搜索结果
    void showTrainInfo(QList<Train *> *searchResult);//显示搜索结果
private slots:
    void on_train_btm_clicked();

    void on_user_btm_clicked();

    void on_info_pb_clicked();

    void on_pass_pb_clicked();

    void on_his_pb_clicked();

    void on_bal_pb_clicked();

    void on_money_query_btn_clicked();

    void on_money_update_btn_clicked();

    void on_pushButton_clicked();

    void on_info_query_btn_clicked();

    void on_info_updatebtn_clicked();

    void on_password_reset_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
