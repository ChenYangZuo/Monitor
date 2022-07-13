#include <QFileDialog>
#include <QDebug>
#include "filterdialog.h"
#include "ui_filterdialog.h"

FilterDialog::FilterDialog(QWidget *parent, bool check, QString filename) : QDialog(parent), ui(new Ui::FilterDialog) {
    ui->setupUi(this);
    ui->FilterSwitch->setChecked(check);
    ui->DLLEdit->setText(filename);
    if(check) {
        ui->DLLEdit->setEnabled(true);
        ui->Browse->setEnabled(true);
        FilterStart = true;
    }
    else {
        ui->DLLEdit->setEnabled(false);
        ui->Browse->setEnabled(false);
        FilterStart = false;
    }
    connect(ui->Browse,SIGNAL(clicked()),this,SLOT(Open()));
    connect(ui->FilterSwitch,SIGNAL(stateChanged(int)),this,SLOT(checkBoxChanged(int)));
}

FilterDialog::~FilterDialog() {
    delete ui;
}

void FilterDialog::Open() {
    Address = QFileDialog::getOpenFileName(this,"Open File","/","库(*.dll)");
    ui->DLLEdit->setText(Address);
}

void FilterDialog::checkBoxChanged(int state) {
    if(state == Qt::Checked){
        ui->DLLEdit->setEnabled(true);
        ui->Browse->setEnabled(true);
        FilterStart = true;
    }
    else {
        ui->DLLEdit->setEnabled(false);
        ui->Browse->setEnabled(false);
        FilterStart = false;
    }
}

bool FilterDialog::getFilterStart() {
    return FilterStart;
}

QString FilterDialog::getAddress() {
    return Address;
}
