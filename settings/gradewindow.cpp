#include "gradewindow.h"
#include "ui_gradewindow.h"

GradeWindow::GradeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GradeWindow)
{
    ui->setupUi(this);
    this->setFixedSize(283,241);
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowFlags(Qt::Dialog);
}

GradeWindow::~GradeWindow()
{
    delete ui;
}
