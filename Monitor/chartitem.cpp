#include "chartitem.h"

ChartItem::ChartItem() {
    ChartSeries = new QSplineSeries();
}

void ChartItem::setName(QString name){
    ChartName = name;
}

void ChartItem::setColor(QString color) {
    ChartColor = color;
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

void ChartItem::finish(){
    isStart = false;
}