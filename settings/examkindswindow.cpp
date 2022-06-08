#include "examkindswindow.h"
#include "ui_examkindswindow.h"
#include <QMessageBox>

ExamkindsWindow::ExamkindsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ExamkindsWindow)
{
    ui->setupUi(this);
    this->setFixedSize(286,237);
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowFlags(Qt::Dialog);

    Refresh_Table(ui->tbKinds,"examkinds");

    QObject::connect(ui->btnDel, &QPushButton::clicked, this, &this->delete_kind);
    QObject::connect(ui->btnAdd, &QPushButton::clicked, this, &this->add_kind);
    QObject::connect(ui->btnEdit, &QPushButton::clicked, this, &this->updata_kind);
}

ExamkindsWindow::~ExamkindsWindow()
{
    delete ui;
}

void ExamkindsWindow::delete_kind()
{
    int row = ui->tbKinds->currentRow() + 1;
    QMessageBox::StandardButton result = QMessageBox::question(this,TITLE,
                          "是否要删除考试 "+ui->tbKinds->item(row-1,0)->text()+" ？");
    if (result == QMessageBox::Yes)
    {
        if (Delete_Table(ui->tbKinds, "examkinds", row))
            QMessageBox::information(this,TITLE,"删除成功！");
        else
            QMessageBox::critical(this,TITLE,"删除失败！");
    }
}

void ExamkindsWindow::updata_kind()
{
    QString KeyName, InputTitle, InputLabel;
    switch (ui->tbKinds->currentColumn())
    {
        case 0:
            KeyName = "kindID";
            InputTitle = "修改考试ID";
            InputLabel = "请输入修改后的考试ID：";
        break;
        case 1:
            KeyName = "kindName";
            InputTitle = "修改考试名称";
            InputLabel = "请输入修改后的考试名称：";
        break;
        default:
            KeyName = "UNKNOWN BY VLSMB";
            InputTitle = "ERROR404";
            InputLabel = "AN EXPRESSION OCCURRED...";
    }
    QString Value = QInputDialog::getText(this, InputTitle,InputLabel,QLineEdit::Normal,ui->tbKinds->currentItem()->text());
    if (Value!="")
    {
        bool status = Updata_Table(ui->tbKinds, "examkinds", KeyName, Value);
        if (status)
            QMessageBox::information(this, TITLE, InputTitle+"成功！");
        else
            QMessageBox::critical(this, TITLE, InputTitle+"失败！\n可能是数据库文件损坏、出现重名问题。");
    }

}

void ExamkindsWindow::add_kind()
{
    QString NewID = ui->editID->text();
    QString NewName = ui->editName->text();
    if (NewID=="" || NewName=="")
        QMessageBox::warning(this, TITLE, "请输入要添加的考试名称！");
    else
    {
        bool status = Add_Examkinds_Table(ui->tbKinds, NewID, NewName);
        if (status)
            QMessageBox::information(this, TITLE, "考试信息增加成功！");
        else
            QMessageBox::critical(this, TITLE, "考试信息增加失败！\n可能是数据库文件损坏、出现重名问题。");
    }
}
