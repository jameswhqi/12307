#ifndef CHARGEDIALOGE_H
#define CHARGEDIALOGE_H

#include <QDialog>

namespace Ui {
class ChargeDialoge;
}

class ChargeDialoge : public QDialog
{
    Q_OBJECT

public:
    explicit ChargeDialoge(QWidget *parent = 0);
    ~ChargeDialoge();

private slots:
    void on_pushButton_clicked();

    void on_money_yes_clicked();

    void on_money_no_clicked();

private:
    Ui::ChargeDialoge *ui;
};

#endif // CHARGEDIALOGE_H
