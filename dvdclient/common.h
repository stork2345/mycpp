#ifndef COMMON_H
#define COMMON_H



class User
{
public:
    User();
    User(char *name,char *password,int level,double money);
    ~User();
    User(const User&);

    char *getName(void) const;
    void setName(char *name);

    char *getPass(void) const;
    void setPass(char *password);

    int getLevel(void)const;
    void setLevel(int level);

    double getMoney(void)const;
    void setMoney(double money);

private:
    char *m_name;
    char *m_password;
    int m_level;
    double m_money;
};

class DVD
{
public:
    DVD(char *name,char *picfp,int price=0,int left=0);
    ~DVD();
    DVD(const DVD&);

    char *getName(void)const;
    void setName(char *name);

    char *getPic(void)const;
    void setPic(char *picfp);

    int getPrice(void)const;
    void setPrice(int price);

    int getLeft(void)const;
    void setLeft(int left);

private:
    char *m_name;
    char *m_picfp;
    int m_price;
    int  m_left;
};
class DATETIME
{
public:
    DATETIME();
    DATETIME(int year,int month,int day);
    ~DATETIME();
    int getYear(void)const;
    void setYear(int year);

    int getMonth(void)const;
    void setMonth(int month);

    int getDay(void)const;
    void setDay(int day);

    DATETIME& operator+=(int day);
    bool isleapyear(int year);
    void correcting(void);
    void chartodate(const char *date);
    char *datetochar(void)const;

private:
    int m_year;
    int m_month;
    int m_day;
};
class History
{
public:
    History(char* dvdname,char*usrname,DATETIME start,DATETIME ret,double money);
    ~History();
    History(const History&);

    char *getDvdname(void)const;
    void setDvdname(char *dvdname);

    char *getUsrname(void)const;
    void setUsrname(char *usrname);

    DATETIME getStart(void)const;
    void setStart(DATETIME& start);

    DATETIME getRet(void)const;
    void setRet(DATETIME& ret);

    double getMoney(void)const;
    void setMoney(double money);



private:
    char *m_dvdname;
    char *m_usrname;
    DATETIME m_start;
    DATETIME m_ret;
    double m_money;
};




#endif // COMMON_H
