#ifndef QUANDLDATA_H
#define QUANDLDATA_H

#include "data.h"
#include <QObject>
#include <QList>


class QuandlData: public Data
{
public:
    QuandlData();
//    QList<QByteArray> getDate();
//private:
//    QList<QByteArray> date;
};

#endif // QUANDLDATA_H
