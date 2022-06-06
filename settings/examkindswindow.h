#ifndef EXAMKINDSWINDOW_H
#define EXAMKINDSWINDOW_H

#include <QMainWindow>

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
};

#endif // EXAMKINDSWINDOW_H
