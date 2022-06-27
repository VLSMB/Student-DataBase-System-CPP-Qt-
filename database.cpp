#include "database.h"
#include <QDebug>
#include <QSqlTableModel>
#include <QTableWidgetItem>
#include <QMessageBox>

QStringList ComboBox_To_StringList(QComboBox *ComboBox, bool haveALL)
{
    // 将组合框转换为字符串组，便于修改数据库，同时删除最后一个元素“所有”
    QStringList List;
    for (int index=0; index<ComboBox->count(); index++)
        List << ComboBox->itemText(index);
    if (haveALL)
        List.removeLast();
    return List;
}

int Get_Index_By_Text(QComboBox *ComboBox, QString Text)
{
    QStringList StringList = ComboBox_To_StringList(ComboBox, false);
    return StringList.indexOf(Text);
}

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
    return false;
}

bool Open_Database(){
    return db->open();
}

bool Exists_Database(){
    return QFile::exists("studentdb.db");
}

QSqlDatabase dbs = QSqlDatabase::addDatabase("QSQLITE");
QSqlDatabase* db=&dbs;

int Get_Table_Number(QString name)
{
    QSqlQuery query;
    query.exec("select * from "+name);
    query.last();
    return query.at() + 1;
}

void ID_To_Name(QTableWidget *Table, QString tablename, int Col, int IDIndex, int ValueIndex)
{
    // 将表格中的ID转换为相应的名字
    QSqlQuery query1;
    query1.exec("select * from "+tablename);
    query1.next();
    int number = Get_Table_Number(tablename);
    while (number--)
    {
        for (int row=0;row<Table->rowCount(); row++)
        {
            int compare = QString::compare(Table->item(row,Col)->text(), query1.value(IDIndex).toString());
            if (compare == 0)
                Table->item(row,Col)->setText(query1.value(ValueIndex).toString());
        }
        query1.next();
    }
}

void Table_To_ComboBox(QComboBox *ComboBox, QString table, int Index, bool haveall)
{
    QSqlQuery query1;
    query1.exec("select * from "+table);
    query1.last();
    int num = query1.at()+1;
    QSqlQuery query2;
    query2.exec("select * from "+table);
    query2.next();
    QStringList List;
    while (num--)
    {
        List << query2.value(Index).toString();
        query2.next();
    }
    if (haveall)
        List << "所有";
    ComboBox->addItems(List);
}

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

void Refresh_StudentInfo_Table_INITIAL(QTableWidget *Table)
{
    // 格式化年级和班级的数字
    Refresh_Table(Table, "student");
    ID_To_Name(Table, "grade", 3, 0, 1);
    ID_To_Name(Table, "class", 2, 0, 2);
    /*QSqlQuery query1;
    query1.exec("select * from grade");
    query1.next();
    int grade = Get_Table_Number("grade");
    while (grade--)
    {
        for (int row=0;row<Table->rowCount(); row++)
        {
            int compare = QString::compare(Table->item(row,3)->text(), query1.value(0).toString());
            if (compare == 0)
                Table->item(row,3)->setText(query1.value(1).toString());
        }
        query1.next();
    }
    QSqlQuery query2;
    query2.exec("select * from class");
    query2.next();
    int classnumber = Get_Table_Number("class");
    while (classnumber--)
    {
        for (int row=0;row<Table->rowCount(); row++)
        {
            int compare = QString::compare(Table->item(row,2)->text(), query2.value(0).toString());
            if (compare == 0)
                Table->item(row,2)->setText(query2.value(2).toString());
        }
        query2.next();
    }*/

}

void Refresh_ResultInfo_Table_INITIAL(QTableWidget *Table)
{
    for(int r = Table->rowCount() - 1;r >= 0; r--)
    {
        // 初始化表格，清空所有行
        Table->removeRow(r);
    }
    QSqlQuery query;
    int i = 0,j = 0, Col, Row;
    query.exec("select * from result");
    query.last();
    Row = query.at() + 1;
    Table->setRowCount(Row);
    Col = Table->columnCount();
    query.first();
    // 按列填数据
    for (i=0; i<Row; i++)
    {
        for (j=0; j<Col; j++)
        {
            // 每一列的情况
            switch (j)
            {
            case 0:
                Table->setItem(i, j, new QTableWidgetItem(query.value(1).toString()));
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                Table->setItem(i, j, new QTableWidgetItem(query.value(3).toString()));
                break;
            case 4:
                Table->setItem(i, j, new QTableWidgetItem(query.value(2).toString()));
                break;
            case 5:
                Table->setItem(i, j, new QTableWidgetItem(query.value(4).toString()));
                break;
            case 6:
                Table->setItem(i, j, new QTableWidgetItem(query.value(0).toString()));
                break;
            }
        }
        query.next();
    }
    // 格式化科目和种类
    ID_To_Name(Table, "subject", 3, 0, 1);
    ID_To_Name(Table, "examkinds", 4, 0, 1);

    // 通过学生ID映射学生姓名和班级
    QSqlQuery query2, query3;
    query2.exec("select * from student");
    query2.last();
    int student = query2.at()+1;
    query3.exec("select * from student");
    query3.next();
    for (int x=0; x<student; x++)
    {
        for (int y=0; y<Table->rowCount(); y++)
        {
            QString temp1 = Table->item(y,0)->text();
            QString temp2 = query3.value(0).toString();
            int compare = QString::compare(temp1, temp2);
            if (compare==0)
            {
                Table->setItem(y, 1, new QTableWidgetItem(query3.value(1).toString()));
                Table->setItem(y, 2, new QTableWidgetItem(query3.value(2).toString()));
            }
        }
        query3.next();
    }

    ID_To_Name(Table, "class", 2, 0, 2);
}

void Refresh_StudentInfo_Table(QTableWidget *Table, QComboBox *Grade, QComboBox *Class)
{
    Refresh_StudentInfo_Table_INITIAL(Table);
    for (int row=0;row<Table->rowCount();row++)
    {
        if (Table->item(row,2)->text() != Class->currentText() && Class->currentText() != "所有")
            Table->hideRow(row);
        if (Table->item(row,3)->text() != Grade->currentText() && Grade->currentText() != "所有")
            Table->hideRow(row);
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
bool Add_Student_Table(QTableWidget *Table, QComboBox *classbox, QComboBox *gradebox, QString stuID, QString stuName, QString classID, QString gradeID, QString age, QString sex, QString phone, QString address)
{
    QSqlQuery query;
    bool status = query.exec(QString("insert into student (stuID, stuName, classID, gradeID, age, sex, phone, address) values ('%0', '%1', '%2', '%3', '%4', '%5', '%6', '%7')")
                             .arg(stuID, stuName, classID, gradeID, age, sex, phone, address));
    Refresh_StudentInfo_Table(Table, gradebox, classbox);
    return status;
}
bool Add_Result_Table(QTableWidget *Table, QString ID, QString stuID, QString kindID, QString subID, QString result)
{
    QSqlQuery query;
    bool status = query.exec(QString("insert into result (ID, stuID, kindID, subID, result) values ('%0', '%1', '%2', '%3', '%4')")
                             .arg(ID, stuID, kindID, subID, result));
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

QStringList Refresh_Classes_Table_Const(QComboBox* ComboBox)
{
    // 返回一个QStringList，内容为classID，索引值与className一一对应
    QSqlQuery query;
    query.exec("select * from class");
    query.last();
    int size = query.at() + 1; // size为数据个数
    QStringList classID;
    query.first();
    for (int i=0; i<size; i++)
    {
        classID << query.value(0).toString();
        ComboBox->addItem(query.value(2).toString());
        query.next();
    }
    return classID;
}

QStringList Refresh_KindsSubject_Table_Const(QString name)
{
    // 返回一个QStringList
    QSqlQuery query;
    query.exec("select * from "+name);
    query.last();
    int size = query.at() + 1; // size为数据个数
    QStringList classID;
    query.first();
    for (int i=0; i<size; i++)
    {
        classID << query.value(0).toString();
        query.next();
    }
    return classID;
}


bool Add_Classes_Table(QTableWidget *Table, QString classID, QString gradeID, QString className)
{
    QSqlQuery query;
    bool status = query.exec("insert into class (classID, gradeID, className) values ("
                             +classID+", "+gradeID+", '"+className+"')");
    Refresh_Table(Table, "class");
    return status;
}
