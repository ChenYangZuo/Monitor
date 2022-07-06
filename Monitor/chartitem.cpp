#include "chartitem.h"

ChartItem::ChartItem() {
    ChartSeries = new QSplineSeries();
}

void ChartItem::setName(QString name){
    ChartName = name;
}

void ChartItem::setChartData(QList<double> data){
    ChartData = data;
}

void ChartItem::setChartSeries(QSplineSeries series){
    ChartSeries = &series;
}

void ChartItem::start(){
    isStart = true;
}
