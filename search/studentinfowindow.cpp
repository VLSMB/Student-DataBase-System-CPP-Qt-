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
}

StudentInfoWindow::~StudentInfoWindow()
{
    delete ui;
}
