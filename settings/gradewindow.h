#ifndef GRADEWINDOW_H
#define GRADEWINDOW_H
#define TITLE "学生成绩管理系统"

#include <QMainWindow>
#include "database.h"
#include <QInputDialog>

namespace Ui {
class GradeWindow;
}

class GradeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GradeWindow(QWidget *parent = 0);
    ~GradeWindow();

private:
    Ui::GradeWindow *ui;

public slots:
    void delete_grade();
    void add_grade();
    void updata_grade();
};

#endif // GRADEWINDOW_H
