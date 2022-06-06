#ifndef STUDENTINFOWINDOW_H
#define STUDENTINFOWINDOW_H

#include <QMainWindow>

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
};

#endif // STUDENTINFOWINDOW_H
