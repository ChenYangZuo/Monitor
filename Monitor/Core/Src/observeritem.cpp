#include "observeritem.h"
#include <QDebug>
#include <utility>

ObserverItem::ObserverItem(QWidget *parent) : QWidget{parent} {
    checkBox->setObjectName("checkBox");
    filterLabel->setObjectName("filter");
    filterLabel->setFixedSize(16, 16);
    colorLabel->setFixedSize(10, 10);
    mainLayout->addWidget(checkBox);
    mainLayout->addWidget(filterLabel);
    mainLayout->addWidget(colorLabel);
    setLayout(mainLayout);
}

void ObserverItem::setItemName(const QString& name) {
    itemName = name;
    checkBox->setText(name);
}

void ObserverItem::setItemColor(QString style) {
    mStyle = std::move(style);
    colorLabel->setStyleSheet(mStyle);
}

QString ObserverItem::getItemName() {
    return itemName;
}

void ObserverItem::setCheckState(Qt::CheckState state) {
    checkBox->setCheckState(state);
}
