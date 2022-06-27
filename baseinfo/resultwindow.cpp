#include "resultwindow.h"
#include "ui_resultwindow.h"

ResultWindow::ResultWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ResultWindow)
{
    ui->setupUi(this);
    this->setFixedSize(766,383);
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowFlags(Qt::Dialog);

    Refresh_ResultInfo_Table_INITIAL(ui->tbResult);
    Table_To_ComboBox(ui->cboxClass, "class", 2, true);
    Table_To_ComboBox(ui->cboxGrade, "grade", 1, true);
    Table_To_ComboBox(ui->cboxKinds, "examkinds", 1, true);
    Table_To_ComboBox(ui->cboxStuName, "student", 0, true);
    Table_To_ComboBox(ui->cboxSubject, "subject", 1, true);
    ui->cboxClass->setCurrentIndex(ui->cboxClass->count()-1);
    ui->cboxGrade->setCurrentIndex(ui->cboxGrade->count()-1);
    ui->cboxKinds->setCurrentIndex(ui->cboxKinds->count()-1);
    ui->cboxStuName->setCurrentIndex(ui->cboxStuName->count()-1);
    ui->cboxSubject->setCurrentIndex(ui->cboxSubject->count()-1);

    this->subID = Refresh_KindsSubject_Table_Const("subject");
    this->kindID = Refresh_KindsSubject_Table_Const("examkinds");

    QObject::connect(ui->btnAdd, &QPushButton::clicked, this, &this->add_result);
    QObject::connect(ui->btnDel, &QPushButton::clicked, this, &this->del_result);
    QObject::connect(ui->btnEdit, &QPushButton::clicked, this, &this->edit_result);
    QObject::connect(ui->btnQuery, &QPushButton::clicked, this, &this->refresh_result);

}

ResultWindow::~ResultWindow()
{
    delete ui;
}

void ResultWindow::add_result()
{
    if (ui->cboxKinds->currentText()=="所有" || ui->cboxStuName->currentText()=="所有" || ui->cboxSubject->currentText()=="所有")
        QMessageBox::warning(this, TITLE, "请选择具体的班级、考试信息！");
    else
    {
        QString kind = this->kindID[Get_Index_By_Text(ui->cboxKinds, ui->cboxKinds->currentText())];
        QString student = ui->cboxStuName->currentText();
        QString subject = this->subID[Get_Index_By_Text(ui->cboxSubject, ui->cboxSubject->currentText())];
        int ID = ui->tbResult->rowCount()+1;
        double result = ui->editResult->value();
        bool status = Add_Result_Table(ui->tbResult, QString("%0").arg(ID), student, kind, subject, QString("%0").arg(result));
        ui->btnQuery->click();
        if (status)
            QMessageBox::information(this, TITLE, "添加成绩成功！");
        else
            QMessageBox::critical(this, TITLE, "信息增加失败！\n可能是数据库文件损坏、出现重名问题。");
    }
}

void ResultWindow::del_result()
{
    int row = ui->tbResult->currentRow() + 1;
    QMessageBox::StandardButton result = QMessageBox::question(this,TITLE,
                          "是否要删除成绩 "+ui->tbResult->item(row-1,6)->text()+" ？");
    if (result == QMessageBox::Yes)
    {
        if (Delete_Table(ui->tbResult, "result", row))
        {
            ui->btnQuery->click();
            QMessageBox::information(this,TITLE,"删除成功！");
        }
        else
        {
            ui->btnQuery->click();
            QMessageBox::critical(this,TITLE,"删除失败！");
        }
    }

}

void ResultWindow::refresh_result()
{
    Refresh_ResultInfo_Table_INITIAL(ui->tbResult);
    for (int row=0; row<ui->tbResult->rowCount(); row++)
    {
        if (ui->cboxClass->currentText() != "所有")
        {
            if (!ui->tbResult->item(row,2)->text().contains(ui->cboxClass->currentText()))
                ui->tbResult->hideRow(row);
        }
        if (ui->cboxKinds->currentText() != "所有")
        {
            if (!ui->tbResult->item(row,4)->text().contains(ui->cboxKinds->currentText()))
                ui->tbResult->hideRow(row);
        }
        if (ui->cboxStuName->currentText() != "所有")
        {
            if (!ui->tbResult->item(row,0)->text().contains(ui->cboxStuName->currentText()))
                ui->tbResult->hideRow(row);
        }
        if (ui->cboxSubject->currentText() != "所有")
        {
            if (!ui->tbResult->item(row,3)->text().contains(ui->cboxSubject->currentText()))
                ui->tbResult->hideRow(row);
        }
    }
}

void ResultWindow::edit_result()
{
    QString KeyName, InputTitle, InputLabel;
    enum QInputType {STRING, INT, COMBOBOX, UNEDIT, ERROR};
    int NowType = ERROR;
    switch (ui->tbResult->currentColumn())
    {
        case 0:
            KeyName = "stuID";
            InputTitle = "修改学生编号ID";
            InputLabel = "请选择修改后的学生编号ID：";
            NowType = COMBOBOX;
        break;
        case 1:
            KeyName = "stuName";
            InputTitle = "修改学生姓名";
            InputLabel = "请输入修改后的学生姓名：";
            NowType = UNEDIT;
        break;
        case 2:
            KeyName = "classID";
            InputTitle = "修改班级";
            InputLabel = "请选择修改后的班级：";
            NowType = UNEDIT;
        break;
        case 3:
            KeyName = "subID";
            InputTitle = "修改科目";
            InputLabel = "请选择修改后的科目：";
            NowType = COMBOBOX;
        break;
        case 4:
            KeyName = "kindID";
            InputTitle = "修改种类";
            InputLabel = "请输入修改后的考试种类：";
            NowType = COMBOBOX;
        break;
        case 5:
            KeyName = "result";
            InputTitle = "修改成绩";
            InputLabel = "请选择修改后的成绩：";
            NowType = INT;
        break;
        case 6:
            KeyName = "ID";
            InputTitle = "修改编号";
            InputLabel = "请输入要修改后的编号：";
            NowType = STRING;
        break;
        default:
            KeyName = "UNKNOWN BY VLSMB";
            InputTitle = "ERROR404";
            InputLabel = "AN EXPRESSION OCCURRED...";
    }
    double Value_INT;
    QString Value;
    bool status = false;
    switch (NowType)
    {
    case STRING:
        Value = QInputDialog::getText(this, InputTitle,InputLabel,QLineEdit::Normal,ui->tbResult->currentItem()->text());
        if (Value!="")
        {
            status = Updata_Table(ui->tbResult, "result", KeyName, Value);
            if (status){
                ui->btnQuery->click();
                QMessageBox::information(this, TITLE, InputTitle+"成功！");}
            else{
                ui->btnQuery->click();
                QMessageBox::critical(this, TITLE, InputTitle+"失败！\n可能是数据库文件损坏、出现重名问题。");}
        }
    break;
    case INT: // 其实是double，但懒得改了
        Value_INT = QInputDialog::getDouble(this, InputTitle, InputLabel, ui->tbResult->currentItem()->text().toDouble(), 0, 1000, 3);
        if (Value_INT != ui->tbResult->currentItem()->text().toDouble())
        {
            status = Updata_Table(ui->tbResult, "result", KeyName, QString("%0").arg(Value_INT));
            if (status)
            {
                ui->btnQuery->click();
                QMessageBox::information(this, TITLE, InputTitle+"成功！");
            }
            else
            {
                ui->btnQuery->click();
                QMessageBox::critical(this, TITLE, InputTitle+"失败！\n可能是数据库文件损坏、出现重名问题。");
            }
        }
    break;
    case COMBOBOX:
        switch (ui->tbResult->currentColumn())
        {
        case 0:
            // 修改编号
            Value = QInputDialog::getItem(this, InputTitle, InputLabel,ComboBox_To_StringList(ui->cboxStuName, true),
                                          Get_Index_By_Text(ui->cboxStuName, ui->tbResult->currentItem()->text()),false);
            if (Value == ui->tbResult->currentItem()->text())
                break;
            status = Updata_Table(ui->tbResult, "result", KeyName, Value);
            if (status){
                ui->btnQuery->click();
                QMessageBox::information(this, TITLE, InputTitle+"成功！");}
            else
            {
                ui->btnQuery->click();
                QMessageBox::critical(this, TITLE, InputTitle+"失败！\n可能是数据库文件损坏、出现重名问题。");
            }
        break;
        case 3:
            // 修改科目
            Value = QInputDialog::getItem(this, InputTitle, InputLabel,ComboBox_To_StringList(ui->cboxSubject, true),
                                          Get_Index_By_Text(ui->cboxSubject, ui->tbResult->currentItem()->text()),false);
            if (Value == ui->tbResult->currentItem()->text())
                break;
            status = Updata_Table(ui->tbResult, "result", KeyName, this->subID[Get_Index_By_Text(ui->cboxSubject, Value)]);
            if (status){
                ui->btnQuery->click();
                QMessageBox::information(this, TITLE, InputTitle+"成功！");}
            else{
                ui->btnQuery->click();
                QMessageBox::critical(this, TITLE, InputTitle+"失败！\n可能是数据库文件损坏、出现重名问题。");
            }
        break;
        case 4:
            Value = QInputDialog::getItem(this, InputTitle, InputLabel,ComboBox_To_StringList(ui->cboxKinds, false),
                                          Get_Index_By_Text(ui->cboxKinds, ui->tbResult->currentItem()->text()),false);
            if (Value == ui->tbResult->currentItem()->text())
                break;
            status = Updata_Table(ui->tbResult, "result", KeyName, this->kindID[Get_Index_By_Text(ui->cboxKinds, Value)]);
            if (status){
                ui->btnQuery->click();
                QMessageBox::information(this, TITLE, InputTitle+"成功！");}
            else{
                ui->btnQuery->click();
                QMessageBox::critical(this, TITLE, InputTitle+"失败！\n可能是数据库文件损坏、出现重名问题。");
            }
        break;
        }

    break;
    case UNEDIT:
        QMessageBox::critical(this, TITLE, "禁止修改本项！");
    break;
    default:
        QMessageBox::critical(this, TITLE, "未知错误！");

    }
}
