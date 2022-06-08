#include "studentinfowindow.h"
#include "ui_studentinfowindow.h"

StudentInfoWindow::StudentInfoWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StudentInfoWindow)
{
    ui->setupUi(this);
    this->setFixedSize(705,343);
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowFlags(Qt::Dialog);
    Refresh_Table(ui->tbStudent,"student");

    QObject::connect(ui->btnQuery, &QPushButton::clicked, this, &this->search_student);
}

StudentInfoWindow::~StudentInfoWindow()
{
    delete ui;
}

void StudentInfoWindow::search_student()
{
    Refresh_Table(ui->tbStudent, "student");
    int col = ui->cboxCondition->currentIndex();
    for (int row=0; row<ui->tbStudent->rowCount(); row++)
    {
        if (!(ui->tbStudent->item(row, col)->text().contains(ui->editKey->text())))
            ui->tbStudent->hideRow(row);
    }
}
