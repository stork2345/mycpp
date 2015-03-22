#include "dvdclient.h"
#include "ui_dvdclient.h"
#include "common.h"

#include <cstdio>
#include <QTableWidget>

#include <QDebug>
#include <QList>



dvdclient::dvdclient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::dvdclient)
{
    ui->setupUi(this);
    ui->name_lab->setText(user.getName());
    QString level = QString("%1").arg(user.getLevel());
    ui->level_lab->setText(level);
    QString money=QString("%1").arg(user.getMoney());
    ui->money_lab->setText(money);
}

dvdclient::~dvdclient()
{
    delete ui;
}

void dvdclient::on_Btn_his_clicked()
{
    MYSQL_RES *res = NULL;
    MYSQL_ROW row = NULL;
    QList<History> *his_list=NULL;

    DATETIME start;
    DATETIME ret;
    double cost=0;

    QString name = ui->name_lab->text();
    QString sql_cmd="select * from history where USERNAME = '"+name+"';";
    char*  ch=NULL;
    QByteArray ba = sql_cmd.toLatin1();
    ch=ba.data();

    if(mysql_query(conn, ch))
    {
            printf("%s\n",mysql_error(conn));
            exit(1);
    }
    res = mysql_use_result(conn);
    while ((row = mysql_fetch_row(res)) != NULL)
    {
       start.chartodate(row[3]);
       ret.chartodate(row[4]);
       double cost=atol(row[5]);
       History cur(row[1],row[2],start,ret,cost);
       his_list->push_back(cur);
    }

}
