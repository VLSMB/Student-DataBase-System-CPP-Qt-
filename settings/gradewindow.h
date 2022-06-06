#ifndef GRADEWINDOW_H
#define GRADEWINDOW_H

#include <QMainWindow>

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
};

#endif // GRADEWINDOW_H
