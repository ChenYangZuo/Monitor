#ifndef OBSERVERITEM_H
#define OBSERVERITEM_H

#include <QWidget>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QLabel>

class ObserverItem : public QWidget {

Q_OBJECT

public:

    explicit ObserverItem(QWidget *parent = nullptr);

    void setItemName(const QString&);

    void setItemColor(QString);

    void setCheckState(Qt::CheckState);

    QString getItemName();

    QCheckBox *checkBox = new QCheckBox();

private:
    QString itemName;
    QHBoxLayout *mainLayout = new QHBoxLayout;
    QLabel *colorLabel = new QLabel();

    QString mStyle = QString("QLabel{background-color:blue;}");
};

#endif // OBSERVERITEM_H
