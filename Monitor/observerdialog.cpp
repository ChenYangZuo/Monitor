#include "observerdialog.h"
#include "ui_observerdialog.h"

ObserverDialog::ObserverDialog(QWidget *parent) : QDialog(parent), ui(new Ui::ObserverDialog) {
    ui->setupUi(this);

    for (int i = 0; i < 7; i++) {
        ui->comboBox->addItem(colorList[i]);
    }

}

ObserverDialog::~ObserverDialog() {
    delete ui;
}

void ObserverDialog::on_buttonBox_accepted() {
    name = ui->lineEdit->text();
    color = ui->comboBox->currentText();
}