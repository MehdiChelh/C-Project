#ifndef TRAINDIALOG_H
#define TRAINDIALOG_H

#include <QApplication>
#include <QDebug>
#include <QObject>
#include <QDialog>
#include "neural_net.h"

using namespace std;

class TrainDialog: public QDialog
{
    Q_OBJECT
public:
    TrainDialog();
public slots:
    void Test();
};

#endif // TRAINDIALOG_H
