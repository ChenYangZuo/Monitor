#ifndef FILTERDIALOG_H
#define FILTERDIALOG_H

#include <QDialog>

namespace Ui {
class FilterDialog;
}

class FilterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FilterDialog(QWidget *parent = nullptr, bool = false, QString = "");
    ~FilterDialog();

    bool getFilterStart();

    QString getAddress();

private slots:
    void Open();
    void checkBoxChanged(int);

private:
    Ui::FilterDialog *ui;

    bool FilterStart = false;
    QString Address = "";
};

#endif // FILTERDIALOG_H
