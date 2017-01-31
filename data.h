#ifndef DATA_H
#define DATA_H

#include <QString>
#include <QStringList>
#include <QFile>
#include <QDebug>
#include <QList>
#include <QByteArray>
#include <cmath>

using namespace std;

class Data
{
public:
    Data();
    QList<QByteArray> getColumnsOfCSV(QString pathToCSV);
    void openCSV(QString pathToCSV, QList<QString> selectedColumns, QString dateLabel, QList<QString> outputColumns);
    QList<QString> getInputColumnsName(){return input_col_names;}
    QList<QString> getOutputColumnsName(){return output_col_names;}
    QList<QString> getDate(){return date;}
    QList<QString> static byteArraysToStrings(QList<QByteArray> listBA);
    vector<vector <double>> getInput(){return input;}
    vector<vector <double>> getOutput(){return output;}
    bool isFilled() {return (input.size() > 0);}
    void duplicateColumn(QString column_name);
    void shiftColumn(QString column_name);
    vector<vector<vector<double>>> splitData(int split_value);
    void static normalizeData(vector<vector<vector<double>>>* train_test_data);
private:
    QList<QString> input_col_names;
    QList<QString> output_col_names;
    QList<QString> date;
    vector<vector <double>> input;
    vector<vector <double>> output;
};

#endif // DATA_H
