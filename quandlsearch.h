#ifndef QUANDLSEARCH_H
#define QUANDLSEARCH_H


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
#include <QFileDialog>
#include "daterangedialog.h"
#include <QMessageBox>

class QuandlSearch : public QDialog
{
    Q_OBJECT
public:
    QuandlSearch(QLineEdit*, QTreeWidget*);
    ~QuandlSearch();
public slots:
    void searchResponse();
    QString downloadDataset(const QString start_date, const QString end_date, const QString dir);
private:
    QLineEdit* searchKeywords;
    QTreeWidget* listWidget;
};
#endif // QUANDLSEARCH_H
