#include "database.h"
#include <QDebug>
#include <QSqlTableModel>
#include <QTableWidgetItem>
#include <QMessageBox>

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

void Refresh_Table(QTableWidget *Table, QString Name)
{
    for(int r = Table->rowCount() - 1;r >= 0; r--)
    {
        // 初始化表格，清空所有行
        Table->removeRow(r);
    }
    QSqlQuery query;
    int i = 0,j = 0, Col, Row;
    query.exec("select * from " + Name);
    query.last();
    Row = query.at() + 1;
    Table->setRowCount(Row);
    Col = Table->columnCount();
    query.first();
    while (j < Row)
    {
        // 读取数据库，显示所有行
        for (i=0; i<Col; i++)
            Table->setItem(j, i, new QTableWidgetItem(query.value(i).toString()));
        j++;
        query.next();
    }
}

bool Delete_Table(QTableWidget *Table, QString TableName, int RowID)
{
    QSqlQuery query;
    bool status = query.exec("delete from "+TableName+QString(" where rowid=%1").arg(RowID));
    Refresh_Table(Table, TableName);
    return status;
}

bool Add_User_Table(QTableWidget *Table, QString NewUser, QString NewPwd)
{
    QSqlQuery query;
    bool status = query.exec("insert into admin (userName, userPwd) values ('"+NewUser+"', '"+NewPwd+"')");
    Refresh_Table(Table, "admin");
    return status;
}
bool Add_Grade_Table(QTableWidget *Table, QString NewID, QString NewName)
{
    QSqlQuery query;
    bool status = query.exec("insert into grade (gradeID, gradeName) values ('"+NewID+"', '"+NewName+"')");
    Refresh_Table(Table, "grade");
    return status;
}
bool Add_Subject_Table(QTableWidget *Table, QString NewID, QString NewName)
{
    QSqlQuery query;
    bool status = query.exec("insert into subject (subID, subName) values ('"+NewID+"', '"+NewName+"')");
    Refresh_Table(Table, "subject");
    return status;
}
bool Add_Examkinds_Table(QTableWidget *Table, QString NewID, QString NewName)
{
    QSqlQuery query;
    bool status = query.exec("insert into examkinds (kindID, kindName) values ('"+NewID+"', '"+NewName+"')");
    Refresh_Table(Table, "examkinds");
    return status;
}

bool Updata_Table(QTableWidget *Table, QString TableName, QString KeyName, QString Value)
{
    QSqlQuery query;
    bool status = query.exec("UPDATE \"main\".\""+TableName+"\" SET \""+KeyName+"\" = '"
                                             +Value+QString("' WHERE rowid = %1").arg(Table->currentRow()+1));
    Refresh_Table(Table, TableName);
    return status;
}

QStringList Refresh_Grade_Table_Const(QComboBox *ComboBox)
{
    // 返回一个QStringList，内容为gradeID，索引值与gradeName一一对应
    QSqlQuery query;
    query.exec("select * from grade");
    query.last();
    int size = query.at() + 1; // size为数据个数
    QStringList gradeID;
    query.first();
    for (int i=0; i<size; i++)
    {
        gradeID << query.value(0).toString();
        ComboBox->addItem(query.value(1).toString());
        query.next();
    }
    return gradeID;
}

bool Add_Classes_Table(QTableWidget *Table, QString classID, QString gradeID, QString className)
{
    QSqlQuery query;
    bool status = query.exec("insert into class (classID, gradeID, className) values ("
                             +classID+", "+gradeID+", '"+className+"')");
    Refresh_Table(Table, "class");
    return status;
}
