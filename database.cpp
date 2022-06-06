#include "database.h"
#include <QDebug>

bool Find_User_login(QString user,QString pwd){
    QSqlQuery query;
    query.exec(QString(R"(SELECT userPwd FROM admin WHERE userName='%1';)").arg(user));
    QString Value;
    if(query.next())
        Value=query.value(0).toString();
    if (Value=="" || Value!=pwd)
        return false;
    else if (Value==pwd)
        return true;
}

bool Open_Database(){
    return db->open();
}

bool Exists_Database(){
    return QFile::exists("studentdb.db");
}

QSqlDatabase dbs = QSqlDatabase::addDatabase("QSQLITE");
QSqlDatabase* db=&dbs;
