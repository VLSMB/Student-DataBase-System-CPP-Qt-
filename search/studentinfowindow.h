#ifndef STUDENTINFOWINDOW_H
#define STUDENTINFOWINDOW_H
#define TITLE "学生成绩管理系统"

#include <QMainWindow>
#include "database.h"
#include <QInputDialog>

namespace Ui {
class StudentInfoWindow;
}

class StudentInfoWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StudentInfoWindow(QWidget *parent = 0);
    ~StudentInfoWindow();

private:
    Ui::StudentInfoWindow *ui;
public slots:
    void search_student();
};

#endif // STUDENTINFOWINDOW_H
