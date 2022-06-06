#ifndef SUBJECTWINDOW_H
#define SUBJECTWINDOW_H

#include <QMainWindow>

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
};

#endif // SUBJECTWINDOW_H
