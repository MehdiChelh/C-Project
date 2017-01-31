#ifndef DATA_H
#define DATA_H

#include <QString>
#include <QStringList>
#include <QFile>
#include <QDebug>
#include <QList>
#include <QByteArray>
#include <cmath>

class Data
{
public:
    Data();
    bool static isInferior(QString date1, QString date2);
    QList<QByteArray> getColumnsOfCSV(QString pathToCSV);
    void openCSV(QString pathToCSV, QList<QString> selectedColumns, QString dateLabel, QList<QString> outputColumns);
    QList<QString> getInputColumnsName(){return input_col_names;}
    QList<QString> getOutputColumnsName(){return output_col_names;}
    QList<QString> getDate();
    std::vector<std::vector <double>> getInput();
    std::vector<std::vector <double>> getOutput(){return output;}
    QList<QString> static byteArraysToStrings(QList<QByteArray> listBA);
    bool isFilled() {return (input.size() > 0);}
    void duplicateColumn(QString column_name);
    void shiftColumn(QString column_name);
    std::vector<std::vector<std::vector<double>>> splitData(int split_value);
    void static normalizeData(std::vector<std::vector<std::vector<double>>>* train_test_data);
private:
    QList<QString> input_col_names;
    QList<QString> output_col_names;
    QList<QString> date;
    std::vector<std::vector <double>> input;
    std::vector<std::vector <double>> output;

//    QString filename;
};

#endif // DATA_H
