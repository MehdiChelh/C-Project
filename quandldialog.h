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
#include "quandlsearch.h"

class QuandlDialog : public QDialog
{
    Q_OBJECT
public:
    QuandlDialog();
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
};


#endif // QUANDLDIALOG_H
