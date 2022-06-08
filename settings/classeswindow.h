#ifndef CLASSESWINDOW_H
#define CLASSESWINDOW_H
#define TITLE "学生成绩管理系统"

#include <QMainWindow>
#include "database.h"
#include <QInputDialog>

namespace Ui {
class ClassesWindow;
}

class ClassesWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClassesWindow(QWidget *parent = 0);
    ~ClassesWindow();
    QStringList gradeID;

private:
    Ui::ClassesWindow *ui;

public slots:
    void delete_classes();
    void add_classes();
    void updata_classes();
};

#endif // CLASSESWINDOW_H
