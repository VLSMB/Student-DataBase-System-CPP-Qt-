#ifndef USERWINDOW_H
#define USERWINDOW_H
#define TITLE "学生成绩管理系统"

#include <QMainWindow>
#include "database.h"
#include <QInputDialog>

namespace Ui {
class UserWindow;
}

class UserWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserWindow(QWidget *parent = 0);
    ~UserWindow();

private:
    Ui::UserWindow *ui;

public slots:
    void delete_user();
    void add_user();
    void updata_user();
};

#endif // USERWINDOW_H
