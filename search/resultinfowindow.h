#ifndef RESULTINFOWINDOW_H
#define RESULTINFOWINDOW_H

#include <QMainWindow>

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
};

#endif // RESULTINFOWINDOW_H
