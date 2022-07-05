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

    void setItemName(const QString &);

    void setItemIndex(int);

    void setItemColor(QString);

private:
    QHBoxLayout *mainLayout = new QHBoxLayout;
    QCheckBox *checkBox = new QCheckBox();
    QLabel *nameLabel = new QLabel();
    int mIndex = 0;
    QString mStyle = QString("QLabel{background-color:blue;}");

public slots:

    void checkBoxChanged();

};

#endif // OBSERVERITEM_H
