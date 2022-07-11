#include <QDebug>
#include <QMessageBox>
#include <QVariant>
#include "monitor.h"
#include "ui_monitor.h"
#include "settingsdialog.h"
#include "observeritem.h"
#include "observerdialog.h"

// 初始化
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
    // 初始化图表
    chart = new QChart();
    ui->Chart->setChart(chart);
    ui->Chart->setRenderHint(QPainter::Antialiasing);
    // 绑定槽
    connect(ui->ConnectButton, SIGNAL(clicked()), this, SLOT(btn_connect()));
    connect(ui->AddButton, SIGNAL(clicked()), this, SLOT(AddObserver()));
    connect(ui->DeleteButton, SIGNAL(clicked()), this, SLOT(DeleteObserve()));
    connect(ui->ChartSettings, SIGNAL(triggered()), this, SLOT(SetChart()));
    connect(ui->DataIn, SIGNAL(triggered()), this, SLOT(LoadSettings()));
    connect(ui->DataOut, SIGNAL(triggered()), this, SLOT(SaveSettings()));
    connect(ui->GenerateShot, SIGNAL(triggered()), this, SLOT(GenerateShot()));
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
                CSV_Filename = QString("./rawdata/raw-%1.csv").arg(
                        QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss"));
                CSV_File.setFileName(CSV_Filename);
                if (CSV_File.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
                    QTextStream in(&CSV_File);
                    QString strText("");
                    strText = QString("Time,") + QString("Data");
                    in << strText << "/n";
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
                CSV_File.close();
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
                CSV_Filename = QString("./rawdata/raw-%1.csv").arg(
                        QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss"));
                CSV_File.setFileName(CSV_Filename);
                if (CSV_File.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
                    QTextStream in(&CSV_File);
                    QString strText("");
                    strText = QString("Time,") + QString("Data");
                    in << strText << '\n';
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
                CSV_File.close();
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
                QString CurrentTime = QTime::currentTime().toString("HH:mm:ss.zzz");
                ui->RawData->append(QString("[%1]%2").arg(CurrentTime, msg));
                QTextStream in(&CSV_File);
                QString strMessage = QString(u8"%1,%2").arg(CurrentTime, msg);
                in << strMessage << '\n';
                // 数据过滤
                QStringList msgList = msg.split(",");
                if (msgList.size() == 2) {
                    for (auto &i: ChartList) {
                        if (i.getName() == msgList[0]) {
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
                QString CurrentTime = QTime::currentTime().toString("HH:mm:ss.zzz");
                ui->RawData->append(QString("[%1]%2").arg(CurrentTime, Serial_buff));
                QTextStream in(&CSV_File);
                QString strMessage = QString(u8"%1,%2").arg(CurrentTime, Serial_buff);
                in << strMessage << '\n';
                // 数据过滤
                QStringList msgList = Serial_buff.split(",");
                if (msgList.size() == 2) {
                    for (auto &i: ChartList) {
                        if (i.getName() == msgList[0]) {
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
        if (chart->axes(Qt::Horizontal).empty() || chart->axes(Qt::Vertical).empty()) {
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
        for(int i=0;i<ui->ObservedList->count();i++) {
            if (ui->ObservedList->item(i)->data(Qt::UserRole).value<ChartItem>().ChartName == dialog->name) {
                QMessageBox::warning(nullptr, "ERROR", "已添加相同名称的观察者");
                return;
            }
            if (ui->ObservedList->item(i)->data(Qt::UserRole).value<ChartItem>().ChartName == "") {
                QMessageBox::warning(nullptr, "ERROR", "观察者名称不能为空");
                return;
            }
        }

        // 新建ChartItem
        struct ChartItem chartitem;
        chartitem.ChartName = dialog->name;
        chartitem.ChartColor = dialog->color;
        chartitem.ChartSeries->setColor(QColor(chartitem.ChartColor));
        chartitem.ChartVisible = true;
        chart->addSeries(chartitem.ChartSeries);
        chart->createDefaultAxes();

        // 添加UI
        auto *WidgetContainerItem = new QListWidgetItem(ui->ObservedList);
        WidgetContainerItem->setSizeHint(QSize(40, 50));
        auto *WidgetContainer = new ObserverItem(ui->ObservedList);
        WidgetContainer->setCheckState(Qt::Checked);
        connect(WidgetContainer->getCheckBox(), SIGNAL(stateChanged(int)), this, SLOT(CheckBoxChanged(int)));
        WidgetContainer->setItemName(dialog->name);
        WidgetContainer->setItemColor(QString("QLabel{background-color:%1;}").arg(dialog->color));
        ui->ObservedList->setItemWidget(WidgetContainerItem, WidgetContainer);
        WidgetContainerItem->setData(Qt::UserRole,QVariant::fromValue(chartitem));
    }
    delete dialog;
}

// 删除一个观察者
void Monitor::DeleteObserve() {
    auto *checkBox = ui->ObservedList->itemWidget(ui->ObservedList->currentItem())->findChild<QCheckBox *>("checkBox");
    qDebug() << checkBox->text();

    for (int i = 0; i < ChartList.size(); i++) {
        if (ChartList[i].getName() == checkBox->text()) {
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
    QMessageBox::about(this, "About", "\nHangzhouDianziUniversity\nZZZCY");
}

// 观察者可视变化
void Monitor::CheckBoxChanged(int a) {
    qDebug() << "CHANGED!";
    for (int i = 0; i < ui->ObservedList->count(); i++) {
        if (ui->ObservedList->itemWidget(ui->ObservedList->item(i))->findChild<QCheckBox *>("checkBox")->isChecked()) {
            for (auto &j: ChartList) {
                if (j.getName() == ui->ObservedList->itemWidget(ui->ObservedList->item(i))->findChild<QCheckBox *>(
                        "checkBox")->text()) {
                    j.start();
                    chart->addSeries(j.ChartSeries);
                }
            }
        } else {
            for (auto &j: ChartList) {
                if (j.getName() == ui->ObservedList->itemWidget(ui->ObservedList->item(i))->findChild<QCheckBox *>(
                        "checkBox")->text()) {
                    j.finish();
                    chart->removeSeries(j.ChartSeries);
                }
            }
        }
    }
}

// 读入Json设置
void Monitor::LoadSettings() {
    qDebug() << "Loading...";

    QFile file("settings.json");
    file.open(QFile::ReadOnly);
    QJsonDocument mJsonDoc = QJsonDocument::fromJson(file.readAll());
    QJsonObject mJson = mJsonDoc.object();
    //Window Size
    CHART_ADAPTER_ON = mJson.value("CHART_ADAPTER_ON").toBool();
    MAX_FIX_X = mJson.value("MAX_FIX_X").toVariant().toInt();
    MAX_FIX_Y = mJson.value("MAX_FIX_Y").toVariant().toInt();
    MIN_FIX_Y = mJson.value("MIN_FIX_Y").toVariant().toInt();
    //Source Config
    SourceMode = mJson.value("Source").toVariant().toInt();
    ui->DataSourceList->setCurrentIndex(SourceMode);
    //UDP Config
    UDP_ip = mJson.value("UDP_IP").toString();
    UDP_port = mJson.value("UDP_PORT").toVariant().toInt();
    //COM Config
    COM_PortName = mJson.value("COM_PortName").toString();
    COM_BaudRate = mJson.value("COM_BaudRate").toVariant().toInt();
    ui->COMList->setCurrentText(COM_PortName);
    ui->BaudrateList->setCurrentText(QString("%1").arg(COM_BaudRate));
    //ObserverList
    QJsonArray subObj = mJson.value("CHART").toArray();
    for (auto &&sub: subObj) {
        QString name = sub.toObject().value("NAME").toString();
        QString color = sub.toObject().value("COLOR").toString();
        if (!RuleCheck_Name(name)) {
            continue;
        }
        // 添加UI
        auto *WContainerItem = new QListWidgetItem(ui->ObservedList);
        WContainerItem->setSizeHint(QSize(40, 50));
        auto *WContainer = new ObserverItem(ui->ObservedList);
        WContainer->setCheckState(Qt::Checked);
        connect(WContainer->getCheckBox(), SIGNAL(stateChanged(int)), this, SLOT(CheckBoxChanged(int)));
        WContainer->setItemName(name);
        WContainer->setItemColor(QString("QLabel{background-color:%1;}").arg(color));
        ui->ObservedList->setItemWidget(WContainerItem, WContainer);
        // 新建ChartItem
        auto *chartitem = new ChartItem();
        chartitem->setName(name);
        chartitem->setColor(color);
        chartitem->ChartSeries->setColor(QColor(chartitem->getColor()));
        chartitem->start();
        chart->addSeries(chartitem->ChartSeries);
        chart->createDefaultAxes();
        ChartList.append(*chartitem);
    }
    if (!CHART_ADAPTER_ON) {
        chart->axes(Qt::Horizontal).first()->setRange(0, MAX_FIX_X);
        chart->axes(Qt::Vertical).first()->setRange(MIN_FIX_Y, MAX_FIX_Y);
    } else {
        chart->axes(Qt::Horizontal).first()->setRange(0, MAX_ADA_X);
    }
    QMessageBox::information(this, "Monitor", "加载设置成功");
}

// 导出Json设置
void Monitor::SaveSettings() {
    qDebug() << "Saving...";
    QJsonObject mJson;
    //Window Size
    mJson.insert("CHART_ADAPTER_ON", CHART_ADAPTER_ON);
    mJson.insert("MAX_FIX_X", MAX_FIX_X);
    mJson.insert("MAX_FIX_Y", MAX_FIX_Y);
    mJson.insert("MIN_FIX_Y", MIN_FIX_Y);
    //Source Config
    mJson.insert("Source", SourceMode);
    //UDP Config
    mJson.insert("UDP_IP", UDP_ip);
    mJson.insert("UDP_PORT", UDP_port);
    //COM Config
    mJson.insert("COM_PortName", COM_PortName);
    mJson.insert("COM_BaudRate", COM_BaudRate);
    //ObserverList
    QJsonArray sub;
    for (auto &i: ChartList) {
        QJsonObject pchart;
        pchart.insert("NAME", i.getName());
        pchart.insert("COLOR", i.getColor());
        sub.append(pchart);
    }
    mJson.insert("CHART", sub);

    QJsonDocument mJsonDoc(mJson);
    QByteArray json = mJsonDoc.toJson();
    QFile file("settings.json");
    file.open(QFile::WriteOnly);
    file.write(json);
    file.close();

    QMessageBox::information(this, "Monitor", "保存设置成功");
}

// 生成截图
void Monitor::GenerateShot() {
    QPixmap p = ui->Chart->grab();
    QImage img = p.toImage();
    QString path = QFileDialog::getSaveFileName(this, "Save as", "/", "PNG(*.png)");
    img.save(path);
    QMessageBox::information(this, "Monitor", "截图已生成");
}

// 命名规则检查
bool Monitor::RuleCheck_Name(const QString &name) {
    // 规则命名检查
    for (auto &i: ChartList) {
        if (i.getName() == name) {
            return false;
        }
    }
    return true;
}

void Monitor::on_ObservedList_customContextMenuRequested(const QPoint &pos) {
    QListWidgetItem *curItem = ui->ObservedList->itemAt(pos);
    auto *checkBox = ui->ObservedList->itemWidget(curItem)->findChild<QCheckBox *>("checkBox");

    qDebug() << checkBox->text();

    auto *popMenu = new QMenu(this);
    auto *deleteSeed = new QAction(tr("Delete"), this);
    auto *clearSeeds = new QAction(tr("Clear"), this);
    popMenu->addAction(deleteSeed);
    popMenu->addAction(clearSeeds);
    connect(deleteSeed, SIGNAL(triggered()), this, SLOT(deleteSeedSlot()));
    popMenu->exec(QCursor::pos());
    delete popMenu;
    delete deleteSeed;
    delete clearSeeds;
}

void Monitor::deleteSeedSlot() {
    int ch = QMessageBox::warning(nullptr, "Warning",
                                  "Are you sure to delete seed ?",
                                  QMessageBox::Yes | QMessageBox::No,
                                  QMessageBox::No);

    if (ch != QMessageBox::Yes)
        return;

    QListWidgetItem *item = ui->ObservedList->currentItem();
    if (item == nullptr)
        return;

    int curIndex = ui->ObservedList->row(item);
    ui->ObservedList->takeItem(curIndex);
    delete item;
}
