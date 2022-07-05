#ifndef CHARTITEM_H
#define CHARTITEM_H

#include <QtCharts>


class ChartItem {

public:
    ChartItem();
    QString ChartName;
    QList<double> ChartData;
    QSplineSeries *ChartSeries;

    void setName(QString);
    void setChartData(QList<double>);
    void setChartSeries(QSplineSeries);

};

#endif // CHARTITEM_H
