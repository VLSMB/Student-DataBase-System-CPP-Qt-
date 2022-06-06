#ifndef CLASSESWINDOW_H
#define CLASSESWINDOW_H

#include <QMainWindow>

namespace Ui {
class ClassesWindow;
}

class ClassesWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClassesWindow(QWidget *parent = 0);
    ~ClassesWindow();

private:
    Ui::ClassesWindow *ui;
};

#endif // CLASSESWINDOW_H
