#include "monitor.h"
#include <QDebug>
#include <QMessageBox>
#include "./ui_monitor.h"

Monitor::Monitor(QWidget *parent) : QMainWindow(parent) , ui(new Ui::Monitor) {
    ui->setupUi(this);

    serialPort = new QSerialPort;
    udpSocket = new QUdpSocket(this);

    ui->DataSourceList->addItem(QString("UDP"));
    ui->DataSourceList->addItem(QString("COM"));

    const auto serialPortInfos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &serialPortInfo: serialPortInfos) {
        ui->COMList->addItem(serialPortInfo.portName());
        ui->SourceDetail->setText(QString("[%1]%2").arg(serialPortInfo.manufacturer(),serialPortInfo.description()));
    }

    connect(ui->ConnectButton,SIGNAL(clicked()),this,SLOT(btn_connect()));
}

Monitor::~Monitor() {
    delete ui;
}

void Monitor::btn_connect() {
    if(Serial_On){
        if(!isConnected){
            serialPort->setPortName(QString("COM10"));
            serialPort->setBaudRate(115200);
            serialPort->setParity(QSerialPort::NoParity);
            serialPort->setDataBits(QSerialPort::Data8);
            serialPort->setStopBits(QSerialPort::OneStop);
            serialPort->setFlowControl(QSerialPort::NoFlowControl);
            serialPort->open(QIODevice::ReadWrite);
            connect(serialPort, SIGNAL(readyRead()),this,SLOT(DataReceived()));

            ui->ConnectButton->setText(QString("Disconnect"));
            isConnected = true;
        }
        else{
            serialPort->close();
            disconnect(serialPort,SIGNAL(readyRead()));
            ui->ConnectButton->setText(QString("Connect"));
            isConnected = false;
        }
    }
    else{
        if(!isConnected){
            port=5555;
            udpSocket->bind(port);
            bool result = connect(udpSocket,SIGNAL(readyRead()),this,SLOT(DataReceived()));
            if(!result){
                QMessageBox::information(this,QString("ERROR"),QString("UDP Socket Create ERROR!"));
                return;
            }
            ui->ConnectButton->setText(QString("Disconnect"));
            isConnected = true;
        }
        else{
            udpSocket->close();
            disconnect(udpSocket,SIGNAL(readyRead()));
            ui->ConnectButton->setText(QString("Connect"));
            isConnected = false;
        }
    }
}

void Monitor::DataReceived() {
    if(Serial_On){
        QByteArray data = serialPort->readAll();
        if(!data.isEmpty()){
            ui->RawData->insertPlainText(QString(data));
        }
    }
    else{
        while(udpSocket->hasPendingDatagrams()){
            QByteArray datagram;
            datagram.resize(udpSocket->pendingDatagramSize());
            udpSocket->readDatagram(datagram.data(),datagram.size());
            QString msg = datagram.data();
            ui->RawData->insertPlainText(msg);
        }
    }
}
