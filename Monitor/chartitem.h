#ifndef CHARTITEM_H
#define CHARTITEM_H

#include <QtCharts>


class ChartItem {

public:
    ChartItem();
    bool isStart = false;
    QString ChartName;
    QList<double> ChartData;
    QSplineSeries *ChartSeries;

    void setName(QString);
    void setChartData(QList<double>);
    void setChartSeries(QSplineSeries);
    void start();

};

#endif // CHARTITEM_H
