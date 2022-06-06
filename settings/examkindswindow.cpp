#include "examkindswindow.h"
#include "ui_examkindswindow.h"

ExamkindsWindow::ExamkindsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ExamkindsWindow)
{
    ui->setupUi(this);
    this->setFixedSize(286,237);
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowFlags(Qt::Dialog);
}

ExamkindsWindow::~ExamkindsWindow()
{
    delete ui;
}
