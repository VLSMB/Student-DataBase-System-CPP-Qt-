#include "mainwindow.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include <QFile>
#include "database.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(350,257);
    db->setDatabaseName("studentdb.db");
    bool ok = Open_Database();
    bool dbFile = Exists_Database();
    if (!ok || !dbFile){
        QMessageBox::critical(NULL,TITLE,"数据库连接失败！");
        if (!dbFile){
            db->close();
            QFile fileTemp("studentdb.db");
            fileTemp.remove();
        }
        a.exit(1);
    }
    w.show();

    return a.exec();
}
