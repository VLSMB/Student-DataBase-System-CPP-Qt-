#include "resultinfowindow.h"
#include "ui_resultinfowindow.h"

ResultInfoWindow::ResultInfoWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ResultInfoWindow)
{
    ui->setupUi(this);
    this->setFixedSize(762,343);
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowFlags(Qt::Dialog);
}

ResultInfoWindow::~ResultInfoWindow()
{
    delete ui;
}
