#ifndef OBSERVERDIALOG_H
#define OBSERVERDIALOG_H

#include <QDialog>

namespace Ui {
    class ObserverDialog;
}

class ObserverDialog : public QDialog {
Q_OBJECT

public:
    explicit ObserverDialog(QWidget *parent = nullptr);

    ~ObserverDialog();

    QString name = "";
    QString color = "red";

private:
    Ui::ObserverDialog *ui;
    QList<QString> colorList = {"red", "green", "blue", "cyan", "magenta", "yellow"};

public slots:

    void on_buttonBox_accepted();
};

#endif // OBSERVERDIALOG_H
