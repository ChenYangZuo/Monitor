#ifndef FILTER_FIR_H
#define FILTER_FIR_H

#include "filter_fir_global.h"
#include <QList>

extern "C" FILTER_FIR_EXPORT double filter_fir(QList<double>&,double);

#endif // FILTER_FIR_H
