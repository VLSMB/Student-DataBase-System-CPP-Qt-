#ifndef SUBJECTWINDOW_H
#define SUBJECTWINDOW_H
#define TITLE "学生成绩管理系统"

#include <QMainWindow>
#include "database.h"
#include <QInputDialog>

namespace Ui {
class SubjectWindow;
}

class SubjectWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SubjectWindow(QWidget *parent = 0);
    ~SubjectWindow();

private:
    Ui::SubjectWindow *ui;

public slots:
    void delete_subject();
    void add_subject();
    void updata_subject();
};

#endif // SUBJECTWINDOW_H
