#include "gradewindow.h"
#include "ui_gradewindow.h"
#include <QMessageBox>

GradeWindow::GradeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GradeWindow)
{
    ui->setupUi(this);
    this->setFixedSize(283,241);
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowFlags(Qt::Dialog);
    Refresh_Table(ui->tbGrade,"grade");

    QObject::connect(ui->btnDel, &QPushButton::clicked, this, &this->delete_grade);
    QObject::connect(ui->btnAdd, &QPushButton::clicked, this, &this->add_grade);
    QObject::connect(ui->btnEdit, &QPushButton::clicked, this, &this->updata_grade);
}

GradeWindow::~GradeWindow()
{
    delete ui;
}

void GradeWindow::delete_grade()
{
    int row = ui->tbGrade->currentRow() + 1;
    QMessageBox::StandardButton result = QMessageBox::question(this,TITLE,
                          "是否要删除年级 "+ui->tbGrade->item(row-1,0)->text()+" ？");
    if (result == QMessageBox::Yes)
    {
        if (Delete_Table(ui->tbGrade, "grade", row))
            QMessageBox::information(this,TITLE,"删除成功！");
        else
            QMessageBox::critical(this,TITLE,"删除失败！");
    }
}

void GradeWindow::updata_grade()
{
    QString KeyName, InputTitle, InputLabel;
    switch (ui->tbGrade->currentColumn())
    {
        case 0:
            KeyName = "gradeID";
            InputTitle = "修改年级ID";
            InputLabel = "请输入修改后的年级ID：";
        break;
        case 1:
            KeyName = "gradeName";
            InputTitle = "修改年级名称";
            InputLabel = "请输入修改后的年级名称：";
        break;
        default:
            KeyName = "UNKNOWN BY VLSMB";
            InputTitle = "ERROR404";
            InputLabel = "AN EXPRESSION OCCURRED...";
    }
    QString Value = QInputDialog::getText(this, InputTitle,InputLabel,QLineEdit::Normal,ui->tbGrade->currentItem()->text());
    if (Value!="")
    {
        bool status = Updata_Table(ui->tbGrade, "grade", KeyName, Value);
        if (status)
            QMessageBox::information(this, TITLE, InputTitle+"成功！");
        else
            QMessageBox::critical(this, TITLE, InputTitle+"失败！\n可能是数据库文件损坏、出现重名问题。");
    }

}

void GradeWindow::add_grade()
{
    QString NewID = ui->editID->text();
    QString NewName = ui->editName->text();
    if (NewID=="" || NewName=="")
        QMessageBox::warning(this, TITLE, "请输入要添加的年级名称！");
    else
    {
        bool status = Add_Grade_Table(ui->tbGrade, NewID, NewName);
        if (status)
            QMessageBox::information(this, TITLE, "年级信息增加成功！");
        else
            QMessageBox::critical(this, TITLE, "年级信息增加失败！\n可能是数据库文件损坏、出现重名问题。");
    }
}
