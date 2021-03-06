#ifndef QUANDLDIALOG_H
#define QUANDLDIALOG_H


#include <QApplication>
#include <QObject>
#include <QDialog>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTreeWidget>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <curl/curl.h>
#include <QDebug>
#include <QLabel>
#include <QSlider>
#include "tab1.h"
#include "quandlsearch.h"
#include "data.h"
#include "tablewidget.h"

class QuandlDialog : public QDialog
{
    Q_OBJECT
public:
    QuandlDialog(Data* _data, TableWidget* _table, QComboBox* _comboBox_1, QComboBox* _comboBox_2);
    ~QuandlDialog();
public slots:
    void enablingSelection();
    void selectDate();
    void chooseFolder();
    void download();
private:
    QGridLayout *grid;
    QLineEdit* searchKeywords;
    QTreeWidget* listWidget;
    QPushButton *select_dataset;
    QPushButton *search_button;
    QuandlSearch *search;
    QLineEdit* end_date;
    QLineEdit* start_date;
    QLineEdit* destination_folder;
    Data* data;
    TableWidget *table;
    QComboBox* comboBox_1;
    QComboBox* comboBox_2;
};


#endif // QUANDLDIALOG_H

