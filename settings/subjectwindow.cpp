#include "subjectwindow.h"
#include "ui_subjectwindow.h"

SubjectWindow::SubjectWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SubjectWindow)
{
    ui->setupUi(this);
    this->setFixedSize(283,240);
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowFlags(Qt::Dialog);
}

SubjectWindow::~SubjectWindow()
{
    delete ui;
}
