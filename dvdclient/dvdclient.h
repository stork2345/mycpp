#ifndef DVDCLIENT_H
#define DVDCLIENT_H

#include <QMainWindow>
#include "common.h"
#include <mysql/mysql.h>



extern User user;
extern MYSQL *conn;

namespace Ui {
class dvdclient;
}

class dvdclient : public QMainWindow
{
    Q_OBJECT

public:
    explicit dvdclient(QWidget *parent = 0);
    ~dvdclient();
    void load();
private slots:


    void on_Btn_his_clicked();

    void on_Btn_show_clicked();



    void on_rented_tab_cellClicked(int row, int column);

    void on_Btn_my_clicked();

    void on_Btn_ret_clicked();

    void on_brn_recharge_clicked();
    
    void on_Btn_rent_clicked();

    void on_Btn_EXIT_clicked();

private:
    Ui::dvdclient *ui;
};

#endif // DVDCLIENT_H
