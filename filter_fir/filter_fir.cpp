#include "filter_fir.h"
#include <cmath>
#include <complex>
#include <QFile>
#include <QDir>
#include <QCoreApplication>
#include <QDebug>

double filter_fir(QList<double>& buffer, double data){
    QList<double> B = {
        0.01371888807641,  0.04088447702935, 0.002712877770901, -0.01457739134178,
        0.006641859048837, -0.03012145345071, -0.05578417902593,  0.02234928048926,
        0.05649875259341, 0.002500211803031,  0.04347509897176,  0.07327029467123,
        -0.1332644738461,  -0.2454423190008,  0.07548126994108,   0.3403092785529,
        0.07548126994108,  -0.2454423190008,  -0.1332644738461,  0.07327029467123,
        0.04347509897176, 0.002500211803031,  0.05649875259341,  0.02234928048926,
        -0.05578417902593, -0.03012145345071, 0.006641859048837, -0.01457739134178,
        0.002712877770901,  0.04088447702935,  0.01371888807641
    };

    buffer.append(data);
    if(buffer.size()<B.size()){
        return 0;
    }
    while(buffer.size()>B.size()){
        buffer.removeFirst();
    }

    double temp = 0;
    for(int i=0;i<buffer.size();i++){
        temp += buffer.at(i)*B.at(i);
    }
    return temp;
}
