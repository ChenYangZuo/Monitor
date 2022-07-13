/********************************************************************************
** Form generated from reading UI file 'filterdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILTERDIALOG_H
#define UI_FILTERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FilterDialog
{
public:
    QVBoxLayout *verticalLayout;
    QCheckBox *FilterSwitch;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *DLLEdit;
    QPushButton *Browse;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *FilterDialog)
    {
        if (FilterDialog->objectName().isEmpty())
            FilterDialog->setObjectName(QString::fromUtf8("FilterDialog"));
        FilterDialog->resize(400, 103);
        verticalLayout = new QVBoxLayout(FilterDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        FilterSwitch = new QCheckBox(FilterDialog);
        FilterSwitch->setObjectName(QString::fromUtf8("FilterSwitch"));

        verticalLayout->addWidget(FilterSwitch);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(FilterDialog);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        DLLEdit = new QLineEdit(FilterDialog);
        DLLEdit->setObjectName(QString::fromUtf8("DLLEdit"));

        horizontalLayout->addWidget(DLLEdit);

        Browse = new QPushButton(FilterDialog);
        Browse->setObjectName(QString::fromUtf8("Browse"));

        horizontalLayout->addWidget(Browse);


        verticalLayout->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(FilterDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(FilterDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), FilterDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), FilterDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(FilterDialog);
    } // setupUi

    void retranslateUi(QDialog *FilterDialog)
    {
        FilterDialog->setWindowTitle(QCoreApplication::translate("FilterDialog", "Dialog", nullptr));
        FilterSwitch->setText(QCoreApplication::translate("FilterDialog", "\345\220\257\347\224\250\346\273\244\346\263\242\345\231\250", nullptr));
        label->setText(QCoreApplication::translate("FilterDialog", "\351\223\276\346\216\245", nullptr));
        Browse->setText(QCoreApplication::translate("FilterDialog", "\346\265\217\350\247\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FilterDialog: public Ui_FilterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILTERDIALOG_H
