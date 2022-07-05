/********************************************************************************
** Form generated from reading UI file 'settingsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSDIALOG_H
#define UI_SETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SettingsDialog
{
public:
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *Adapter;
    QVBoxLayout *verticalLayout;
    QRadioButton *radioButton_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *MaxXInput;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpinBox *MinYInput;
    QSpinBox *MaxYInput;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SettingsDialog)
    {
        if (SettingsDialog->objectName().isEmpty())
            SettingsDialog->setObjectName(QString::fromUtf8("SettingsDialog"));
        SettingsDialog->resize(220, 171);
        verticalLayout_3 = new QVBoxLayout(SettingsDialog);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        Adapter = new QRadioButton(SettingsDialog);
        Adapter->setObjectName(QString::fromUtf8("Adapter"));

        verticalLayout_2->addWidget(Adapter);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        radioButton_2 = new QRadioButton(SettingsDialog);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));

        verticalLayout->addWidget(radioButton_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(SettingsDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label);

        MaxXInput = new QSpinBox(SettingsDialog);
        MaxXInput->setObjectName(QString::fromUtf8("MaxXInput"));
        MaxXInput->setMaximum(1000);

        horizontalLayout->addWidget(MaxXInput);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 2);

        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(SettingsDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_2);

        MinYInput = new QSpinBox(SettingsDialog);
        MinYInput->setObjectName(QString::fromUtf8("MinYInput"));
        MinYInput->setMinimum(-500);
        MinYInput->setMaximum(500);

        horizontalLayout_2->addWidget(MinYInput);

        MaxYInput = new QSpinBox(SettingsDialog);
        MaxYInput->setObjectName(QString::fromUtf8("MaxYInput"));
        MaxYInput->setMinimum(-500);
        MaxYInput->setMaximum(500);

        horizontalLayout_2->addWidget(MaxYInput);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 1);
        horizontalLayout_2->setStretch(2, 1);

        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(verticalLayout);


        verticalLayout_3->addLayout(verticalLayout_2);

        buttonBox = new QDialogButtonBox(SettingsDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_3->addWidget(buttonBox);


        retranslateUi(SettingsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SettingsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SettingsDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingsDialog)
    {
        SettingsDialog->setWindowTitle(QCoreApplication::translate("SettingsDialog", "Dialog", nullptr));
        Adapter->setText(QCoreApplication::translate("SettingsDialog", "\350\207\252\351\200\202\345\272\224\345\244\247\345\260\217", nullptr));
        radioButton_2->setText(QCoreApplication::translate("SettingsDialog", "\345\233\272\345\256\232\345\244\247\345\260\217", nullptr));
        label->setText(QCoreApplication::translate("SettingsDialog", "\346\250\252\345\220\221", nullptr));
        label_2->setText(QCoreApplication::translate("SettingsDialog", "\347\272\265\345\220\221", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingsDialog: public Ui_SettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOG_H
