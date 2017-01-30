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
#include <QSyntaxHighlighter>
#include <QGroupBox>
#include <QListWidget>
#include <QComboBox>
#include <curl/curl.h>
#include <Python/Python.h>
//#include "PythonQt3.1/src/PythonQt.h"
#include "drawnn.h"
#include "quandlsearch.h"
#include "quandldialog.h"
#include "data.h"
#include "tablewidget.h"
#include "preprocdialog.h"
#include "traindialog.h"

class Tab1 : public QWidget
{
    Q_OBJECT
public:
    Tab1();
    ~Tab1();
    QList<QString> static selectItemsDialog(QString title, QList<QString> items);
public slots:
    void resetInputFormNeurons();
    void loadCustomData();
    void selectData();
    void enablingDisablingButtons();
    void DataPreprocessDialog();
    void QuandlDialog();
    void duplicateColumn();
private:
    QGridLayout *grid;
    QPushButton *load_data_button;
    QPushButton *add_layer_button;
    QPushButton *pop_layer_button;
    QPushButton *learning_button;
    QLineEdit * inputFormNeurons;
    QLabel *labelForDebug;
    QString pathToCSV;
    Data *data;
    DrawNN *paintWidget;
    TableWidget *table;
    QComboBox* comboBox;
};


class TrainTestLabel: public QLabel
{
    Q_OBJECT
public:
    TrainTestLabel(QWidget* parent);
public slots:
    void setCustomText(int);
};

#endif // TAB1_H
