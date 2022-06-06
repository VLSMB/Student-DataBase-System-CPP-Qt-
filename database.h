#ifndef DATABASE_H
#define DATABASE_H
#include <QFile>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>


extern bool Find_User_login(QString user,QString pwd);
extern bool Open_Database();
extern bool Exists_Database();
extern QSqlDatabase *db;


#endif // DATABASE_H
