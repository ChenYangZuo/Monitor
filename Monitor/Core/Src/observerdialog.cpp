#include "observerdialog.h"
#include "ui_observerdialog.h"

ObserverDialog::ObserverDialog(QWidget *parent) : QDialog(parent), ui(new Ui::ObserverDialog) {
    ui->setupUi(this);

    for (auto & i : colorList) {
        ui->comboBox->addItem(i);
    }

}

ObserverDialog::~ObserverDialog() {
    delete ui;
}

void ObserverDialog::on_buttonBox_accepted() {
    name = ui->lineEdit->text();
    color = ui->comboBox->currentText();
}