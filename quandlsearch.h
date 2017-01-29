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

class QuandlSearch : public QDialog
{
    Q_OBJECT
public:
    QuandlSearch(QLineEdit*, QTreeWidget*);
    ~QuandlSearch();
public slots:
    void searchResponse();
    void selectItem();
private:
    QLineEdit* searchKeywords;
    QTreeWidget* listWidget;
};
#endif // QUANDLSEARCH_H
