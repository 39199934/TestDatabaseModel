#ifndef MYSQL_H
#define MYSQL_H
#include <QSql>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QSqlResult>
#include <iostream>
#include <QSqlTableModel>
#include <QBuffer>
#include <QWidget>
#include <QSqlQueryModel>
//#include "ShowImage.h"
using namespace std;
//#pragma comment(lib,"libmysql")
class MySql
{
public:
    MySql();
    virtual ~MySql();
    void viewTable();
    void insert();
    QSqlQueryModel* getModel();
    //QVector<QString> getDescription();
   // QSqlTableModel* getModel();
private:
    QString hostName;
    QString dbName;
    QString userName;
    QString password;
    int port;
    QSqlDatabase dbConn;
    QSqlQueryModel* model;
   // ShowImage* show;
};

#endif // MYSQL_H
