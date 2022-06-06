#include "classeswindow.h"
#include "ui_classeswindow.h"

ClassesWindow::ClassesWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClassesWindow)
{
    ui->setupUi(this);
    this->setFixedSize(307,267);
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowFlags(Qt::Dialog);
}

ClassesWindow::~ClassesWindow()
{
    delete ui;
}
