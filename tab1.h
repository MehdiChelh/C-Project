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
#include <QDialog>
#include <QTableWidget>
#include <QTextEdit>
#include <QColor>
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
    void seeData();
    void DataPreprocessDialog();
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

class CodeEdit : public QTextEdit
{
    Q_OBJECT
public:
    CodeEdit(QDialog*);
public slots:
    void codeTransformation();
};

#endif // TAB1_H
