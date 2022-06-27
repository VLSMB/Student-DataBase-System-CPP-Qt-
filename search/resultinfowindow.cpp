#include "resultinfowindow.h"
#include "ui_resultinfowindow.h"

ResultInfoWindow::ResultInfoWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ResultInfoWindow)
{
    ui->setupUi(this);
    this->setFixedSize(762,343);
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowFlags(Qt::Dialog);

    Refresh_ResultInfo_Table_INITIAL(ui->tbResult);
    Table_To_ComboBox(ui->cboxKinds, "examkinds", 1, true);
    Table_To_ComboBox(ui->cboxSubject, "subject", 1, true);
    ui->cboxKinds->setCurrentIndex(ui->cboxKinds->count()-1);
    ui->cboxSubject->setCurrentIndex(ui->cboxSubject->count()-1);

    QObject::connect(ui->btnQuery, &QPushButton::clicked, this, &this->search_result);
}

ResultInfoWindow::~ResultInfoWindow()
{
    delete ui;
}

void ResultInfoWindow::search_result()
{
    Refresh_ResultInfo_Table_INITIAL(ui->tbResult);
    for (int row=0; row< ui->tbResult->rowCount(); row++)
    {
        if (ui->cboxKinds->currentText() != "所有")
        {
            if (!ui->tbResult->item(row,4)->text().contains(ui->cboxKinds->currentText()))
                ui->tbResult->hideRow(row);
        }
        if (ui->cboxSubject->currentText() != "所有")
        {
            if (!ui->tbResult->item(row,3)->text().contains(ui->cboxSubject->currentText()))
                ui->tbResult->hideRow(row);
        }
        if (!ui->tbResult->item(row,1)->text().contains(ui->editName->text()))
            ui->tbResult->hideRow(row);
    }
}
