#ifndef DATABASE_H
#define DATABASE_H
#include <QFile>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QTableWidget>
#include <QComboBox>
#include <QStringList>

extern bool Find_User_login(QString user,QString pwd);
extern bool Open_Database();
extern bool Exists_Database();
extern QSqlDatabase *db;
extern void Refresh_Table(QTableWidget *Table, QString Name);
extern bool Delete_Table(QTableWidget *Table, QString TableName, int RowID);
extern bool Add_User_Table(QTableWidget* Table, QString NewUser, QString NewPwd);
extern bool Updata_Table(QTableWidget* Table, QString TableName, QString KeyName, QString Value);
extern bool Add_Grade_Table(QTableWidget* Table, QString NewID, QString NewName);
extern bool Add_Subject_Table(QTableWidget* Table, QString NewID, QString NewName);
extern bool Add_Examkinds_Table(QTableWidget* Table, QString NewID, QString NewName);

extern QStringList Refresh_Grade_Table_Const(QComboBox* ComboBox);
extern bool Add_Classes_Table(QTableWidget* Table,QString classID, QString gradeID, QString className);

#endif // DATABASE_H
