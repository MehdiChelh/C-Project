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
#include <QDebug>
#include <QInputDialog>
#include <QMessageBox>

class DrawNN : public QWidget
{
    Q_OBJECT
public:
    DrawNN(QWidget *parent);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent * event);
protected:
    void mouseMoveEvent(QMouseEvent * event);
public slots:
    void addLayer();
    void getNumberOfNeurons(QString);
    void popLayer();
    std::vector <int> getNNlayers();
private:
    qreal scale;
    std::vector <int> NNlayers;
    int number_of_neurons_for_new_layer;
    std::vector <int> rect;
    std::vector <int> delimiters;
    float ellipse_size;
};

#endif // DRAWNN_H
