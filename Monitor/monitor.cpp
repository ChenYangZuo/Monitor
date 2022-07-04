#include "monitor.h"
#include <QDebug>
#include <QMessageBox>
#include "ui_monitor.h"

Monitor::Monitor(QWidget *parent) : QMainWindow(parent), ui(new Ui::Monitor) {
    ui->setupUi(this);

    setWindowTitle(QString("UDP/COM Monitor"));

    serialPort = new QSerialPort;
    udpSocket = new QUdpSocket(this);

    ui->DataSourceList->addItem(QString("UDP"));
    ui->DataSourceList->addItem(QString("COM"));
    connect(ui->DataSourceList, SIGNAL(currentIndexChanged(int)), this, SLOT(SourceChanged(int)));

    ui->BaudrateList->addItem(QString("115200"));
    ui->BaudrateList->addItem(QString("57600"));
    ui->BaudrateList->addItem(QString("38400"));
    ui->BaudrateList->addItem(QString("19200"));
    ui->BaudrateList->addItem(QString("9600"));

    serialPortInfos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &serialPortInfo: serialPortInfos) {
        ui->COMList->addItem(serialPortInfo.portName());
    }
    QSerialPortInfo serialPortInfo = serialPortInfos[ui->COMList->currentIndex()];
    ui->SourceDetail->setText(QString("[%1]%2").arg(serialPortInfo.manufacturer(), serialPortInfo.description()));

    ui->COMList->setVisible(false);
    ui->COMLabel->setVisible(false);
    ui->BaudrateList->setVisible(false);
    ui->BaudrateLabel->setVisible(false);
    ui->SourceDetail->setVisible(false);
    ui->SourceDetailLabel->setVisible(false);

    connect(ui->COMList, SIGNAL(currentIndexChanged(int)), this, SLOT(COMChanged(int)));

    ui->IPAddressEdit->setText("127.0.0.1");
    ui->PortEdit->setMinimum(0);
    ui->PortEdit->setMaximum(65535);
    ui->PortEdit->setValue(5555);

    connect(ui->ConnectButton, SIGNAL(clicked()), this, SLOT(btn_connect()));

    chart = new QChart();
    series = new QSplineSeries();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->axes(Qt::Vertical).first()->setRange(-125, 125);
    chart->axes(Qt::Horizontal).first()->setRange(0, 100);
    ui->Chart->setChart(chart);
    ui->Chart->setRenderHint(QPainter::Antialiasing);

    connect(ui->AboutMenu,SIGNAL(triggered()),this,SLOT(About()));

    StatusLabel = new QLabel("Ready.");
    statusBar()->addPermanentWidget(StatusLabel, 1);
}

Monitor::~Monitor() {
    delete ui;
}

void Monitor::btn_connect() {
    SourceMode = ui->DataSourceList->currentIndex();
    switch (SourceMode) {
        //UDP
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
            //COM
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

void Monitor::DataReceived() {
    switch (SourceMode) {
        case 0: {
            while (udpSocket->hasPendingDatagrams()) {
                QByteArray datagram;
                datagram.resize(int(udpSocket->pendingDatagramSize()));
                udpSocket->readDatagram(datagram.data(), datagram.size());
                QString msg = datagram.data();
                ui->RawData->append(msg);

                QRegExp rx("(?:\\[)(.*)(?:\\])");
                rx.indexIn(msg, 0);
                qDebug() << msg << rx.cap(0);
                double finalSignal = rx.cap(0).replace("[", "").replace("]", "").toDouble();
                ChartData.append(finalSignal);
                qDebug() << finalSignal;
                while (ChartData.size() > 80) {
                    ChartData.removeFirst();
                }
                series->clear();
                for (int i = 0; i < ChartData.size(); ++i) {
                    series->append(i, ChartData.at(i));
                }
            }
            break;
        }
        case 1: {
            QByteArray data = serialPort->readLine();
            if (!data.isEmpty()) {
                QString strData = QString(data);
                Serial_buff.append(strData);
                if (!data.contains("\n")) {
                    return;
                }
                ui->RawData->insertPlainText(Serial_buff);
                QRegExp rx("(?:\\[)(.*)(?:\\])");
                rx.indexIn(Serial_buff, 0);
                ChartData.append(rx.cap(0).replace("[", "").replace("]", "").toDouble());
                qDebug() << Serial_buff << rx.cap(0);
                Serial_buff.clear();

                //刷新Chart
                while (ChartData.size() > 100) {
                    ChartData.removeFirst();
                }
                series->clear();
                for (int i = 0; i < ChartData.size(); ++i) {
                    series->append(i, ChartData.at(i));
                }
            }
            break;
        }
    }
}

void Monitor::COMChanged(int index) {
    QSerialPortInfo serialPortInfo = serialPortInfos[index];
    ui->SourceDetail->setText(QString("[%1]%2").arg(serialPortInfo.manufacturer(), serialPortInfo.description()));
}

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

void Monitor::About(){
    QMessageBox::about(nullptr,"About","HangZhouDianZiUniversity ZZZCY");
}
