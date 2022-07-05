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

    bool CHART_ADAPTER_ON = true;
    const int MAX_ADA_X = 100;
    int MAX_FIX_X = 100;
    int MAX_FIX_Y = 50;
    int MIN_FIX_Y = -50;

private:
    int temp = 0;

    Ui::Monitor *ui;
    QList<QSerialPortInfo> serialPortInfos;
    QSerialPort *serialPort;
    QString Serial_buff = "";
    QUdpSocket *udpSocket;

    bool isConnected = false;
    int port = 5555;
    int SourceMode = 0;

    QChart *chart;
//    QList<double> ChartData;
//    QList<double> CosChartData;
    QSplineSeries *series;
    QMap<QString,QList<double>*> DataMap;
    QMap<QString,QSplineSeries*> SeriesMap;

    QList<long> mBaudRateList = {115200, 57600, 38400, 19200, 9600};

    QLabel *StatusLabel;

public slots:

    void btn_connect();

    void DataReceived();

    void COMChanged(int);

    void SourceChanged(int);

    void SetChart();

    void AddObserver();

    void DeleteObserve();

    void About();
};

#endif // MONITOR_H
