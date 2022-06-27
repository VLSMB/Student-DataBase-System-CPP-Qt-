#ifndef DATABASE_H
#define DATABASE_H
#include <QFile>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QTableWidget>
#include <QComboBox>
#include <QStringList>
#include <QSqlRecord>

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
extern bool Add_Student_Table(QTableWidget* Table, QComboBox *classbox, QComboBox *gradebox,QString stuID, QString stuName, QString classID, QString gradeID, QString age, QString sex, QString phone,QString address);
extern bool Add_Result_Table(QTableWidget* Table, QString ID, QString stuID, QString kindID, QString subID, QString result);

extern QStringList Refresh_Grade_Table_Const(QComboBox* ComboBox);
extern QStringList Refresh_Classes_Table_Const(QComboBox* ComboBox);
extern QStringList Refresh_KindsSubject_Table_Const(QString name);
extern bool Add_Classes_Table(QTableWidget* Table,QString classID, QString gradeID, QString className);
extern void Refresh_StudentInfo_Table(QTableWidget *Table, QComboBox *Grade, QComboBox *Class);
extern void Refresh_StudentInfo_Table_INITIAL(QTableWidget *Table);
extern void Refresh_ResultInfo_Table_INITIAL(QTableWidget *Table);

extern int Get_Table_Number(QString name);
extern QStringList ComboBox_To_StringList(QComboBox *ComboBox, bool haveALL);
extern int Get_Index_By_Text(QComboBox *ComboBox, QString Text);
extern void ID_To_Name(QTableWidget *Table, QString tablename, int Col, int IDIndex, int ValueIndex);
extern void Table_To_ComboBox(QComboBox *ComboBox, QString table, int Index, bool haveall);

#endif // DATABASE_H
