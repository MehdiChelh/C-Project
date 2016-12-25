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
#include <QObject>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QLabel>
#include <QDebug>
#include "drawnn.h"

class Tab1 : public QWidget
{
    Q_OBJECT
public:
    Tab1();
    ~Tab1();
public slots:
    void resetInputFormNeurons();
    void loadData();
    void selectData();
    void enablingDisablingButtons();
private:
    QGridLayout *grid;
    QPushButton *load_data_button;
    QPushButton *add_layer_button;
    QPushButton *pop_layer_button;
    QPushButton *learning_button;
    QLineEdit * inputFormNeurons;
    QLabel *labelForDebug;
    QString data;
    DrawNN *paintWidget;
};

#endif // TAB1_H
