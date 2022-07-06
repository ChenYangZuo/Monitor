#include "observeritem.h"
#include <QDebug>
#include <utility>

ObserverItem::ObserverItem(QWidget *parent) : QWidget{parent} {
    checkBox->setObjectName("checkBox");
    nameLabel->setFixedSize(10, 10);
    mainLayout->addWidget(checkBox);
    mainLayout->addWidget(nameLabel);
    setLayout(mainLayout);
    connect(checkBox, SIGNAL(stateChanged(int)), this, SLOT(checkBoxChanged()));
}

void ObserverItem::checkBoxChanged() {
    qDebug() << "You Pushed Num " << mIndex;
}

void ObserverItem::setItemName(const QString &name) {
    checkBox->setText(name);
}

void ObserverItem::setItemIndex(int index) {
    mIndex = index;
}

void ObserverItem::setItemColor(QString style) {
    mStyle = std::move(style);
    nameLabel->setStyleSheet(mStyle);
}
