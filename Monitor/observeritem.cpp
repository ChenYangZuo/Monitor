#include "observeritem.h"
#include <QDebug>
#include <utility>

ObserverItem::ObserverItem(QWidget *parent) : QWidget{parent} {
    colorLabel->setFixedSize(10, 10);
    mainLayout->addWidget(checkBox);
    mainLayout->addWidget(colorLabel);
    setLayout(mainLayout);
}

void ObserverItem::setItemName(const QString& name) {
    itemName = name;
    checkBox->setText(name);
}

void ObserverItem::setItemIndex(int index) {
    itemIndex = index;
}

void ObserverItem::setItemColor(QString style) {
    mStyle = std::move(style);
    colorLabel->setStyleSheet(mStyle);
}

QString ObserverItem::getItemName() {
    return itemName;
}

bool ObserverItem::getCheckState() {
    return checkBox->isChecked();
}

void ObserverItem::setCheckState(Qt::CheckState state) {
    checkBox->setCheckState(state);
}

QCheckBox *ObserverItem::getCheckBox() {
    return checkBox;
}
