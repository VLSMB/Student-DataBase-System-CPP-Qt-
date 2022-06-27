#ifndef RESULTINFOWINDOW_H
#define RESULTINFOWINDOW_H
#define TITLE "学生成绩管理系统"

#include <QMainWindow>
#include "database.h"

namespace Ui {
class ResultInfoWindow;
}

class ResultInfoWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ResultInfoWindow(QWidget *parent = 0);
    ~ResultInfoWindow();

private:
    Ui::ResultInfoWindow *ui;

public slots:
    void search_result();
};

#endif // RESULTINFOWINDOW_H
