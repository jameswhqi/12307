#ifndef ORDERDIALOG_H
#define ORDERDIALOG_H

#include <QDialog>

namespace Ui {
class OrderDialog;
}

class OrderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OrderDialog(QWidget *parent = 0);
    ~OrderDialog();

private:
    Ui::OrderDialog *ui;
};

#endif // ORDERDIALOG_H
