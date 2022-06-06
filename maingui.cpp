#include "maingui.h"
#include "ui_MainGui.h"
#include <QLabel>
#include <QMessageBox>
#include <QTime>
#include <QDate>
#include <QAction>

MainGui::MainGui(QString NowUser,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainGui)
{
    ui->setupUi(this);
    QLabel* UserInfo = new QLabel;
    UserInfo->setText("当前用户：" + NowUser);
    ui->statusbar->addWidget(UserInfo);
    QLabel* TimeInfo = new QLabel;
    QTime time = QTime::currentTime();
    QDate date = QDate::currentDate();
    TimeInfo->setText("登陆时间：" + date.toString("yyyy-MM-dd") + " " + time.toString("hh:mm:ss"));
    ui->statusbar->addWidget(TimeInfo);
    QLabel* ComposedInfo = new QLabel;
    ComposedInfo->setText("COMPOSED BY VLSMB");
    ui->statusbar->addWidget(ComposedInfo);

    QObject::connect(ui->action_9,&QAction::triggered,this,&this->open_userWindow);
    QObject::connect(ui->action_5,&QAction::triggered,this,&this->open_studentWindow);
    QObject::connect(ui->action_6,&QAction::triggered,this,&this->open_resultWindow);
    QObject::connect(ui->action_7,&QAction::triggered,this,&this->open_studentinfo);
    QObject::connect(ui->action_8,&QAction::triggered,this,&this->open_resultinfo);

    QObject::connect(ui->action,&QAction::triggered,this,&this->open_grade);
    QObject::connect(ui->action_2,&QAction::triggered,this,&this->open_classes);
    QObject::connect(ui->action_3,&QAction::triggered,this,&this->open_subject);
    QObject::connect(ui->action_4,&QAction::triggered,this,&this->open_examkinds);

}

MainGui::~MainGui()
{
    delete ui;
}

void MainGui::open_userWindow()
{
    UserWindowInfo = new UserWindow(this);
    UserWindowInfo->show();
}
void MainGui::open_studentWindow()
{
    Student = new StudentWindow(this);
    Student->show();
}
void MainGui::open_resultWindow()
{
    Result = new ResultWindow(this);
    Result->show();
}
void MainGui::open_resultinfo()
{
    ResultInfo = new ResultInfoWindow(this);
    ResultInfo->show();
}
void MainGui::open_studentinfo()
{
    StudentInfo = new StudentInfoWindow(this);
    StudentInfo->show();
}
void MainGui::open_classes()
{
    Classes = new ClassesWindow;
    Classes->show();
}
void MainGui::open_examkinds()
{
    Examkinds = new ExamkindsWindow;
    Examkinds->show();
}
void MainGui::open_grade()
{
    Grade = new GradeWindow;
    Grade->show();
}
void MainGui::open_subject()
{
    Subject = new SubjectWindow;
    Subject->show();
}
