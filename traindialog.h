#ifndef TRAINDIALOG_H
#define TRAINDIALOG_H

#include <QApplication>
#include <QDebug>
#include <QObject>
#include <QDialog>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QGroupBox>
#include <QSlider>
#include <QPushButton>
#include <QProgressBar>
#include <QTreeWidget>
#include <QMessageBox>
#include "neural_net.h"
#include "data.h"
#include "neural_net.h"

using namespace std;

class TrainDialog: public QDialog
{
    Q_OBJECT
public:
    TrainDialog(QWidget* parent, Data* data, std::vector<unsigned int>* topology);
public slots:
    void Test();
    void TrainTest();
    void addMSEListItem(QString);
private:
    QLineEdit* alphaQline;
    QLineEdit* etaQline;
    QLineEdit* nIterQline;
    QSlider* slider;
    QProgressBar* trainProgress;
    QTreeWidget* mseList;
    Data* data;
    std::vector<unsigned int>* topology;
};


class TrainTestLabel: public QLabel
{
    Q_OBJECT
public:
    TrainTestLabel(QWidget* parent);
public slots:
    void setCustomText(int);
};

#endif // TRAINDIALOG_H
