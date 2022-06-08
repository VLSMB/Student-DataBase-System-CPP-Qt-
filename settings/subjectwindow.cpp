#include "subjectwindow.h"
#include "ui_subjectwindow.h"
#include <QMessageBox>

SubjectWindow::SubjectWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SubjectWindow)
{
    ui->setupUi(this);
    this->setFixedSize(283,240);
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowFlags(Qt::Dialog);
    Refresh_Table(ui->tbSubject,"subject");

    QObject::connect(ui->btnDel, &QPushButton::clicked, this, &this->delete_subject);
    QObject::connect(ui->btnAdd, &QPushButton::clicked, this, &this->add_subject);
    QObject::connect(ui->btnEdit, &QPushButton::clicked, this, &this->updata_subject);
}

SubjectWindow::~SubjectWindow()
{
    delete ui;
}

void SubjectWindow::delete_subject()
{
    int row = ui->tbSubject->currentRow() + 1;
    QMessageBox::StandardButton result = QMessageBox::question(this,TITLE,
                          "是否要删除考试科目 "+ui->tbSubject->item(row-1,0)->text()+" ？");
    if (result == QMessageBox::Yes)
    {
        if (Delete_Table(ui->tbSubject, "subject", row))
            QMessageBox::information(this,TITLE,"删除成功！");
        else
            QMessageBox::critical(this,TITLE,"删除失败！");
    }
}

void SubjectWindow::updata_subject()
{
    QString KeyName, InputTitle, InputLabel;
    switch (ui->tbSubject->currentColumn())
    {
        case 0:
            KeyName = "subID";
            InputTitle = "修改学科ID";
            InputLabel = "请输入修改后的学科ID：";
        break;
        case 1:
            KeyName = "subName";
            InputTitle = "修改学科名称";
            InputLabel = "请输入修改后的学科名称：";
        break;
        default:
            KeyName = "UNKNOWN BY VLSMB";
            InputTitle = "ERROR404";
            InputLabel = "AN EXPRESSION OCCURRED...";
    }
    QString Value = QInputDialog::getText(this, InputTitle,InputLabel,QLineEdit::Normal,ui->tbSubject->currentItem()->text());
    if (Value!="")
    {
        bool status = Updata_Table(ui->tbSubject, "subject", KeyName, Value);
        if (status)
            QMessageBox::information(this, TITLE, InputTitle+"成功！");
        else
            QMessageBox::critical(this, TITLE, InputTitle+"失败！\n可能是数据库文件损坏、出现重名问题。");
    }

}

void SubjectWindow::add_subject()
{
    QString NewID = ui->editID->text();
    QString NewName = ui->editName->text();
    if (NewID=="" || NewName=="")
        QMessageBox::warning(this, TITLE, "请输入要添加的学科名称！");
    else
    {
        bool status = Add_Subject_Table(ui->tbSubject, NewID, NewName);
        if (status)
            QMessageBox::information(this, TITLE, "学科信息增加成功！");
        else
            QMessageBox::critical(this, TITLE, "学科信息增加失败！\n可能是数据库文件损坏、出现重名问题。");
    }
}

