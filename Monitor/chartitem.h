#ifndef CHARTITEM_H
#define CHARTITEM_H

#include <QtCharts>


class ChartItem {

public:
    ChartItem();
    bool isStart = false;
    QString ChartName;
    QString ChartColor;
    QList<double> ChartData;
    QSplineSeries *ChartSeries;

    void setName(QString);
    void setColor(QString);
    void setChartData(QList<double>);
    void setChartSeries(QSplineSeries);
    void start();
    void finish();

};

#endif // CHARTITEM_H
