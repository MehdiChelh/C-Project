#ifndef DRAWNN_H
#define DRAWNN_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QIntValidator>
#include <QGridLayout>
#include <QPainter>
#include <QPaintEvent>
#include <QtGlobal>
#include <vector>
#include <QObject>


class DrawNN : public QWidget
{
    Q_OBJECT
public:
    DrawNN(QWidget *parent);
    void paintEvent(QPaintEvent *);
public slots:
    void addLayer();
    void getNumberOfNeurons(QString);
    void popLayer();
private:
    qreal scale;
    std::vector <int> NNlayers;
    int number_of_neurons_for_new_layer;
};

#endif // DRAWNN_H
