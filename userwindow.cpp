#include "userwindow.h"
#include "ui_userwindow.h"
#include <QMessageBox>

UserWindow::UserWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserWindow)
{
    ui->setupUi(this);
    this->setFixedSize(283,240);
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowFlags(Qt::Dialog);
    Refresh_Table(ui->tbUser,"admin");

    QObject::connect(ui->btnDel, &QPushButton::clicked, this, &this->delete_user);
    QObject::connect(ui->btnAdd, &QPushButton::clicked, this, &this->add_user);
    QObject::connect(ui->btnEdit, &QPushButton::clicked, this, &this->updata_user);

}

UserWindow::~UserWindow()
{
    delete ui;
}

void UserWindow::delete_user()
{
    int row = ui->tbUser->currentRow() + 1;
    QMessageBox::StandardButton result = QMessageBox::question(this,TITLE,
                          "是否要删除用户 "+ui->tbUser->item(row-1,0)->text()+" ？");
    if (result == QMessageBox::Yes)
    {
        if (Delete_Table(ui->tbUser, "admin", row))
            QMessageBox::information(this,TITLE,"删除成功！");
        else
            QMessageBox::critical(this,TITLE,"删除失败！");
    }
}

void UserWindow::add_user()
{
    QString NewUser = ui->editName->text();
    QString NewPwd = ui->editPwd->text();
    if (NewUser=="" || NewPwd=="")
        QMessageBox::warning(this, TITLE, "请输入要添加的用户名和密码！");
    else
    {
        bool status = Add_User_Table(ui->tbUser, NewUser, NewPwd);
        if (status)
            QMessageBox::information(this, TITLE, "用户信息增加成功！");
        else
            QMessageBox::critical(this, TITLE, "用户信息增加失败！\n可能是数据库文件损坏、出现重名问题。");
    }
}

void UserWindow::updata_user()
{
    QString KeyName, InputTitle, InputLabel;
    switch (ui->tbUser->currentColumn())
    {
        case 0:
            KeyName = "userName";
            InputTitle = "修改用户名";
            InputLabel = "请输入修改后的用户名：";
        break;
        case 1:
            KeyName = "userPwd";
            InputTitle = "修改密码";
            InputLabel = "请输入修改后的密码：";
        break;
        default:
            KeyName = "UNKNOWN BY VLSMB";
            InputTitle = "ERROR404";
            InputLabel = "AN EXPRESSION OCCURRED...";
    }
    QString Value = QInputDialog::getText(this, InputTitle,InputLabel,QLineEdit::Normal,ui->tbUser->currentItem()->text());
    if (Value!="")
    {
        bool status = Updata_Table(ui->tbUser, "admin", KeyName, Value);
        if (status)
            QMessageBox::information(this, TITLE, InputTitle+"成功！");
        else
            QMessageBox::critical(this, TITLE, InputTitle+"失败！\n可能是数据库文件损坏、出现重名问题。");
    }

}
