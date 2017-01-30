#ifndef DATA_H
#define DATA_H

#include <QString>
#include <QStringList>
#include <QFile>
#include <QDebug>
#include <QList>
#include <QByteArray>

class Data
{
public:
    Data();
    bool static isInferior(QString date1, QString date2);
    QList<QByteArray> getColumnsOfCSV(QString pathToCSV);
    void openCSV(QString pathToCSV, QList<QString> selectedColumns, QString dateLabel, QList<QString> outputColumns);
    QList<QString> getColumnsName();
    QList<QString> getDate();
    std::vector<std::vector <double>> getInput();
    QList<QString> static byteArraysToStrings(QList<QByteArray> listBA);
    bool isFilled() {return (input.size() > 0);}
private:
    QList<QString> columns_name;
    QList<QString> date;
    std::vector<std::vector <double>> input;
    std::vector<std::vector <double>> output;

//    QString filename;
};

#endif // DATA_H
