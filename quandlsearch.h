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

class QuandlSearch : public QDialog
{
    Q_OBJECT
public:
    QuandlSearch();
    ~QuandlSearch();
public slots:
    void searchResponse();
    void selectItem();
    void disableButtons();
private:
    QGridLayout *grid;
    QLineEdit* searchKeywords;
    QTreeWidget* listWidget;
    QPushButton *select_dataset;
    QPushButton *search_button;
};
#endif // QUANDLSEARCH_H
