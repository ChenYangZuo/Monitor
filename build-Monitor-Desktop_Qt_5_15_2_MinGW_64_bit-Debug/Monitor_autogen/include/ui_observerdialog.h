/********************************************************************************
** Form generated from reading UI file 'observerdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OBSERVERDIALOG_H
#define UI_OBSERVERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ObserverDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *comboBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ObserverDialog)
    {
        if (ObserverDialog->objectName().isEmpty())
            ObserverDialog->setObjectName(QString::fromUtf8("ObserverDialog"));
        ObserverDialog->resize(210, 139);
        verticalLayout = new QVBoxLayout(ObserverDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(ObserverDialog);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(ObserverDialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 2);

        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(ObserverDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        comboBox = new QComboBox(ObserverDialog);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout_2->addWidget(comboBox);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 2);

        verticalLayout->addLayout(horizontalLayout_2);

        buttonBox = new QDialogButtonBox(ObserverDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(ObserverDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ObserverDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ObserverDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ObserverDialog);
    } // setupUi

    void retranslateUi(QDialog *ObserverDialog)
    {
        ObserverDialog->setWindowTitle(QCoreApplication::translate("ObserverDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("ObserverDialog", "Name", nullptr));
        label_2->setText(QCoreApplication::translate("ObserverDialog", "Color", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ObserverDialog: public Ui_ObserverDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBSERVERDIALOG_H
