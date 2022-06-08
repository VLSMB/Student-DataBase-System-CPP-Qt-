#include "classeswindow.h"
#include "ui_classeswindow.h"
#include <QMessageBox>

ClassesWindow::ClassesWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClassesWindow)
{
    ui->setupUi(this);
    this->setFixedSize(307,267);
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowFlags(Qt::Dialog);
    Refresh_Table(ui->tbClass,"class");
    this->gradeID = Refresh_Grade_Table_Const(ui->cboxGrade);

    QObject::connect(ui->btnDel, &QPushButton::clicked, this, &this->delete_classes);
    QObject::connect(ui->btnAdd, &QPushButton::clicked, this, &this->add_classes);
    QObject::connect(ui->btnEdit, &QPushButton::clicked, this, &this->updata_classes);
}

ClassesWindow::~ClassesWindow()
{
    delete ui;
}


void ClassesWindow::delete_classes()
{
    int row = ui->tbClass->currentRow() + 1;
    QMessageBox::StandardButton result = QMessageBox::question(this,TITLE,
                          "是否要删除班级 "+ui->tbClass->item(row-1,0)->text()+" ？");
    if (result == QMessageBox::Yes)
    {
        if (Delete_Table(ui->tbClass, "class", row))
            QMessageBox::information(this,TITLE,"删除成功！");
        else
            QMessageBox::critical(this,TITLE,"删除失败！");
    }
}

void ClassesWindow::updata_classes()
{
    QString KeyName, InputTitle, InputLabel;
    switch (ui->tbClass->currentColumn())
    {
        case 0:
            KeyName = "classID";
            InputTitle = "修改班级ID";
            InputLabel = "请输入修改后的班级ID：";
        break;
        case 1:
            KeyName = "gradeID";
            InputTitle = "修改年级ID";
            InputLabel = "请输入修改后的年级ID：";
        break;
        case 2:
            KeyName = "className";
            InputTitle = "修改班级名称";
            InputLabel = "请输入修改后的班级名称：";
        break;
        default:
            KeyName = "UNKNOWN BY VLSMB";
            InputTitle = "ERROR404";
            InputLabel = "AN EXPRESSION OCCURRED...";
    }
    QString Value = QInputDialog::getText(this, InputTitle,InputLabel,QLineEdit::Normal,ui->tbClass->currentItem()->text());
    if (Value!="")
    {
        bool status = Updata_Table(ui->tbClass, "class", KeyName, Value);
        if (status)
            QMessageBox::information(this, TITLE, InputTitle+"成功！");
        else
            QMessageBox::critical(this, TITLE, InputTitle+"失败！\n可能是数据库文件损坏、出现重名问题。");
    }

}

void ClassesWindow::add_classes()
{
    QString classID = ui->editID->text();
    QString className = ui->editName->text();
    if (classID=="" || className=="")
        QMessageBox::warning(this, TITLE, "请输入要添加的班级信息！");
    else
    {
        bool status = Add_Classes_Table(ui->tbClass, classID,gradeID[ui->cboxGrade->currentIndex()], className);
        if (status)
            QMessageBox::information(this, TITLE, "班级信息增加成功！");
        else
            QMessageBox::critical(this, TITLE, "班级信息增加失败！\n可能是数据库文件损坏、出现重名问题。");
    }
}
