#ifndef RESULTWINDOW_H
#define RESULTWINDOW_H

#include "database.h"
#define TITLE "学生成绩管理系统"
#include <QMainWindow>
#include <QMessageBox>
#include <QInputDialog>
#include <QStringList>

namespace Ui {
class ResultWindow;
}

class ResultWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ResultWindow(QWidget *parent = 0);
    ~ResultWindow();
    QStringList subID;
    QStringList kindID;

private:
    Ui::ResultWindow *ui;
public slots:
    void add_result();
    void edit_result();
    void del_result();
    void refresh_result();
};

#endif // RESULTWINDOW_H
