#include "dvdclient.h"
#include "ui_dvdclient.h"
#include "common.h"

#include "recharge.h"
#include "ui_recharge.h"

#include <cstdio>
#include <QTableWidget>
#include <QtGui>
#include <QDebug>
#include <QList>
#include <QMessageBox>
#include "logwindow.h"


int static_row;
extern logwindow *logw;

dvdclient::dvdclient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::dvdclient)
{
    ui->setupUi(this);

    load();
    ui->message->clear();
    ui->pic_lab->setText("no selected");
    ui->pic_lab->setAlignment(Qt::AlignCenter);

}

dvdclient::~dvdclient()
{
    delete ui;
}
void dvdclient::load()
{
    ui->name_lab->setText(user.getName());
    QString level = QString("%1").arg(user.getLevel());
    ui->level_lab->setText(level);
    QString money=QString("%1").arg(user.getMoney());
    ui->money_lab->setText(money);
    ui->Btn_rent->setEnabled(false);
    ui->Btn_ret->setEnabled(false);
}
void dvdclient::on_Btn_his_clicked()
{
    MYSQL_RES *res = NULL;
    MYSQL_ROW row = NULL;
    QList<History> his_list;
    QList<History>::iterator iter;//=his_list.begin();
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
       cost=atol(row[5]);


       // History *cur=new History(row[1],row[2],start,ret,cost);
       History  cur(row[1],row[2],start,ret,cost);
       his_list.push_back(cur);
    }
       iter=his_list.begin();
      QStringList header;
      header<<"DVD"<<"START"<<"RET"<<"COST($)";
      ui->rented_tab->clear();




        ui->rented_tab->setColumnCount(4);
        ui->rented_tab->setHorizontalHeaderLabels(header);
        //ui->rented_tab->setColumnWidth(0,160);
       // ui->rented_tab->horizontalHeader()->setStretchLastSection(true);
       // ui->rented_tab->horizontalHeader()->setStretchLastSection(true);
        ui->rented_tab->setRowCount(his_list.size());
        for(int i=0;i<his_list.size();i++)
        {
            if(iter==his_list.end())
            {
                break;
            }
             char money[24]={};

            ui->rented_tab->setItem(i,0,new QTableWidgetItem((iter->getDvdname())));

            ui->rented_tab->setItem(i,1,new QTableWidgetItem(iter->getStart().datetochar()));
            if(iter->getRet().isempty() )
            {
                    ui->rented_tab->setItem(i,2,new QTableWidgetItem("not return"));
             }
            else
            {
                 ui->rented_tab->setItem(i,2,new QTableWidgetItem(iter->getRet().datetochar()));
            }
             sprintf(money,"%.1lf",iter->getMoney());
             ui->rented_tab->setItem(i,3,new QTableWidgetItem(money));
             ++iter;
        }
        //ui->rented_tab->resizeColumnsToContents();   //resizeColumnToContents (0);
         ui->rented_tab->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
        ui->Btn_ret->setEnabled(false);
        ui->Btn_rent->setEnabled(false);

}

void dvdclient::on_Btn_show_clicked()
{
    MYSQL_RES *res = NULL;
    MYSQL_ROW row = NULL;
    QList<DVD> dvd_list;

    QString sql_cmd="select * from dvdlib where STATUS = '1' order by SALES desc;";

    char*  ch=NULL;
    QByteArray ba = sql_cmd.toLatin1();
    ch=ba.data();

    if(mysql_query(conn, ch))
    {
            printf("%s\n",mysql_error(conn));
            exit(1);
    }

    res = mysql_use_result(conn);
     int price=0;
     int left=0;
    while ((row = mysql_fetch_row(res)) != NULL)
    {

       price =atoi(row[3]);
       left =atoi(row[4]);
       DVD cur(row[1],row[2],price,left);
        dvd_list.push_back(cur);
    }
    QStringList header;
    header<<"DVD"<<"PRICE"<<"LEFT";
    ui->rented_tab->clear();

    ui->rented_tab->setColumnCount(3);
    ui->rented_tab->setHorizontalHeaderLabels(header);
    //ui->rented_tab->horizontalHeader()->setStretchLastSection(true);
    //ui->rented_tab->setColumnWidth(0,160);
   // ui->rented_tab->horizontalHeader()->setStretchLastSection(true);
    ui->rented_tab->setRowCount(dvd_list.size());

    QList<DVD>::iterator iter=dvd_list.begin();


    for(int i=0;i<dvd_list.size();i++)
    {
        if(iter==dvd_list.end())
        {
            break;
        }


        ui->rented_tab->setItem(i,0,new QTableWidgetItem((iter->getName())));
        if(i<3)
        {
            ui->rented_tab->item(i,0)->setIcon(QIcon(QPixmap("/home/iotek/qtres/hot.jpg")));
        }

        char temp[24]={};
        sprintf(temp,"%d",iter->getPrice());
        ui->rented_tab->setItem(i,1,new QTableWidgetItem(temp));
        sprintf(temp,"%d",iter->getLeft());
        ui->rented_tab->setItem(i,2,new QTableWidgetItem(temp));
        if(iter->getLeft()<6)
        {
            ui->rented_tab->item(i,0)->setTextColor(QColor(200,111,100));
            ui->rented_tab->item(i,1)->setTextColor(QColor(200,111,100));
            ui->rented_tab->item(i,2)->setTextColor(QColor(200,111,100));
        }
        iter++;
    }
     ui->rented_tab->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    //ui->rented_tab->resizeColumnsToContents();
    ui->Btn_ret->setEnabled(false);
    ui->Btn_rent->setEnabled(false);


}


void dvdclient::on_rented_tab_cellClicked(int row, int column)
{
    MYSQL_RES *res = NULL;
    MYSQL_ROW mysql_row = NULL;
    static_row=row;
    column=0;
    QString dvdname=ui->rented_tab->item(static_row,column)->text();

    QString q_price=ui->rented_tab->item(static_row,1)->text();
    QString q_left=ui->rented_tab->item(static_row,2)->text();

    QString sql_cmd="select PICFP from dvdlib where DVDNAME='"+dvdname+"';";
    char*  ch=NULL;
    QByteArray ba = sql_cmd.toLatin1();
    ch=ba.data();

    if(mysql_query(conn, ch))
    {
            printf("%s\n",mysql_error(conn));
            exit(1);
    }
    res = mysql_use_result(conn);
    QString fp;
    while ((mysql_row = mysql_fetch_row(res)) != NULL)
    {
        fp=mysql_row[0];
    }

    QPixmap pixmap(fp);
    ui->pic_lab->setPixmap(pixmap);
    ui->pic_lab->show();
    ui->pic_lab->setScaledContents(true);
    int balence=ui->money_lab->text().toInt();
    if((isDigitStr(q_price))&&(isDigitStr(q_left)))
    {
        ui->Btn_ret->setEnabled(false);
        if((balence-q_price.toInt())>0)
        {
            ui->Btn_rent->setEnabled(true);
        }
        else
        {
            ui->Btn_rent->setEnabled(false);
        }
        ui->message->setText("At least more than 1 day");
    }
    else if(q_left!="not return")
    {
        ui->Btn_ret->setEnabled(false);
        ui->Btn_rent->setEnabled(false);
    }
    else
    {
        ui->Btn_ret->setEnabled(true);
        ui->Btn_rent->setEnabled(false);
    }

}

void dvdclient::on_Btn_my_clicked()
{

    QString name =ui->name_lab->text();
    MYSQL_RES *res = NULL;
    MYSQL_ROW row = NULL;
    QList<History> his_list;
    QList<History>::iterator iter;//=his_list.begin();
   DATETIME start;
   DATETIME ret;
    double cost=0;

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
      if(!ret.isempty())
      {
          continue;
      }
       cost=atol(row[5]);


       History  cur(row[1],row[2],start,ret,cost);
       his_list.push_back(cur);
    }
       iter=his_list.begin();
      QStringList header;
      header<<"DVD"<<"START"<<"RET"<<"COST($)";
      ui->rented_tab->clear();




        ui->rented_tab->setColumnCount(4);
        ui->rented_tab->setHorizontalHeaderLabels(header);
        //ui->rented_tab->setColumnWidth(0,120);
        //ui->rented_tab->horizontalHeader()->setStretchLastSection(true);
        //ui->rented_tab->horizontalHeader()->setStretchLastSection(true);
        ui->rented_tab->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
        ui->rented_tab->setRowCount(his_list.size());
        for(int i=0;i<his_list.size();i++)
        {
            if(iter==his_list.end())
            {
                break;
            }

            ui->rented_tab->setItem(i,0,new QTableWidgetItem((iter->getDvdname())));

            ui->rented_tab->setItem(i,1,new QTableWidgetItem(iter->getStart().datetochar()));

            ui->rented_tab->setItem(i,2,new QTableWidgetItem("not return"));
            char money[24]={};

            sprintf(money,"%.1lf",iter->getMoney());
            ui->rented_tab->setItem(i,3,new QTableWidgetItem(money));

           ++iter;
        }
        ui->Btn_ret->setEnabled(false);
        ui->Btn_rent->setEnabled(false);
}

void dvdclient::on_Btn_ret_clicked()
{
        MYSQL_RES *res = NULL;
        MYSQL_ROW row = NULL;

        QString dvdname = ui->rented_tab->item(static_row,0)->text();
        QString qstart=ui->rented_tab->item(static_row,1)->text();
        char*  ch=NULL;
        QByteArray ba=qstart.toLatin1();
        ch=ba.data();
        DATETIME start;
        start.chartodate(ch);
        DATETIME now;
        int date=(now-start)+1;

        QString sql_cmd="update history set RET = '" +QString(QLatin1String(now.datetochar()))+"' where DVDNAME = '"+dvdname+"' and USERNAME = '"+ui->name_lab->text()+"';";


        ba = sql_cmd.toLatin1();
        ch=ba.data();

        if(mysql_query(conn, ch))
        {
                printf("%s\n",mysql_error(conn));
                exit(1);
        }
        sql_cmd = "update dvdlib set LIFT = LIFT + '1' where DVDNAME = '"+dvdname+ "';";
        ba=sql_cmd.toLatin1();
        ch=ba.data();
        if(mysql_query(conn, ch))
        {
                printf("%s\n",mysql_error(conn));
                exit(1);
        }
        sql_cmd="select PRICE from dvdlib where DVDNAME = '"+dvdname+"';";
        ba=sql_cmd.toLatin1();
        ch=ba.data();
        if(mysql_query(conn, ch))
        {
                printf("%s\n",mysql_error(conn));
                exit(1);
        }
        qstart.clear();
        res = mysql_use_result(conn);
        while ((row = mysql_fetch_row(res)) != NULL)
        {
            qstart=row[0];
        }
        double charge = date*(qstart.toDouble());
        qDebug()<<"date:"<<date<<"charge:"<<charge<<endl;

        sql_cmd="update users set MONEY = MONEY - '"+QString::number(charge,'f',0)+"' where NAME = '"+ui->name_lab->text()+"';";
        ba=sql_cmd.toLatin1();
        ch=ba.data();
        if(mysql_query(conn, ch))
        {
                printf("%s\n",mysql_error(conn));
                exit(1);
        }
        user.setMoney(user.getMoney()-charge);
        ui->money_lab->setText(QString::number(user.getMoney()));
        sql_cmd="update history set MONEY = '"+QString::number(charge,'f',0)+"' where USERNAME = '"+ui->name_lab->text()+"' and DVDNAME = '"+dvdname+"';";
        ba=sql_cmd.toLatin1();
        ch=ba.data();
        if(mysql_query(conn, ch))
        {
                printf("%s\n",mysql_error(conn));
                exit(1);
        }


       ui->rented_tab->removeRow(static_row);
       ui->rented_tab->resizeColumnsToContents();
       ui->Btn_ret->setEnabled(false);



}

void dvdclient::on_brn_recharge_clicked()
{
    recharge *chargewidget=new recharge;
    chargewidget->show();
    chargewidget->move((QApplication::desktop()->width() - chargewidget->width())/2,(QApplication::desktop()->height() - chargewidget->height())/2);
    chargewidget->setFocus();
}



void dvdclient::on_Btn_rent_clicked()
{
    MYSQL_RES *res = NULL;
    MYSQL_ROW row = NULL;
    QString dvdname=ui->rented_tab->item(static_row,0)->text();
    QString username=ui->name_lab->text();
    DATETIME now;
    QString start=now.datetochar();
    int left=ui->rented_tab->item(static_row,2)->text().toInt();
    char *ch=NULL;

    if(left<=0)
    {
        ui->message->setText(dvdname+"has already rent over!");
        return;
    }

    QString sql_cmd="select * from history where DVDNAME = '"+dvdname+"' and USERNAME = '"+username+"' and RET = '0000-00-00';";

    QByteArray ba=sql_cmd.toLatin1();
    ch=ba.data();
    ba.clear();
    if(mysql_query(conn, ch))
    {
            printf("%s\n",mysql_error(conn));
            exit(1);
    }
    res = mysql_use_result(conn);
    QString temp;
    while ((row = mysql_fetch_row(res)) != NULL)
    {
        temp=row[0];
    }
    if(!temp.isEmpty())
    {
        ui->message->setWordWrap(true);
        ui->message->setAlignment(Qt::AlignTop);
        ui->message->setText("You have alread rented "+dvdname+"!");
        return;
    }

    sql_cmd.clear();
    sql_cmd="insert into history (DVDNAME,USERNAME,START,RET,MONEY) values ('"+dvdname+"','"+username+"','"+start+"','"+"0000-00-00',"+"'0')"+";";
    ba=sql_cmd.toLatin1();
    ch=ba.data();
    if(mysql_query(conn, ch))
    {
            printf("%s\n",mysql_error(conn));
            exit(1);
    }
    sql_cmd.clear();
    sql_cmd="update dvdlib set LIFT = LIFT-'1' where DVDNAME = '"+dvdname+"';";
    ba=sql_cmd.toLatin1();
    ch=ba.data();
    if(mysql_query(conn, ch))
    {
            ui->message->setText(mysql_error(conn));
    }
    ui->message->setText("Rent successed!");
    ui->Btn_show->click();
}

void dvdclient::on_Btn_EXIT_clicked()
{
    this->close();
    user.clear();
    logw->show();
}
