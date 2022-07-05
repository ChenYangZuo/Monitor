#include "udpserver.h"
#include <cmath>

UdpServer::UdpServer(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(QString("UDP Server"));
    TimerLabel = new QLabel(QString("计时器"));
    TextLineEdit = new QLineEdit();
    StartBtn = new QPushButton(QString("开始"));

    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(TimerLabel);
    mainLayout->addWidget(TextLineEdit);
    mainLayout->addWidget(StartBtn);

    connect(StartBtn,SIGNAL(clicked()),this,SLOT(StartBtnClicked()));

    port = 5555;
    isStarted = false;
    udpSocket = new QUdpSocket(this);
    timer = new QTimer(this);

    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));

}

UdpServer::~UdpServer()
{
}

void UdpServer::StartBtnClicked(){
    if(!isStarted){
        StartBtn->setText(QString("停止"));
        timer->start(100);
        isStarted = true;
    }
    else{
        StartBtn->setText(QString("开始"));
        timer->stop();
        isStarted = false;
    }
}

void UdpServer::timeout(){
//    QString msg = TextLineEdit->text();
//    QString msg = QString::number(sin(cnt)*100,'f',2);
    QString msg = QString("SIN,%1").arg(sin(cnt)*100);
    cnt += 0.2;
    int length = 0;
    if(msg==""){
        return;
    }
    if((length=udpSocket->writeDatagram(msg.toLatin1(),msg.length(),QHostAddress::Broadcast,port))!=msg.length()){
        return;
    }
    msg = QString("COS,%1").arg(cos(cnt)*100);
    length = 0;
    if((length=udpSocket->writeDatagram(msg.toLatin1(),msg.length(),QHostAddress::Broadcast,port))!=msg.length()){
        return;
    }
}
