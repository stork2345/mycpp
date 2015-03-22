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

private slots:


    void on_Btn_his_clicked();

private:
    Ui::dvdclient *ui;

};

#endif // DVDCLIENT_H
