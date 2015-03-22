#include "logwindow.h"
#include "dvdclient.h"
#include "ui_logwindow.h"

#include <QtGui>
#include <QDebug>

User user;

logwindow::logwindow(QWidget *parent)
    :QDialog(parent),
    ui(new Ui::logwindow)
{
    ui->setupUi(this);
    ui->Passline->setEchoMode(QLineEdit::Password);
}

logwindow::~logwindow()
{
    delete ui;
}



void logwindow::on_Btn_signin_clicked()
{

        QString name=ui->Nameline->text();
        QString pass = ui->Passline->text();
        MYSQL_RES *res = NULL;
        MYSQL_ROW row = NULL;
        int flag=0;
       if(name.isEmpty())
       {
            ui->massage->setText("The user name cannot be empty!");
        }
       else if((name.length()<=4)&&(name.length()>24))
       {
            ui->massage->setText("The user name length \n must in 4~24! ");
       }
       else if((pass.length()<6)&&(pass.length()>24))
       {
           ui->massage->setText("The password length\n must in 6~24!");
       }
       else
       {
           QString sql_cmd = "select * from users where (NAME,PASSWORD) =  ('"+name+"','"+pass+"');";
           //  qDebug() << "sqlcmd" << sql_cmd <<endl;
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
                //qDebug() << "row[1]:" << row[1] <<"row[2]:"<<row[2]<<"row[3]:"<<row[3]<<"row[4]"<<row[4]<<endl;
                user.setName(row[1]);
                user.setPass(row[2]);
                user.setLevel(atoi(row[3]));
                user.setMoney(atof(row[4]));
                flag=1;
           }

           if(flag==1)
           {
                flag=0;
                dvdclient *mainwindow=new dvdclient;
                mainwindow->show();
                mainwindow->move((QApplication::desktop()->width() - mainwindow->width())/2,(QApplication::desktop()->height() - mainwindow->height())/2);
                mainwindow->setFocus();
                this->close();
           }
           else
           {
                ui->massage->setText("username / password error!");
           }

       }
}


void logwindow::on_Btn_cancel_clicked()
{
    exit(0);
}



void logwindow::on_Btn_reg_clicked()
{
    MYSQL_RES *res = NULL;
    MYSQL_ROW row = NULL;
    QString name=ui->Nameline->text();
    QString pass = ui->Passline->text();
    int flag=0;

   if(name.isEmpty())
   {
        ui->massage->setText("The user name cannot be empty!");
    }
   else if((name.length()<=4)&&(name.length()>24))
   {
        ui->massage->setText("The user name length \n must in 4~24! ");
   }
   else if((pass.length()<6)&&(pass.length()>24))
   {
       ui->massage->setText("The password length\n must in 6~24!");
   }
   else
   {
       QString sql_cmd = "select * from users where NAME = '"+name+"';";
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
                flag=1;
           }
           mysql_free_result(res);
           if(flag==1)
           {
                   ui->massage->setText("The user name has been registed!");
           }
           else
           {
                sql_cmd.clear();
                sql_cmd="insert into users (NAME,PASSWORD,LEVEL,MONEY) value('"+name+"','"+pass+"','"+'0'+"','"+'0'+"');";
                ba.clear();
                ba = sql_cmd.toLatin1();
                ch=ba.data();

                if(mysql_query(conn, ch))
                {
                        printf("%s\n",mysql_error(conn));
                        exit(1);
                }
                    res = mysql_use_result(conn);
                    ui->massage->setText("regist success!");
           }
           flag=0;
   }

}
