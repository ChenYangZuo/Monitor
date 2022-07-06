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

    void setItemName(const QString &) const;

    void setItemIndex(int);

    void setItemColor(QString);

    QCheckBox *checkBox = new QCheckBox();

private:
    int mIndex = 0;
    QHBoxLayout *mainLayout = new QHBoxLayout;
    QLabel *nameLabel = new QLabel();
    QString mStyle = QString("QLabel{background-color:blue;}");
};

#endif // OBSERVERITEM_H
