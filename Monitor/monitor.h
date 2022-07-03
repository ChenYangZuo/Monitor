#ifndef MONITOR_H
#define MONITOR_H

#include <QMainWindow>
#include <QLabel>
#include <QComboBox>
#include <QTextBrowser>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QUdpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Monitor; }
QT_END_NAMESPACE

class Monitor : public QMainWindow
{
    Q_OBJECT

public:
    Monitor(QWidget *parent = nullptr);
    ~Monitor();

private:
    Ui::Monitor *ui;
    QSerialPort *serialPort;
    QUdpSocket *udpSocket;

    int port;
    bool isConnected = false;
    bool Serial_On = false;

public slots:
    void btn_connect();
    void DataReceived();
};
#endif // MONITOR_H
