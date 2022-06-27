#ifndef STUDENTWINDOW_H
#define STUDENTWINDOW_H

#include "database.h"
#define TITLE "学生成绩管理系统"
#include <QMainWindow>
#include <QMessageBox>
#include <QInputDialog>
#include <QStringList>

namespace Ui {
class StudentWindow;
}

class StudentWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StudentWindow(QWidget *parent = 0);
    ~StudentWindow();
    QStringList gradeID;
    QStringList classID;

private:
    Ui::StudentWindow *ui;

public slots:
    void refresh_student();
    void delete_student();
    void add_student();
    void updata_student();
};

#endif // STUDENTWINDOW_H
