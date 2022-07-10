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
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
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
    QAction *DataIn;
    QAction *DataOut;
    QAction *AboutMenu;
    QAction *GenerateShot;
    QAction *ChartSettings;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *mainLayout;
    QHBoxLayout *topLayout;
    QTabWidget *tabWidget;
    QWidget *SourceTab;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_11;
    QLabel *DataSourceLabel;
    QComboBox *DataSourceList;
    QHBoxLayout *horizontalLayout_12;
    QLabel *COMLabel;
    QComboBox *COMList;
    QHBoxLayout *horizontalLayout_13;
    QLabel *BaudrateLabel;
    QComboBox *BaudrateList;
    QHBoxLayout *horizontalLayout_14;
    QLabel *SourceDetailLabel;
    QTextBrowser *SourceDetail;
    QHBoxLayout *horizontalLayout_16;
    QLabel *IPAddressLabel;
    QLineEdit *IPAddressEdit;
    QHBoxLayout *horizontalLayout_17;
    QLabel *PortLabel;
    QSpinBox *PortEdit;
    QSpacerItem *verticalSpacer_3;
    QPushButton *ConnectButton;
    QWidget *ObserverTab;
    QVBoxLayout *verticalLayout_8;
    QListWidget *ObservedList;
    QHBoxLayout *horizontalLayout_15;
    QToolButton *AddButton;
    QToolButton *DeleteButton;
    QSpacerItem *horizontalSpacer;
    QChartView *Chart;
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
        DataIn = new QAction(Monitor);
        DataIn->setObjectName(QString::fromUtf8("DataIn"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/load.png"), QSize(), QIcon::Normal, QIcon::Off);
        DataIn->setIcon(icon);
        DataIn->setIconVisibleInMenu(true);
        DataOut = new QAction(Monitor);
        DataOut->setObjectName(QString::fromUtf8("DataOut"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        DataOut->setIcon(icon1);
        DataOut->setIconVisibleInMenu(true);
        AboutMenu = new QAction(Monitor);
        AboutMenu->setObjectName(QString::fromUtf8("AboutMenu"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/about.png"), QSize(), QIcon::Normal, QIcon::Off);
        AboutMenu->setIcon(icon2);
        AboutMenu->setIconVisibleInMenu(true);
        GenerateShot = new QAction(Monitor);
        GenerateShot->setObjectName(QString::fromUtf8("GenerateShot"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/shot.png"), QSize(), QIcon::Normal, QIcon::Off);
        GenerateShot->setIcon(icon3);
        GenerateShot->setIconVisibleInMenu(true);
        ChartSettings = new QAction(Monitor);
        ChartSettings->setObjectName(QString::fromUtf8("ChartSettings"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/settings.png"), QSize(), QIcon::Normal, QIcon::Off);
        ChartSettings->setIcon(icon4);
        ChartSettings->setIconVisibleInMenu(true);
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
        verticalLayout = new QVBoxLayout(SourceTab);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        DataSourceLabel = new QLabel(SourceTab);
        DataSourceLabel->setObjectName(QString::fromUtf8("DataSourceLabel"));

        horizontalLayout_11->addWidget(DataSourceLabel);

        DataSourceList = new QComboBox(SourceTab);
        DataSourceList->setObjectName(QString::fromUtf8("DataSourceList"));
        DataSourceList->setMinimumSize(QSize(0, 30));
        DataSourceList->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_11->addWidget(DataSourceList);

        horizontalLayout_11->setStretch(0, 1);
        horizontalLayout_11->setStretch(1, 3);

        verticalLayout->addLayout(horizontalLayout_11);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        COMLabel = new QLabel(SourceTab);
        COMLabel->setObjectName(QString::fromUtf8("COMLabel"));

        horizontalLayout_12->addWidget(COMLabel);

        COMList = new QComboBox(SourceTab);
        COMList->setObjectName(QString::fromUtf8("COMList"));
        COMList->setMinimumSize(QSize(0, 30));
        COMList->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_12->addWidget(COMList);

        horizontalLayout_12->setStretch(0, 1);
        horizontalLayout_12->setStretch(1, 3);

        verticalLayout->addLayout(horizontalLayout_12);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        BaudrateLabel = new QLabel(SourceTab);
        BaudrateLabel->setObjectName(QString::fromUtf8("BaudrateLabel"));

        horizontalLayout_13->addWidget(BaudrateLabel);

        BaudrateList = new QComboBox(SourceTab);
        BaudrateList->setObjectName(QString::fromUtf8("BaudrateList"));
        BaudrateList->setMinimumSize(QSize(0, 30));
        BaudrateList->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_13->addWidget(BaudrateList);

        horizontalLayout_13->setStretch(0, 1);
        horizontalLayout_13->setStretch(1, 3);

        verticalLayout->addLayout(horizontalLayout_13);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        SourceDetailLabel = new QLabel(SourceTab);
        SourceDetailLabel->setObjectName(QString::fromUtf8("SourceDetailLabel"));

        horizontalLayout_14->addWidget(SourceDetailLabel);

        SourceDetail = new QTextBrowser(SourceTab);
        SourceDetail->setObjectName(QString::fromUtf8("SourceDetail"));
        SourceDetail->setMinimumSize(QSize(0, 30));
        SourceDetail->setMaximumSize(QSize(16777215, 30));
        SourceDetail->setContextMenuPolicy(Qt::NoContextMenu);
        SourceDetail->setAcceptDrops(false);
        SourceDetail->setInputMethodHints(Qt::ImhMultiLine);
        SourceDetail->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        SourceDetail->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        horizontalLayout_14->addWidget(SourceDetail);

        horizontalLayout_14->setStretch(0, 1);
        horizontalLayout_14->setStretch(1, 3);

        verticalLayout->addLayout(horizontalLayout_14);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        IPAddressLabel = new QLabel(SourceTab);
        IPAddressLabel->setObjectName(QString::fromUtf8("IPAddressLabel"));

        horizontalLayout_16->addWidget(IPAddressLabel);

        IPAddressEdit = new QLineEdit(SourceTab);
        IPAddressEdit->setObjectName(QString::fromUtf8("IPAddressEdit"));
        IPAddressEdit->setMinimumSize(QSize(0, 30));
        IPAddressEdit->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_16->addWidget(IPAddressEdit);

        horizontalLayout_16->setStretch(0, 1);
        horizontalLayout_16->setStretch(1, 3);

        verticalLayout->addLayout(horizontalLayout_16);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        PortLabel = new QLabel(SourceTab);
        PortLabel->setObjectName(QString::fromUtf8("PortLabel"));

        horizontalLayout_17->addWidget(PortLabel);

        PortEdit = new QSpinBox(SourceTab);
        PortEdit->setObjectName(QString::fromUtf8("PortEdit"));
        PortEdit->setMinimumSize(QSize(0, 30));
        PortEdit->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_17->addWidget(PortEdit);

        horizontalLayout_17->setStretch(0, 1);
        horizontalLayout_17->setStretch(1, 3);

        verticalLayout->addLayout(horizontalLayout_17);

        verticalSpacer_3 = new QSpacerItem(13, 267, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        ConnectButton = new QPushButton(SourceTab);
        ConnectButton->setObjectName(QString::fromUtf8("ConnectButton"));
        ConnectButton->setMinimumSize(QSize(0, 40));
        ConnectButton->setMaximumSize(QSize(16777215, 40));

        verticalLayout->addWidget(ConnectButton);

        tabWidget->addTab(SourceTab, QString());
        ObserverTab = new QWidget();
        ObserverTab->setObjectName(QString::fromUtf8("ObserverTab"));
        verticalLayout_8 = new QVBoxLayout(ObserverTab);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        ObservedList = new QListWidget(ObserverTab);
        ObservedList->setObjectName(QString::fromUtf8("ObservedList"));
        ObservedList->setContextMenuPolicy(Qt::CustomContextMenu);

        verticalLayout_8->addWidget(ObservedList);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        AddButton = new QToolButton(ObserverTab);
        AddButton->setObjectName(QString::fromUtf8("AddButton"));
        AddButton->setMinimumSize(QSize(32, 32));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/edit.png"), QSize(), QIcon::Normal, QIcon::Off);
        AddButton->setIcon(icon5);

        horizontalLayout_15->addWidget(AddButton);

        DeleteButton = new QToolButton(ObserverTab);
        DeleteButton->setObjectName(QString::fromUtf8("DeleteButton"));
        DeleteButton->setMinimumSize(QSize(32, 32));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        DeleteButton->setIcon(icon6);

        horizontalLayout_15->addWidget(DeleteButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer);


        verticalLayout_8->addLayout(horizontalLayout_15);

        tabWidget->addTab(ObserverTab, QString());

        topLayout->addWidget(tabWidget);

        Chart = new QChartView(centralwidget);
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
        menubar->setGeometry(QRect(0, 0, 1064, 32));
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
        menu->addAction(DataIn);
        menu->addAction(DataOut);
        menu_2->addAction(GenerateShot);
        menu_2->addAction(ChartSettings);
        menu_3->addAction(AboutMenu);

        retranslateUi(Monitor);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Monitor);
    } // setupUi

    void retranslateUi(QMainWindow *Monitor)
    {
        Monitor->setWindowTitle(QCoreApplication::translate("Monitor", "MainWindow", nullptr));
        DataIn->setText(QCoreApplication::translate("Monitor", "\345\257\274\345\205\245\350\256\276\347\275\256", nullptr));
        DataOut->setText(QCoreApplication::translate("Monitor", "\345\257\274\345\207\272\350\256\276\347\275\256", nullptr));
        AboutMenu->setText(QCoreApplication::translate("Monitor", "\345\205\263\344\272\216", nullptr));
        GenerateShot->setText(QCoreApplication::translate("Monitor", "\347\224\237\346\210\220\346\210\252\345\233\276", nullptr));
        ChartSettings->setText(QCoreApplication::translate("Monitor", "\347\224\273\345\270\203\350\256\276\347\275\256", nullptr));
        DataSourceLabel->setText(QCoreApplication::translate("Monitor", "\346\225\260\346\215\256\346\272\220", nullptr));
        COMLabel->setText(QCoreApplication::translate("Monitor", "COM\345\217\243", nullptr));
        BaudrateLabel->setText(QCoreApplication::translate("Monitor", "\346\263\242\347\211\271\347\216\207", nullptr));
        SourceDetailLabel->setText(QCoreApplication::translate("Monitor", "\346\217\217\350\277\260", nullptr));
        IPAddressLabel->setText(QCoreApplication::translate("Monitor", "IP\345\234\260\345\235\200", nullptr));
        PortLabel->setText(QCoreApplication::translate("Monitor", "\347\253\257\345\217\243", nullptr));
        ConnectButton->setText(QCoreApplication::translate("Monitor", "\350\277\236\346\216\245", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(SourceTab), QCoreApplication::translate("Monitor", "\346\225\260\346\215\256\346\272\220", nullptr));
        AddButton->setText(QString());
        DeleteButton->setText(QString());
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
