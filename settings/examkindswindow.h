#ifndef EXAMKINDSWINDOW_H
#define EXAMKINDSWINDOW_H
#define TITLE "学生成绩管理系统"

#include <QMainWindow>
#include "database.h"
#include <QInputDialog>

namespace Ui {
class ExamkindsWindow;
}

class ExamkindsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ExamkindsWindow(QWidget *parent = 0);
    ~ExamkindsWindow();

private:
    Ui::ExamkindsWindow *ui;

public slots:
    void delete_kind();
    void add_kind();
    void updata_kind();
};

#endif // EXAMKINDSWINDOW_H
