#include "studentwindow.h"
#include "ui_studentwindow.h"

StudentWindow::StudentWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StudentWindow)
{
    ui->setupUi(this);
    this->setFixedSize(705,414);
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowFlags(Qt::Dialog);

    Refresh_StudentInfo_Table_INITIAL(ui->tbStudent);
    this->gradeID = Refresh_Grade_Table_Const(ui->cboxGrade);
    this->classID = Refresh_Classes_Table_Const(ui->cboxClass);
    ui->cboxClass->addItem("所有");
    ui->cboxGrade->addItem("所有");
    ui->cboxClass->setCurrentIndex(ui->cboxClass->count()-1);
    ui->cboxGrade->setCurrentIndex(ui->cboxGrade->count()-1);

    QObject::connect(ui->btnQuery,&QPushButton::clicked,this, &this->refresh_student);
    QObject::connect(ui->btnAdd, &QPushButton::clicked, this, &this->add_student);
    QObject::connect(ui->btnDel, &QPushButton::clicked, this, &this->delete_student);
    QObject::connect(ui->btnEdit, &QPushButton::clicked, this, &this->updata_student);
}

StudentWindow::~StudentWindow()
{
    delete ui;
}

void StudentWindow::refresh_student()
{
    Refresh_StudentInfo_Table(ui->tbStudent, ui->cboxGrade, ui->cboxClass);
}
void StudentWindow::add_student()
{
    QString stuID = ui->editID->text();
    QString stuName = ui->editName->text();
    int age = ui->editAge->value();
    QString sex = ui->cboxSex->currentText();
    QString phone = ui->editPhone->text();
    QString address = ui->editAddress->text();
    QString Class = ui->cboxClass->currentText();
    QString grade = ui->cboxGrade->currentText();
    if (stuID=="" || stuName=="" || sex=="" || phone=="" || address=="" || Class=="所有" || grade=="所有")
        QMessageBox::warning(this, TITLE, "请输入具体的学生信息以及选择具体的班级和年级！");
    else
    {
        bool status = Add_Student_Table(ui->tbStudent, ui->cboxClass, ui->cboxGrade, stuID, stuName,
                                        this->classID[Get_Index_By_Text(ui->cboxClass, Class)],
                this->gradeID[Get_Index_By_Text(ui->cboxGrade, grade)], QString("%0").arg(age), sex, phone, address);
        if (status)
            QMessageBox::information(this, TITLE, "学生信息增加成功！");
        else
            QMessageBox::critical(this, TITLE, "学生信息增加失败！\n可能是数据库文件损坏、出现重名问题。");
    }
}
void StudentWindow::delete_student()
{
    int row = ui->tbStudent->currentRow() + 1;
    QMessageBox::StandardButton result = QMessageBox::question(this,TITLE,
                          "是否要删除学生 "+ui->tbStudent->item(row-1,0)->text()+" ？");
    if (result == QMessageBox::Yes)
    {
        if (Delete_Table(ui->tbStudent, "student", row))
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
void StudentWindow::updata_student()
{
    QString KeyName, InputTitle, InputLabel;
    enum QInputType {STRING, INT, COMBOBOX, ERROR};
    int NowType = ERROR;
    switch (ui->tbStudent->currentColumn())
    {
        case 0:
            KeyName = "stuID";
            InputTitle = "修改学生编号ID";
            InputLabel = "请输入修改后的学生编号ID：";
            NowType = STRING;
        break;
        case 1:
            KeyName = "stuName";
            InputTitle = "修改学生姓名";
            InputLabel = "请输入修改后的学生姓名：";
            NowType = STRING;
        break;
        case 2:
            KeyName = "classID";
            InputTitle = "修改班级";
            InputLabel = "请选择修改后的班级：";
            NowType = COMBOBOX;
        break;
        case 3:
            KeyName = "gradeID";
            InputTitle = "修改年级";
            InputLabel = "请选择修改后的年级：";
            NowType = COMBOBOX;
        break;
        case 4:
            KeyName = "age";
            InputTitle = "修改年龄";
            InputLabel = "请输入修改后的年龄：";
            NowType = INT;
        break;
        case 5:
            KeyName = "sex";
            InputTitle = "修改性别";
            InputLabel = "请选择修改后的性别：";
            NowType = COMBOBOX;
        break;
        case 6:
            KeyName = "phone";
            InputTitle = "修改电话";
            InputLabel = "请输入要修改后的电话号码：";
            NowType = STRING;
        break;
        case 7:
            KeyName = "address";
            InputTitle = "修改地址";
            InputLabel = "请输入修改后的地址：";
            NowType = STRING;
        break;
        default:
            KeyName = "UNKNOWN BY VLSMB";
            InputTitle = "ERROR404";
            InputLabel = "AN EXPRESSION OCCURRED...";
    }
    int Value_INT;
    QString Value;
    bool status = false;
    switch (NowType)
    {
    case STRING:
        Value = QInputDialog::getText(this, InputTitle,InputLabel,QLineEdit::Normal,ui->tbStudent->currentItem()->text());
        if (Value!="")
        {
            status = Updata_Table(ui->tbStudent, "student", KeyName, Value);
            if (status){
                Refresh_StudentInfo_Table(ui->tbStudent, ui->cboxGrade, ui->cboxClass);
                QMessageBox::information(this, TITLE, InputTitle+"成功！");}
            else
                QMessageBox::critical(this, TITLE, InputTitle+"失败！\n可能是数据库文件损坏、出现重名问题。");
        }
    break;
    case INT:
        Value_INT = QInputDialog::getInt(this, InputTitle, InputLabel,
                                         ui->tbStudent->currentItem()->text().toInt(),0, 250);
        if (Value_INT != ui->tbStudent->currentItem()->text().toInt())
        {
            status = Updata_Table(ui->tbStudent, "student", KeyName, QString("%0").arg(Value_INT));
            if (status){
                Refresh_StudentInfo_Table(ui->tbStudent, ui->cboxGrade, ui->cboxClass);
                QMessageBox::information(this, TITLE, InputTitle+"成功！");}
            else
                QMessageBox::critical(this, TITLE, InputTitle+"失败！\n可能是数据库文件损坏、出现重名问题。");
        }
    break;
    case COMBOBOX:
        switch (ui->tbStudent->currentColumn())
        {
        case 2:
            // 修改班级
            Value = QInputDialog::getItem(this, InputTitle, InputLabel,ComboBox_To_StringList(ui->cboxClass, true),
                                          Get_Index_By_Text(ui->cboxClass, ui->tbStudent->currentItem()->text()),false);
            if (Value == ui->tbStudent->currentItem()->text())
                break;
            status = Updata_Table(ui->tbStudent, "student", KeyName, this->classID[Get_Index_By_Text(ui->cboxClass, Value)]);
            if (status){
                Refresh_StudentInfo_Table(ui->tbStudent, ui->cboxGrade, ui->cboxClass);
                QMessageBox::information(this, TITLE, InputTitle+"成功！");}
            else
                QMessageBox::critical(this, TITLE, InputTitle+"失败！\n可能是数据库文件损坏、出现重名问题。");
        break;
        case 3:
            // 修改年级
            Value = QInputDialog::getItem(this, InputTitle, InputLabel,ComboBox_To_StringList(ui->cboxGrade, true),
                                          Get_Index_By_Text(ui->cboxGrade, ui->tbStudent->currentItem()->text()),false);
            if (Value == ui->tbStudent->currentItem()->text())
                break;
            status = Updata_Table(ui->tbStudent, "student", KeyName, this->gradeID[Get_Index_By_Text(ui->cboxGrade, Value)]);
            if (status){
                Refresh_StudentInfo_Table(ui->tbStudent, ui->cboxGrade, ui->cboxClass);
                QMessageBox::information(this, TITLE, InputTitle+"成功！");}
            else
                QMessageBox::critical(this, TITLE, InputTitle+"失败！\n可能是数据库文件损坏、出现重名问题。");
        break;
        case 5:
            // 修改年龄
            Value = QInputDialog::getItem(this, InputTitle, InputLabel,ComboBox_To_StringList(ui->cboxSex, false),
                                          Get_Index_By_Text(ui->cboxSex, ui->tbStudent->currentItem()->text()),false);
            if (Value == ui->tbStudent->currentItem()->text())
                break;
            status = Updata_Table(ui->tbStudent, "student", KeyName, Value);
            if (status){
                Refresh_StudentInfo_Table(ui->tbStudent, ui->cboxGrade, ui->cboxClass);
                QMessageBox::information(this, TITLE, InputTitle+"成功！");}
            else
                QMessageBox::critical(this, TITLE, InputTitle+"失败！\n可能是数据库文件损坏、出现重名问题。");
        break;
        }

    break;
    default:
        QMessageBox::critical(this, TITLE, "未知错误！");

    }
}
