#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "monitor.h"

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent), ui(new Ui::SettingsDialog) {
    ui->setupUi(this);
    auto *p = (Monitor *) parent;  //获取父窗口指针
    ui->Adapter->setChecked(p->CHART_ADAPTER_ON);
    ui->radioButton_2->setChecked(!p->CHART_ADAPTER_ON);
    if (p->CHART_ADAPTER_ON) {
        ui->MaxXInput->setEnabled(false);
        ui->MinYInput->setEnabled(false);
        ui->MaxYInput->setEnabled(false);
    }

    if (!p->CHART_ADAPTER_ON) {
        MAX_X = p->MAX_FIX_X;
        MAX_Y = p->MAX_FIX_Y;
        MIN_Y = p->MIN_FIX_Y;
        ui->MaxXInput->setValue(MAX_X);
        ui->MinYInput->setValue(MIN_Y);
        ui->MaxYInput->setValue(MAX_Y);
    }
}

SettingsDialog::~SettingsDialog() {
    delete ui;
}

void SettingsDialog::on_buttonBox_accepted() {
    adaptive = ui->Adapter->isChecked();
    MAX_X = ui->MaxXInput->value();
    MIN_Y = ui->MinYInput->value();
    MAX_Y = ui->MaxYInput->value();
}


void SettingsDialog::on_Adapter_pressed() {
    ui->MaxXInput->setEnabled(false);
    ui->MinYInput->setEnabled(false);
    ui->MaxYInput->setEnabled(false);
}


void SettingsDialog::on_radioButton_2_pressed() {
    ui->MaxXInput->setEnabled(true);
    ui->MinYInput->setEnabled(true);
    ui->MaxYInput->setEnabled(true);
}

