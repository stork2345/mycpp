
#include "logwindow.h"
#include "common.h"
#include <QApplication>

#include <iostream>
#include <string>
#include <mysql/mysql.h>
#include <cstdio>
using namespace std;

MYSQL *conn;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   char server[] = "localhost";
   char user[] = "root";
   char password[] = "123456";
   char database[] = "dvdlib";

    conn = mysql_init(NULL);

            if (!mysql_real_connect(conn, server,user, password, database, 0, NULL, 0))
            {
                    fprintf(stderr, "%s\n", mysql_error(conn));
                    exit(1);
            }



    logwindow login;

    login.show();


    return a.exec();
}
