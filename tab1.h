#ifndef TAB1_H
#define TAB1_H

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

class Tab1 : public QWidget
{
public:
    Tab1();
    ~Tab1();
private:
    QGridLayout *grid;
    QPushButton *load_data_button;
    QPushButton *add_layer_button;
};

class DrawNN : public QWidget
{
public:
    DrawNN(QWidget *parent);
    void paintEvent(QPaintEvent *);
    void wheelEvent ( QWheelEvent * event );
private:
    qreal scale;
    std::vector <int> NNlayers;
};

#endif // TAB1_H
