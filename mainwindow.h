#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define TITLE "学生成绩管理系统"
#include <QMainWindow>
#include "maingui.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    MainGui *MainGuiWindow;
    ~MainWindow();

private:
    Ui::MainWindow *ui;
public slots:
    void login();
};

#endif // MAINWINDOW_H
