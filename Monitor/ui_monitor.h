/********************************************************************************
** Form generated from reading UI file 'monitor.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MONITOR_H
#define UI_MONITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Monitor
{
public:
    QAction *action;
    QAction *action_2;
    QAction *action_3;
    QAction *action_4;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *mainLayout;
    QHBoxLayout *topLayout;
    QTabWidget *tabWidget;
    QWidget *SourceTab;
    QVBoxLayout *verticalLayout_10;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_9;
    QComboBox *DataSourceList;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_10;
    QComboBox *COMList;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_11;
    QComboBox *BaudrateList;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_12;
    QLineEdit *SourceDetail;
    QPushButton *ConnectButton;
    QSpacerItem *verticalSpacer_3;
    QWidget *ObserverTab;
    QVBoxLayout *verticalLayout_8;
    QListView *ObservedList;
    QHBoxLayout *horizontalLayout_15;
    QToolButton *AddButton;
    QToolButton *DeleteButton;
    QSpacerItem *horizontalSpacer;
    QGraphicsView *Chart;
    QTextBrowser *RawData;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Monitor)
    {
        if (Monitor->objectName().isEmpty())
            Monitor->setObjectName(QString::fromUtf8("Monitor"));
        Monitor->resize(1064, 671);
        action = new QAction(Monitor);
        action->setObjectName(QString::fromUtf8("action"));
        action_2 = new QAction(Monitor);
        action_2->setObjectName(QString::fromUtf8("action_2"));
        action_3 = new QAction(Monitor);
        action_3->setObjectName(QString::fromUtf8("action_3"));
        action_4 = new QAction(Monitor);
        action_4->setObjectName(QString::fromUtf8("action_4"));
        centralwidget = new QWidget(Monitor);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_5 = new QVBoxLayout(centralwidget);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        mainLayout = new QVBoxLayout();
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        topLayout = new QHBoxLayout();
        topLayout->setObjectName(QString::fromUtf8("topLayout"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setMinimumSize(QSize(300, 0));
        tabWidget->setMaximumSize(QSize(300, 16777215));
        SourceTab = new QWidget();
        SourceTab->setObjectName(QString::fromUtf8("SourceTab"));
        verticalLayout_10 = new QVBoxLayout(SourceTab);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_9 = new QLabel(SourceTab);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_11->addWidget(label_9);

        DataSourceList = new QComboBox(SourceTab);
        DataSourceList->setObjectName(QString::fromUtf8("DataSourceList"));

        horizontalLayout_11->addWidget(DataSourceList);

        horizontalLayout_11->setStretch(0, 1);
        horizontalLayout_11->setStretch(1, 3);

        verticalLayout_9->addLayout(horizontalLayout_11);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_10 = new QLabel(SourceTab);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_12->addWidget(label_10);

        COMList = new QComboBox(SourceTab);
        COMList->setObjectName(QString::fromUtf8("COMList"));

        horizontalLayout_12->addWidget(COMList);

        horizontalLayout_12->setStretch(0, 1);
        horizontalLayout_12->setStretch(1, 3);

        verticalLayout_9->addLayout(horizontalLayout_12);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        label_11 = new QLabel(SourceTab);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_13->addWidget(label_11);

        BaudrateList = new QComboBox(SourceTab);
        BaudrateList->setObjectName(QString::fromUtf8("BaudrateList"));

        horizontalLayout_13->addWidget(BaudrateList);

        horizontalLayout_13->setStretch(0, 1);
        horizontalLayout_13->setStretch(1, 3);

        verticalLayout_9->addLayout(horizontalLayout_13);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_12 = new QLabel(SourceTab);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_14->addWidget(label_12);

        SourceDetail = new QLineEdit(SourceTab);
        SourceDetail->setObjectName(QString::fromUtf8("SourceDetail"));

        horizontalLayout_14->addWidget(SourceDetail);

        horizontalLayout_14->setStretch(0, 1);
        horizontalLayout_14->setStretch(1, 3);

        verticalLayout_9->addLayout(horizontalLayout_14);

        ConnectButton = new QPushButton(SourceTab);
        ConnectButton->setObjectName(QString::fromUtf8("ConnectButton"));

        verticalLayout_9->addWidget(ConnectButton);


        verticalLayout_10->addLayout(verticalLayout_9);

        verticalSpacer_3 = new QSpacerItem(13, 267, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_10->addItem(verticalSpacer_3);

        tabWidget->addTab(SourceTab, QString());
        ObserverTab = new QWidget();
        ObserverTab->setObjectName(QString::fromUtf8("ObserverTab"));
        verticalLayout_8 = new QVBoxLayout(ObserverTab);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        ObservedList = new QListView(ObserverTab);
        ObservedList->setObjectName(QString::fromUtf8("ObservedList"));

        verticalLayout_8->addWidget(ObservedList);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        AddButton = new QToolButton(ObserverTab);
        AddButton->setObjectName(QString::fromUtf8("AddButton"));
        AddButton->setMinimumSize(QSize(32, 32));

        horizontalLayout_15->addWidget(AddButton);

        DeleteButton = new QToolButton(ObserverTab);
        DeleteButton->setObjectName(QString::fromUtf8("DeleteButton"));
        DeleteButton->setMinimumSize(QSize(32, 32));

        horizontalLayout_15->addWidget(DeleteButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer);


        verticalLayout_8->addLayout(horizontalLayout_15);

        tabWidget->addTab(ObserverTab, QString());

        topLayout->addWidget(tabWidget);

        Chart = new QGraphicsView(centralwidget);
        Chart->setObjectName(QString::fromUtf8("Chart"));

        topLayout->addWidget(Chart);

        topLayout->setStretch(0, 1);
        topLayout->setStretch(1, 3);

        mainLayout->addLayout(topLayout);

        RawData = new QTextBrowser(centralwidget);
        RawData->setObjectName(QString::fromUtf8("RawData"));

        mainLayout->addWidget(RawData);

        mainLayout->setStretch(0, 3);
        mainLayout->setStretch(1, 1);

        verticalLayout_5->addLayout(mainLayout);

        Monitor->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Monitor);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1064, 26));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        Monitor->setMenuBar(menubar);
        statusbar = new QStatusBar(Monitor);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        statusbar->setSizeGripEnabled(true);
        Monitor->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menu_3->menuAction());
        menu->addAction(action);
        menu->addAction(action_2);
        menu_2->addAction(action_4);
        menu_3->addAction(action_3);

        retranslateUi(Monitor);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Monitor);
    } // setupUi

    void retranslateUi(QMainWindow *Monitor)
    {
        Monitor->setWindowTitle(QCoreApplication::translate("Monitor", "MainWindow", nullptr));
        action->setText(QCoreApplication::translate("Monitor", "\345\257\274\345\205\245\346\225\260\346\215\256", nullptr));
        action_2->setText(QCoreApplication::translate("Monitor", "\345\257\274\345\207\272\346\225\260\346\215\256", nullptr));
        action_3->setText(QCoreApplication::translate("Monitor", "\345\205\263\344\272\216", nullptr));
        action_4->setText(QCoreApplication::translate("Monitor", "\347\224\237\346\210\220\346\210\252\345\233\276", nullptr));
        label_9->setText(QCoreApplication::translate("Monitor", "\346\225\260\346\215\256\346\235\245\346\272\220", nullptr));
        label_10->setText(QCoreApplication::translate("Monitor", "COM\345\217\243", nullptr));
        label_11->setText(QCoreApplication::translate("Monitor", "\346\263\242\347\211\271\347\216\207", nullptr));
        label_12->setText(QCoreApplication::translate("Monitor", "\346\217\217\350\277\260", nullptr));
        ConnectButton->setText(QCoreApplication::translate("Monitor", "\350\277\236\346\216\245", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(SourceTab), QCoreApplication::translate("Monitor", "\346\225\260\346\215\256\346\272\220", nullptr));
        AddButton->setText(QCoreApplication::translate("Monitor", "\346\267\273\345\212\240", nullptr));
        DeleteButton->setText(QCoreApplication::translate("Monitor", "\345\210\240\351\231\244", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(ObserverTab), QCoreApplication::translate("Monitor", "\350\247\202\345\257\237", nullptr));
        menu->setTitle(QCoreApplication::translate("Monitor", "\346\226\207\344\273\266", nullptr));
        menu_2->setTitle(QCoreApplication::translate("Monitor", "\346\223\215\344\275\234", nullptr));
        menu_3->setTitle(QCoreApplication::translate("Monitor", "\345\270\256\345\212\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Monitor: public Ui_Monitor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MONITOR_H
