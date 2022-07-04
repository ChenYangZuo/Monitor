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
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>

QT_BEGIN_NAMESPACE
namespace Ui { class Monitor; }
QT_END_NAMESPACE

class Monitor : public QMainWindow {
Q_OBJECT

public:
    Monitor(QWidget *parent = nullptr);

    ~Monitor();

private:
    Ui::Monitor *ui;
    QList<QSerialPortInfo> serialPortInfos;
    QSerialPort *serialPort;
    QUdpSocket *udpSocket;

    int port = 5555;
    bool isConnected = false;
    int SourceMode = 0;

    QChart *chart;
    QList<double> ChartData;
    QSplineSeries *series;
    QString Serial_buff = "";

    QList<long> mBaudRateList = {115200, 57600, 38400, 19200, 9600};

    QLabel *StatusLabel;

public slots:

    void btn_connect();

    void DataReceived();

    void COMChanged(int);

    void SourceChanged(int);

    void About();
};

#endif // MONITOR_H
