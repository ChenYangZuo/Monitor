#include <QDebug>
#include <QMessageBox>
#include "monitor.h"
#include "ui_monitor.h"
#include "settingsdialog.h"
#include "observeritem.h"
#include "observerdialog.h"
#include "chartitem.h"

Monitor::Monitor(QWidget *parent) : QMainWindow(parent), ui(new Ui::Monitor) {
    // 初始化UI
    ui->setupUi(this);
    setWindowIcon(QIcon("://monitor.png"));
    setWindowTitle(QString("UDP/COM Monitor"));
    // 初始化通信接口
    serialPort = new QSerialPort;
    udpSocket = new QUdpSocket(this);
    // 初始化UI
    ui->DataSourceList->addItem(QString("UDP"));
    ui->DataSourceList->addItem(QString("COM"));
    connect(ui->DataSourceList, SIGNAL(currentIndexChanged(int)), this, SLOT(SourceChanged(int)));
    ui->BaudrateList->addItem(QString("115200"));
    ui->BaudrateList->addItem(QString("57600"));
    ui->BaudrateList->addItem(QString("38400"));
    ui->BaudrateList->addItem(QString("19200"));
    ui->BaudrateList->addItem(QString("9600"));
    // 获取串口信息
    serialPortInfos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &serialPortInfo: serialPortInfos) {
        ui->COMList->addItem(serialPortInfo.portName());
    }
    QSerialPortInfo serialPortInfo = serialPortInfos[ui->COMList->currentIndex()];
    ui->SourceDetail->setText(QString("[%1]%2").arg(serialPortInfo.manufacturer(), serialPortInfo.description()));
    connect(ui->COMList, SIGNAL(currentIndexChanged(int)), this, SLOT(COMChanged(int)));
    // 设置UDP默认信息
    ui->IPAddressEdit->setText(UDP_ip);
    ui->PortEdit->setMinimum(0);
    ui->PortEdit->setMaximum(65535);
    ui->PortEdit->setValue(5555);
    // 默认显示UDP COM信息不可见
    ui->COMList->setVisible(false);
    ui->COMLabel->setVisible(false);
    ui->BaudrateList->setVisible(false);
    ui->BaudrateLabel->setVisible(false);
    ui->SourceDetail->setVisible(false);
    ui->SourceDetailLabel->setVisible(false);

    connect(ui->ConnectButton, SIGNAL(clicked()), this, SLOT(btn_connect()));

    // 初始化图表
    chart = new QChart();
    ui->Chart->setChart(chart);
    ui->Chart->setRenderHint(QPainter::Antialiasing);

    connect(ui->AddButton, SIGNAL(clicked()), this, SLOT(AddObserver()));
    connect(ui->DeleteButton, SIGNAL(clicked()), this, SLOT(DeleteObserve()));
    connect(ui->ChartSettings, SIGNAL(triggered()), this, SLOT(SetChart()));
    connect(ui->DataIn,SIGNAL(triggered()),this,SLOT(LoadSettings()));
    connect(ui->DataOut,SIGNAL(triggered()),this,SLOT(SaveSettings()));
    connect(ui->AboutMenu, SIGNAL(triggered()), this, SLOT(About()));

    // 置状态栏信息
    StatusLabel = new QLabel("Ready.");
    statusBar()->addPermanentWidget(StatusLabel, 1);
}

Monitor::~Monitor() {
    delete ui;
}

// 建立/断开连接
void Monitor::btn_connect() {
    SourceMode = ui->DataSourceList->currentIndex();
    switch (SourceMode) {
        // UDP
        case 0: {
            if (!isConnected) {
                UDP_port = ui->PortEdit->value();
                UDP_ip = ui->IPAddressEdit->text();
                udpSocket->bind(UDP_port);
                bool result = connect(udpSocket, SIGNAL(readyRead()), this, SLOT(DataReceived()));
                if (!result) {
                    QMessageBox::information(this, QString("ERROR"), QString("UDP Socket Create ERROR!"));
                    return;
                }
                StatusLabel->setText(QString("IP:%1 Port:%2 Connected.").arg(UDP_ip).arg(UDP_port));
                ui->ConnectButton->setText(QString("Disconnect"));

                ui->DataSourceList->setEnabled(false);
                ui->IPAddressEdit->setEnabled(false);
                ui->PortEdit->setEnabled(false);

                isConnected = true;
            } else {
                udpSocket->close();
                disconnect(udpSocket, SIGNAL(readyRead()));
                ui->ConnectButton->setText(QString("Connect"));
                StatusLabel->setText(QString("Ready."));

                ui->DataSourceList->setEnabled(true);
                ui->IPAddressEdit->setEnabled(true);
                ui->PortEdit->setEnabled(true);

                isConnected = false;
            }
            break;
        }
        // COM
        case 1: {
            if (!isConnected) {
                COM_PortName = ui->COMList->currentText();
                COM_BaudRate = mBaudRateList[ui->BaudrateList->currentIndex()];
                serialPort->setPortName(COM_PortName);
                serialPort->setBaudRate(COM_BaudRate);
                serialPort->setParity(QSerialPort::NoParity);
                serialPort->setDataBits(QSerialPort::Data8);
                serialPort->setStopBits(QSerialPort::OneStop);
                serialPort->setFlowControl(QSerialPort::NoFlowControl);
                bool result = serialPort->open(QIODevice::ReadWrite);
                if (!result) {
                    QMessageBox::information(this, QString("ERROR"), QString("COM Connect Create ERROR!"));
                    return;
                }
                connect(serialPort, SIGNAL(readyRead()), this, SLOT(DataReceived()));
                StatusLabel->setText(QString("%1 BaudRate:%2 Connected.").arg(ui->COMList->currentText()).arg(
                        mBaudRateList[ui->BaudrateList->currentIndex()]));
                ui->ConnectButton->setText(QString("Disconnect"));

                ui->DataSourceList->setEnabled(false);
                ui->COMList->setEnabled(false);
                ui->BaudrateList->setEnabled(false);

                isConnected = true;
            } else {
                serialPort->close();
                disconnect(serialPort, SIGNAL(readyRead()));
                ui->ConnectButton->setText(QString("Connect"));
                StatusLabel->setText(QString("Ready."));
                ui->DataSourceList->setEnabled(true);
                ui->COMList->setEnabled(true);
                ui->BaudrateList->setEnabled(true);
                isConnected = false;
            }
            break;
        }
        default:
            break;
    }
}

// 数据接收回调函数
void Monitor::DataReceived() {
    switch (SourceMode) {
        // UDP
        case 0: {
            while (udpSocket->hasPendingDatagrams()) {
                // 取UDP数据
                QByteArray datagram;
                datagram.resize(int(udpSocket->pendingDatagramSize()));
                udpSocket->readDatagram(datagram.data(), datagram.size());
                QString msg = datagram.data();
                ui->RawData->append(msg);
                // 数据过滤
                QStringList msgList = msg.split(",");
                if (msgList.size() == 2) {
                    for (auto &i: ChartList) {
                        if (i.ChartName == msgList[0]) {
                            i.ChartData.append(msgList.at(1).toDouble());
                        }
                    }
                }
                for (auto &i: ChartList) {
                    // 刷新Chart
                    while (i.ChartData.size() > (CHART_ADAPTER_ON ? MAX_ADA_X : MAX_FIX_X)) {
                        i.ChartData.removeFirst();
                    }
                    // 图表自适应大小
                    i.ChartSeries->clear();
                    double max = 0;
                    double min = 0;
                    for (int j = 0; j < i.ChartData.size(); ++j) {
                        if (i.ChartData.at(j) > max) {
                            max = i.ChartData.at(j);
                        }
                        if (i.ChartData.at(j) < min) {
                            min = i.ChartData.at(j);
                        }
                        i.ChartSeries->append(j, i.ChartData.at(j));
                    }
                    chart->axes(Qt::Horizontal).first()->setRange(0, MAX_ADA_X);
                    if (CHART_ADAPTER_ON) {
                        chart->axes(Qt::Vertical).first()->setRange(min - 10, max + 10);
                    }
                }
            }
            break;
        }
            // COM
        case 1: {
            QByteArray data = serialPort->readLine();
            if (!data.isEmpty()) {
                // 取串口数据
                QString strData = QString(data);
                Serial_buff.append(strData);
                if (!data.contains("\n")) {
                    return;
                }
                ui->RawData->insertPlainText(Serial_buff);
                // 数据过滤
                QStringList msgList = Serial_buff.split(",");
                if (msgList.size() == 2) {
                    for (auto &i: ChartList) {
                        if (i.ChartName == msgList[0]) {
                            i.ChartData.append(msgList.at(1).toDouble());
                        }
                    }
                }
                Serial_buff.clear();
                for (auto &i: ChartList) {
                    // 刷新Chart
                    while (i.ChartData.size() > (CHART_ADAPTER_ON ? MAX_ADA_X : MAX_FIX_X)) {
                        i.ChartData.removeFirst();
                    }
                    // 图表自适应大小
                    i.ChartSeries->clear();
                    double max = 0;
                    double min = 0;
                    for (int j = 0; j < i.ChartData.size(); ++j) {
                        if (i.ChartData.at(j) > max) {
                            max = i.ChartData.at(j);
                        }
                        if (i.ChartData.at(j) < min) {
                            min = i.ChartData.at(j);
                        }
                        i.ChartSeries->append(j, i.ChartData.at(j));
                    }
                    chart->axes(Qt::Horizontal).first()->setRange(0, MAX_ADA_X);
                    if (CHART_ADAPTER_ON) {
                        chart->axes(Qt::Vertical).first()->setRange(min - 10, max + 10);
                    }
                }
            }
            break;
        }
    }
}

// 切换COM口时显示详细信息
void Monitor::COMChanged(int index) {
    QSerialPortInfo serialPortInfo = serialPortInfos[index];
    ui->SourceDetail->setText(QString("[%1]%2").arg(serialPortInfo.manufacturer(), serialPortInfo.description()));
}

// 切换源时更改可视
void Monitor::SourceChanged(int index) {
    switch (index) {
        case 0:
            ui->COMList->setVisible(false);
            ui->COMLabel->setVisible(false);
            ui->BaudrateList->setVisible(false);
            ui->BaudrateLabel->setVisible(false);
            ui->SourceDetail->setVisible(false);
            ui->SourceDetailLabel->setVisible(false);
            ui->IPAddressEdit->setVisible(true);
            ui->IPAddressLabel->setVisible(true);
            ui->PortEdit->setVisible(true);
            ui->PortLabel->setVisible(true);
            break;
        case 1:
            ui->COMList->setVisible(true);
            ui->COMLabel->setVisible(true);
            ui->BaudrateList->setVisible(true);
            ui->BaudrateLabel->setVisible(true);
            ui->SourceDetail->setVisible(true);
            ui->SourceDetailLabel->setVisible(true);
            ui->IPAddressEdit->setVisible(false);
            ui->IPAddressLabel->setVisible(false);
            ui->PortEdit->setVisible(false);
            ui->PortLabel->setVisible(false);
            break;
        default:
            break;
    }
}

// 画布属性设置
void Monitor::SetChart() {
    auto *dialog = new SettingsDialog(this);
    int rtn = dialog->exec();
    if (rtn == QDialog::Accepted) {
        CHART_ADAPTER_ON = dialog->adaptive;
        if(chart->axes(Qt::Horizontal).empty() || chart->axes(Qt::Vertical).empty()){
            QMessageBox::warning(nullptr, "WARNING", "请先添加观察者");
            return;
        }
        if (!CHART_ADAPTER_ON) {
            MAX_FIX_X = dialog->MAX_X;
            MAX_FIX_Y = dialog->MAX_Y;
            MIN_FIX_Y = dialog->MIN_Y;
            chart->axes(Qt::Horizontal).first()->setRange(0, MAX_FIX_X);
            chart->axes(Qt::Vertical).first()->setRange(MIN_FIX_Y, MAX_FIX_Y);
        } else {
            chart->axes(Qt::Horizontal).first()->setRange(0, MAX_ADA_X);
        }
    }
    delete dialog;
}

// 添加一个观察者
void Monitor::AddObserver() {
    auto *dialog = new ObserverDialog(this);
    int rtn = dialog->exec();
    if (rtn == QDialog::Accepted) {
        // 规则命名检查
        for (auto &i: ChartList) {
            if (i.ChartName == dialog->name || i.ChartName == "") {
                QMessageBox::warning(nullptr, "ERROR", "已添加相同名称的观察者");
                return;
            }
        }
        // 添加UI
        auto *WContainerItem = new QListWidgetItem(ui->ObservedList);
        WContainerItem->setSizeHint(QSize(40, 50));
        auto *WContainer = new ObserverItem(ui->ObservedList);
        WContainer->checkBox->setChecked(true);
        connect(WContainer->checkBox,SIGNAL(stateChanged(int)),this,SLOT(CheckBoxChanged(int)));
        WContainer->setItemName(dialog->name);
        WContainer->setItemColor(QString("QLabel{background-color:%1;}").arg(dialog->color));
        ui->ObservedList->setItemWidget(WContainerItem, WContainer);
        // 新建ChartItem
        auto *chartitem = new ChartItem();
        chartitem->setName(dialog->name);
        chartitem->setColor(dialog->color);
        chartitem->ChartSeries->setColor(QColor(chartitem->ChartColor));
        chartitem->start();
        chart->addSeries(chartitem->ChartSeries);
        chart->createDefaultAxes();
        ChartList.append(*chartitem);
    }
    delete dialog;
}

// 删除一个观察者
void Monitor::DeleteObserve() {
    auto *checkBox = ui->ObservedList->itemWidget(ui->ObservedList->currentItem())->findChild<QCheckBox *>("checkBox");
    qDebug() << checkBox->text();
    for (int i = 0; i < ChartList.size(); i++) {
        if (ChartList[i].ChartName == checkBox->text()) {
            chart->removeSeries(ChartList[i].ChartSeries);
            ChartList.removeAt(i);
            break;
        }
    }
    ui->ObservedList->removeItemWidget(ui->ObservedList->currentItem());
    delete ui->ObservedList->currentItem();
}

// 关于界面
void Monitor::About() {
    QMessageBox::about(this, "About", "\nHangZhouDianZiUniversity\nZZZCY");
}

// 观察者可视变化
void Monitor::CheckBoxChanged(int a){
    qDebug()<<"CHANGED!";
    for(int i=0;i<ui->ObservedList->count();i++){
        if(ui->ObservedList->itemWidget(ui->ObservedList->item(i))->findChild<QCheckBox *>("checkBox")->isChecked()){
            for (auto &j: ChartList) {
                if (j.ChartName == ui->ObservedList->itemWidget(ui->ObservedList->item(i))->findChild<QCheckBox *>("checkBox")->text()) {
                    j.start();
                    chart->addSeries(j.ChartSeries);
                }
            }
        }
        else{
            for (auto &j: ChartList) {
                if (j.ChartName == ui->ObservedList->itemWidget(ui->ObservedList->item(i))->findChild<QCheckBox *>("checkBox")->text()) {
                    j.finish();
                    chart->removeSeries(j.ChartSeries);
                }
            }
        }
    }
}

// 读入Json设置
void Monitor::LoadSettings(){
    qDebug()<<"Loading...";
    QFile file("settings.json");
    file.open(QFile::ReadOnly);
    QJsonDocument mJsonDoc = QJsonDocument::fromJson(file.readAll());
    QJsonObject mJson = mJsonDoc.object();
    CHART_ADAPTER_ON = mJson.value("CHART_ADAPTER_ON").toBool();
    MAX_FIX_X = mJson.value("MAX_FIX_X").toVariant().toInt();
    MAX_FIX_Y = mJson.value("MAX_FIX_Y").toVariant().toInt();
    MIN_FIX_Y = mJson.value("MIN_FIX_Y").toVariant().toInt();

    QMessageBox::information(this,"Monitor","加载设置成功");
}

// 导出Json设置
void Monitor::SaveSettings(){
    qDebug()<<"Saving...";
    QJsonObject mJson;
    //Window Size
    mJson.insert("CHART_ADAPTER_ON",CHART_ADAPTER_ON);
    mJson.insert("MAX_FIX_X",MAX_FIX_X);
    mJson.insert("MAX_FIX_Y",MAX_FIX_Y);
    mJson.insert("MIN_FIX_Y",MIN_FIX_Y);
    //Source Config
    mJson.insert("Source",SourceMode);
    //UDP Config
    mJson.insert("UDP_IP",UDP_ip);
    mJson.insert("UDP_PORT",UDP_port);
    //COM Config
    mJson.insert("COM_PortName",COM_PortName);
    mJson.insert("COM_BaudRate",COM_BaudRate);
    //ObserverList
    QJsonArray sub;
    for(auto & i : ChartList){
        QJsonObject pchart;
        pchart.insert("NAME",i.ChartName);
        pchart.insert("COLOR",i.ChartColor);
        sub.append(pchart);
    }
    mJson.insert("CHART",sub);

    QJsonDocument mJsonDoc(mJson);
    QByteArray json = mJsonDoc.toJson();
    QFile file("settings.json");
    file.open(QFile::WriteOnly);
    file.write(json);
    file.close();

    QMessageBox::information(this,"Monitor","保存设置成功");
}
