#ifndef LOGWINDOW_H
#define LOGWINDOW_H

#include <QDialog>
#include "common.h"
#include <mysql/mysql.h>


extern User user;
extern MYSQL *conn;

namespace Ui {
class logwindow;
}

class logwindow : public QDialog
{
    Q_OBJECT

public:
    explicit logwindow(QWidget *parent = 0);
    ~logwindow();

private slots:


    void on_Btn_signin_clicked();



    void on_Btn_cancel_clicked();


    void on_Btn_reg_clicked();

private:
    Ui::logwindow *ui;
};

#endif // LOGWINDOW_H
