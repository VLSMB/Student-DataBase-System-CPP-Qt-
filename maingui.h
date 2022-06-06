#ifndef MAINGUI_H
#define MAINGUI_H

#include <QMainWindow>
#include <QString>
#include <iostream>
#include "userwindow.h"
#include "baseinfo/resultwindow.h"
#include "baseinfo/studentwindow.h"
#include "search/resultinfowindow.h"
#include "search/studentinfowindow.h"
#include "settings/classeswindow.h"
#include "settings/examkindswindow.h"
#include "settings/gradewindow.h"
#include "settings/subjectwindow.h"

namespace Ui {
class MainGui;
}

class MainGui : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainGui(QString NowUser,QWidget *parent = 0);
    UserWindow* UserWindowInfo;
    ResultWindow* Result;
    StudentWindow* Student;
    ResultInfoWindow* ResultInfo;
    StudentInfoWindow* StudentInfo;
    ClassesWindow* Classes;
    ExamkindsWindow* Examkinds;
    GradeWindow* Grade;
    SubjectWindow* Subject;
    ~MainGui();

private:
    Ui::MainGui *ui;

public slots:
    void open_userWindow();
    void open_resultWindow();
    void open_studentWindow();
    void open_resultinfo();
    void open_studentinfo();
    void open_classes();
    void open_examkinds();
    void open_grade();
    void open_subject();
};

#endif // MAINGUI_H
