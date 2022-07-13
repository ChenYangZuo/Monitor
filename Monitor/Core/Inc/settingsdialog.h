#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
    class SettingsDialog;
}

class SettingsDialog : public QDialog {
Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);

    ~SettingsDialog();

    bool adaptive = true;
    int MAX_X = 100;
    int MIN_Y = -10;
    int MAX_Y = 10;

private:
    Ui::SettingsDialog *ui;

public slots:

    void on_buttonBox_accepted();

    void on_Adapter_pressed();

    void on_radioButton_2_pressed();
};

#endif // SETTINGSDIALOG_H
