#include <QDebug>
#include <QMessageBox>
#include "monitor.h"
#include "ui_monitor.h"
#include "settingsdialog.h"
#include "observeritem.h"
#include "observerdialog.h"

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
    ui->IPAddressEdit->setText("127.0.0.1");
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
    series = new QSplineSeries();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setRange(0, MAX_ADA_X);
    ui->Chart->setChart(chart);
    ui->Chart->setRenderHint(QPainter::Antialiasing);

    connect(ui->AddButton, SIGNAL(clicked()), this, SLOT(AddObserver()));
    connect(ui->DeleteButton, SIGNAL(clicked()), this, SLOT(DeleteObserve()));
    connect(ui->ChartSettings, SIGNAL(triggered()), this, SLOT(SetChart()));
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
                port = ui->PortEdit->value();
                udpSocket->bind(port);
                bool result = connect(udpSocket, SIGNAL(readyRead()), this, SLOT(DataReceived()));
                if (!result) {
                    QMessageBox::information(this, QString("ERROR"), QString("UDP Socket Create ERROR!"));
                    return;
                }
                StatusLabel->setText(QString("IP:%1 Port:%2 Connected.").arg(ui->IPAddressEdit->text()).arg(port));
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
                serialPort->setPortName(ui->COMList->currentText());
                serialPort->setBaudRate(mBaudRateList[ui->BaudrateList->currentIndex()]);
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
                if(msgList.size()==2){
                    DataMap.value(msgList[0])->append(msgList.at(1).toDouble());
                }

                // 刷新Chart
                while (DataMap.value(msgList[0])->size() > (CHART_ADAPTER_ON ? MAX_ADA_X : MAX_FIX_X)) {
                    DataMap.value(msgList[0])->removeFirst();
                }
                // 图表自适应大小
                SeriesMap.value(msgList[0])->clear();
                double max = 0;
                double min = 0;
                for (int i = 0; i < DataMap.value(msgList[0])->size(); ++i) {
                    if (DataMap.value(msgList[0])->at(i) > max) {
                        max = DataMap.value(msgList[0])->at(i);
                    }
                    if (DataMap.value(msgList[0])->at(i) < min) {
                        min = DataMap.value(msgList[0])->at(i);
                    }
                    SeriesMap.value(msgList[0])->append(i, DataMap.value(msgList[0])->at(i));
                }
                if (CHART_ADAPTER_ON) {
                    chart->axes(Qt::Vertical).first()->setRange(min - 10, max + 10);
                }
            }
            break;
        }
        // COM
        /*
        case 1: {
            QByteArray data = serialPort->readLine();
            if (!data.isEmpty()) {
                // 取串口数据
                QString strData = QString(data);
                Serial_buff.append(strData);
                if (!data.contains("\n")) {
                    return;
                }
                // 数据过滤
                ui->RawData->insertPlainText(Serial_buff);
                QRegExp rx("(?:\\[)(.*)(?:\\])");
                rx.indexIn(Serial_buff, 0);
                double finalSignal = rx.cap(0).replace("[", "").replace("]", "").toDouble();

                ChartData.append(finalSignal);
//                qDebug() << Serial_buff << rx.cap(0);
                Serial_buff.clear();

                // 刷新Chart
                while (ChartData.size() > (CHART_ADAPTER_ON ? MAX_ADA_X : MAX_FIX_X)) {
                    ChartData.removeFirst();
                }
                // 图表自适应大小
                series->clear();
                double max = 0;
                double min = 0;
                for (int i = 0; i < ChartData.size(); ++i) {
                    if (ChartData.at(i) > max) {
                        max = ChartData.at(i);
                    }
                    if (ChartData.at(i) < min) {
                        min = ChartData.at(i);
                    }
                    series->append(i, ChartData.at(i));
                }
                if (CHART_ADAPTER_ON) {
                    chart->axes(Qt::Vertical).first()->setRange(min - 10, max + 10);
                }
            }
            break;
        }
         */
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
        auto *WContainerItem = new QListWidgetItem(ui->ObservedList);
        WContainerItem->setSizeHint(QSize(40, 50));
        auto *WContainer = new ObserverItem(ui->ObservedList);
        WContainer->setItemName(dialog->name);
        WContainer->setItemIndex(temp++);
        WContainer->setItemColor(QString("QLabel{background-color:%1;}").arg(dialog->color));
        ui->ObservedList->setItemWidget(WContainerItem, WContainer);
        //TODO 配合线的容器修改索引
        QList<double> *ChartData = new QList<double>;
        QSplineSeries *ChartSeries = new QSplineSeries;
        DataMap.insert(dialog->name,ChartData);
        SeriesMap.insert(dialog->name,ChartSeries);
        chart->addSeries(ChartSeries);
    }
    delete dialog;
}

// 删除一个观察者
void Monitor::DeleteObserve() {
    qDebug() << "DEL";
    ui->ObservedList->removeItemWidget(ui->ObservedList->currentItem());
    delete ui->ObservedList->currentItem();
}

// 关于界面
void Monitor::About() {
    QMessageBox::about(nullptr, "About", "HangZhouDianZiUniversity ZZZCY");
}
