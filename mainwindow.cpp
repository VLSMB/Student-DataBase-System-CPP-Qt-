#include "mainwindow.h"
#include "ui_main.h"
#include<QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QVariant>
#include "database.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->ConfirmButton,&QPushButton::clicked,this,&this->login);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::login(){
    QString user = ui->UserEdit->text();
    QString pwd = ui->PassEdit->text();
    if (user==""||pwd=="")
        QMessageBox::information(this,TITLE,"请输入用户名和密码");
    else
    {
    if (Find_User_login(user,pwd))
    {
        // QMessageBox::information(this,TITLE,"登陆成功！");
        this->hide();
        MainGuiWindow = new MainGui(user,0);
        MainGuiWindow->show();
    }
    else
        QMessageBox::critical(this,TITLE,"用户名或密码错误！");
    }
}
