#include "common.h"
#include <iostream>
#include <QString>
using namespace std;

#include <cstring>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <QDebug>
#include <mysql/mysql.h>

extern MYSQL *conn;

User::User()
{
    m_name=new char[8];
    m_password=new char[8];
    m_level=0;
    m_money=0.0;
}
User::User(char *name,char *password,int level=0,double money=0)
{
    m_name=new char[strlen(name)+1];
    memset(m_name,0,strlen(name)+1);//全部初始化为0
    strcpy(m_name,name);

    m_password=new char[strlen(password)+1];
    memset(m_password,0,strlen(password)+1);
    strcpy(m_password,password);

    m_level=level;
    m_money=money;
}

User::~User()
{
    delete[] m_name;
    delete[] m_password;
}

User::User(const User& other)
{
    delete[] m_name;
    delete[] m_password;

    m_name=new char[strlen(other.m_name)+1];
    m_password=new char[strlen(other.m_password)+1];

    memset(m_name,0,strlen(other.m_name)+1);
    memset(m_password,0,strlen(other.m_password)+1);

    strcpy(m_name,other.m_name);
    strcpy(m_password,other.m_password);

    m_level=other.m_level;
    m_money=other.m_money;
}

char *User::getName(void) const
{
    return m_name;
}

void User::setName(char *name)
{
    delete[] m_name;
    m_name=new char[strlen(name)+1];
    memset(m_name,0,strlen(name)+1);
    strcpy(m_name,name);
}

char *User::getPass(void) const
{
    return m_password;
}
void User::setPass(char *password)
{
    delete[] m_password;
    m_password=new char[strlen(password)+1];
    memset(m_password,0,strlen(password)+1);
    strcpy(m_password,password);
}

int User::getLevel(void)const
{
    return m_level;
}
void User::setLevel(int level)
{
    m_level=level;
}

double User::getMoney(void)const
{
    return m_money;
}
void User::setMoney(double money)
{
    m_money=money;
}


void User::clear(void)
{
    delete[] m_name;
    m_name= new char[1];
    delete[] m_password;
    m_password= new char[1];
    m_level=0;
    m_money=0;
}

DVD::DVD()
{
    m_name=new char[1];
    *m_name='\0';
    m_picfp=new char[1];
    *m_picfp='\0';
    m_price=0;
    m_left=0;
}

 DVD::DVD(char *name,char *picfp,int price,int left)
 {
    m_name=new char[strlen(name)+1];
    memset(m_name,0,strlen(name)+1);
    strcpy(m_name,name);

    m_picfp=new char[strlen(picfp)+1];
    memset(m_picfp,0,strlen(picfp)+1);
    strcpy(m_picfp,picfp);

    m_price=price;
    m_left=left;
 }

 DVD::~DVD()
 {
     delete[] m_name;
     delete[] m_picfp;
 }

 DVD::DVD(const DVD& other)
 {
     /*delete[] m_name;
     delete[] m_picfp;*/
     m_name=new char[strlen(other.m_name)+1];
     memset(m_name,0,strlen(other.m_name)+1);
     strcpy(m_name,other.m_name);

     m_picfp=new char[strlen(other.m_picfp)+1];
     memset(m_picfp,0,strlen(other.m_picfp)+1);
     strcpy(m_picfp,other.m_picfp);

     m_price=other.m_price;
     m_left=other.m_left;
 }

 char *DVD::getName(void)const
 {
     return m_name;
 }
 void DVD::setName(char *name)
 {
     delete[] m_name;
     m_name=new char[strlen(name)+1];
     memset(m_name,0,strlen(name)+1);
     strcpy(m_name,name);
 }

 char *DVD::getPic(void)const
 {
     return m_picfp;
 }
 void DVD::setPic(char *picfp)
 {
     delete[] m_picfp;
     m_picfp=new char[strlen(picfp)+1];
     memset(m_picfp,0,strlen(picfp)+1);
     strcpy(m_picfp,picfp);
 }

 int DVD::getPrice(void)const
 {
     return m_price;
 }
 void DVD::setPrice(int price)
 {
     m_price=price;
 }

 int DVD::getLeft(void)const
 {
     return m_left;
 }
 void DVD::setLeft(int left)
 {
     m_left=left;
 }


 bool operator<(const DVD& self,const DVD& other)
 {
     QString count_self;
     QString count_other;
     QString sql_cmd="select count(*) from history where DVDNAME= '"+QString(QLatin1String(self.m_name))+"';";
     MYSQL_RES *res = NULL;
     MYSQL_ROW row = NULL;
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
         count_self=row[0];
     }

     sql_cmd="select count(*) from history where DVDNAME= '"+QString(QLatin1String(other.m_name))+"';";
     ba = sql_cmd.toLatin1();
      ch=ba.data();
      if(mysql_query(conn, ch))
      {
              printf("%s\n",mysql_error(conn));
              exit(1);
      }

      res = mysql_use_result(conn);
      while ((row = mysql_fetch_row(res)) != NULL)
      {
          count_other=row[0];
      }
      return (count_self.toInt()<count_other.toInt());
 }


 DATETIME::DATETIME()
 {
     time_t rawtime;
     struct tm * timeinfo;
     time ( &rawtime );
     timeinfo = localtime ( &rawtime );

     m_year = 1900+timeinfo->tm_year;
     m_month = 1+timeinfo->tm_mon;
     m_day = timeinfo->tm_mday;
 }
 DATETIME::DATETIME(int year, int month, int day)
    :m_year(year),m_month(month),m_day(day)
 {
 }
 DATETIME::~DATETIME()
 {
 }

 int DATETIME::getYear(void)const
 {
     return m_year;
 }
 void DATETIME::setYear(int year)
 {
     m_year=year;
 }

 int DATETIME::getMonth(void)const
 {
     return m_month;
 }
 void DATETIME::setMonth(int month)
 {
     m_month=month;
 }

 int DATETIME::getDay(void)const
 {
     return m_day;
 }
 void DATETIME::setDay(int day)
 {
     m_day=day;
 }

 bool DATETIME::isleapyear(int year)
         {
                 if((year%4==0))
                 {
                         return true;
                 }
                 else
                 {
                         return false;
                 }
         }
         DATETIME& DATETIME::operator+=(int day)
         {
             while(day)
             {
                 m_day+=1;
                 this->correcting();
                 day-=1;
             }
             return *this;
         }

        bool DATETIME::isempty(void)
        {
            if((m_year==0)||(m_month==0)||(m_day==0))
            {
                return true;
            }
            return false;
        }
         void DATETIME::chartodate(const char *date)
         {
             char *datecpy=new char[strlen(date+1)];
             strcpy(datecpy,date);
             char *p=datecpy;
             char *temp=p;
             while((*p)!='-')
             {
                 p++;
             }
             *p='\0';
             m_year=atoi(temp);
             p++;
             temp=p;

             while((*p)!='-')
             {
                 p++;
             }
             *p='\0';
            m_month=atoi(temp);
            p++;
            m_day=atoi(p);
            delete[] datecpy;
         }

          char *DATETIME::datetochar(void)const
          {
              char temp[8]={};
              sprintf(temp,"%d",m_year);
              QString year=temp;
              sprintf(temp,"%d",m_month);
              QString month=temp;
              sprintf(temp,"%d",m_day);
              QString day=temp;
              QString date=year+'-'+month+'-'+day+'\0';
              char*  ch=NULL;
              QByteArray ba = date.toLatin1();
              ch=ba.data();
              return ch;
          }


 void DATETIME::correcting()
{
     if((m_month==1)||(m_month==3)||(m_month==5)||(m_month==7)||(m_month==8)
                  ||(m_month==10)||m_month==12)
     {
     if(m_day>31)
     {
        m_day-=31;
        m_month+=1;
     }
     else if(m_month!=2)
                 {
                     if(m_day>30)
                     {
                         m_day-=30;
                         m_month+=1;
                     }
                 }
                 else
                 {
                     if(isleapyear(m_year))
                     {
                         if(m_day>29)
                         {
                             m_day-=29;
                             m_month+=1;
                         }
                     }
                     else
                     {
                         if(m_day>28)
                         {
                             m_day-=28;
                             m_month+=1;
                         }
                     }
                 }
                 if(m_month>12)
                 {
                     m_month-=12;
                     m_year+=1;
                 }
     }
 }
int DATETIME::operator -(DATETIME& other)
{
    int year=m_year-other.m_year;
    int month=m_month-other.m_month;
    int day=m_day-other.m_day;
    qDebug()<<"m_day:"<<m_day<<"other.m_day:"<<other.m_day<<endl;
    qDebug()<<"year:"<<year<<"month"<<month<<"day"<<day<<endl;
    if(day<0)
    {
        month-=1;
        day+=30;
    }
    if(month<0)
    {
        year-=1;
        month+=12;
    }
    return (year*365+month*30+day);
}

 History::History(char* dvdname,char*usrname,DATETIME start,DATETIME ret,double money)
 {
     m_dvdname=new char[strlen(dvdname)+1];
     memset(m_dvdname,0,strlen(dvdname)+1);
     strcpy(m_dvdname,dvdname);

     m_usrname=new char[strlen(usrname)+1];
     memset(m_usrname,0,strlen(usrname)+1);
     strcpy(m_usrname,usrname);

     m_start=start;
     m_ret=ret;
     m_money=money;

 }
 History::~History()
 {
    delete[] m_dvdname;
    delete[] m_usrname;
 }
 History::History(const History& other)
 {
    //setDvdname(other.m_dvdname);
     m_dvdname=new char[strlen(other.m_dvdname)+1];
     memset(m_dvdname,0,strlen(other.m_dvdname)+1);
     strcpy(m_dvdname,other.m_dvdname);

     m_usrname=new char[strlen(other.m_usrname)+1];
     memset(m_usrname,0,strlen(other.m_usrname)+1);
     strcpy(m_usrname,other.m_usrname);


    //setUsrname(other.m_usrname);
    m_start=other.m_start;
    m_ret=other.m_ret;
    m_money=other.m_money;
 }

 char *History::History::getDvdname(void)const
 {
    return m_dvdname;
 }
 void History::setDvdname(char *dvdname)
 {
     delete[] m_dvdname;
     m_dvdname=new char[strlen(dvdname)+1];
     memset(m_dvdname,0,strlen(dvdname)+1);
     strcpy(m_dvdname,dvdname);
 }

 char *History::getUsrname(void)const
 {
    return m_usrname;
 }
 void History::setUsrname(char *usrname)
 {
     delete[] m_usrname;
     m_usrname=new char[strlen(usrname)+1];
     memset(m_usrname,0,strlen(usrname)+1);
     strcpy(m_usrname,usrname);
 }

 DATETIME History::getStart(void)const
 {
     return m_start;
 }
 void History::setStart(DATETIME& start)
 {
     m_start=start;
 }

 DATETIME History::getRet(void)const
 {
     return m_ret;
 }
 void History::setRet(DATETIME& ret)
 {
     m_ret=ret;
 }
 double History::getMoney(void)const
 {
     return m_money;
 }
 void History::setMoney(double money)
 {
     m_money=money;
 }
