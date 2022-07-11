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
#include <QListWidget>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>

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
    Ui::Monitor *ui;
    QList<QSerialPortInfo> serialPortInfos;
    QSerialPort *serialPort;
    QString Serial_buff = "";
    QUdpSocket *udpSocket;

    QString CSV_Filename;
    QFile CSV_File;

    bool isConnected = false;
    int SourceMode = 0;

    QString UDP_ip = "127.0.0.1";
    int UDP_port = 5555;
    QString COM_PortName = "";
    int COM_BaudRate = 9600;

    QChart *chart;
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

    void CheckBoxChanged(int);

    void About();

    void SaveSettings();

    void LoadSettings();

    void GenerateShot();

    bool RuleCheck_Name(const QString&);

    void deleteSeedSlot();

private slots:
    void on_ObservedList_customContextMenuRequested(const QPoint &pos);
};

struct ChartItem{
    QList<double> ChartData;
    QSplineSeries *ChartSeries;
    QString ChartName;
    QString ChartColor;
    bool ChartVisible = false;
};
Q_DECLARE_METATYPE(ChartItem)

#endif // MONITOR_H
