#ifndef DATA_H
#define DATA_H

#include <QString>
#include <QStringList>
#include <QFile>
#include <QDebug>

class Data
{
public:
    Data();
    bool static isInferior(QString date1, QString date2);
    void openCSV(QString pathToCSV);
    QList<QByteArray> getColumnsName();
    QList<QByteArray> getDate();
    std::vector<std::vector <double>> getInput();
private:
    QList<QByteArray> columns_name;
    QList<QByteArray> date;
    std::vector<std::vector <double>> input;
//    QString filename;
};

#endif // DATA_H
