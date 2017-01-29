#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QTableWidget>
#include "data.h"

class TableWidget: public QTableWidget
{
public:
    TableWidget(Data* data, QWidget* parent);
    void fill(Data* data);
};

#endif // TABLEWIDGET_H
