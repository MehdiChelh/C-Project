#include "data.h"

Data::Data()
{

}

QList<QByteArray> Data::getColumnsOfCSV(QString pathToCSV)
{
    QFile file(pathToCSV);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.errorString();
    }
    QList<QByteArray> lines = file.readAll().split('\n');
    //On retourne la première ligne du csv (en supposant qu'elle contient le nom des colonnes)
    return lines[0].split(',');
}

void Data::openCSV(QString pathToCSV, QList<QString> selectedInputColumns, QString dateLabel, QList<QString> outputColumns)
{
    int dateIndice;
    QList<int> selectedInputIndices;
    QList<int> selectedOutputIndices;

    input.clear();
    output.clear();
    date.clear();

    QFile file(pathToCSV);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.errorString();
    }


    input_col_names = selectedInputColumns;
    if(dateLabel != "")
        input_col_names.removeAll(dateLabel);

    output_col_names = outputColumns;
    if(dateLabel != "")
        output_col_names.removeAll(dateLabel);

    QList<QByteArray> lines = file.readAll().split('\n');
    //On récupère les indices des colones choisies comme input
    QList<QByteArray> entete = lines[0].split(',');
    for(int i = 0; i < entete.length(); i++)
    {
        if(input_col_names.contains(entete[i]) && entete[i] != dateLabel){
            selectedInputIndices.append(i);
        }
        if(dateLabel == entete[i])
        {
            dateIndice = i;
        }

        if(output_col_names.contains(entete[i]) && entete[i] != dateLabel){
            int index = output_col_names.indexOf(entete[i]);
            QString newTitle = entete[i] + " [OUTPUT]";

            output_col_names.replace(index, newTitle);
            selectedOutputIndices.append(i);
        }

    }
    //On commence à 1 pour ne pas prendre en compte la première ligne (en suppose qu'elle contient le nom des colonnes)
    for(int i = 1; i < lines.length(); i++){
        QList<QByteArray> liste = lines[i].split(',');
        if(liste.length() >= selectedInputIndices.last() && lines[i] != ""){
            std::vector<double> vecInput;
            std::vector<double> vecOutput;
            Q_FOREACH (const int& indice, selectedInputIndices){
                vecInput.push_back(liste[indice].toDouble());
            }
            Q_FOREACH (const int& indice, selectedOutputIndices){
                vecOutput.push_back(liste[indice].toDouble());
            }
            if(dateLabel != "")
                date.push_back(liste[dateIndice]);
            input.push_back(vecInput);
            output.push_back(vecOutput);
        }
    }
}

void Data::duplicateColumn(QString column_name)
{
    int index = input_col_names.indexOf(column_name);
    int i = 1;
    while(input_col_names.contains(column_name + "_" + QString::number(i))){
        i++;
    }
    QString new_col_name = column_name + "_" + QString::number(i);
    input_col_names.append(new_col_name);
    for(int i = 0; i < input.size(); i++){
        input[i].push_back(input[i][index]);
    }
}

void Data::shiftColumn(QString column_name)
{
    int index = input_col_names.indexOf(column_name);
    std::vector<std::vector<double>> new_input;
    for(int i = 0; i < input.size() - 1; i++){
        std::vector<double> vec;
        for(int j = 0; j < input[i].size(); j++){
            if(j==index){
                vec.push_back(input[i+1][j]);
            }
            else{
                vec.push_back(input[i][j]);
            }
        }
        new_input.push_back(vec);
    }
    input = new_input;
    output.pop_back();
}

std::vector<std::vector<std::vector<double>>> Data::splitData(int split_value)
{
    std::vector<std::vector<std::vector<double>>> res;
    int train_size = std::max((int)1, std::min((int)(input.size() - 1), (int)(input.size()*split_value/100.0)));
    std::vector<std::vector<double>> train_input(input.begin(), input.begin() + train_size);
    std::vector<std::vector<double>> train_output(output.begin(), output.begin() + train_size);
    std::vector<std::vector<double>> test_input(input.begin() + train_size, input.end());
    std::vector<std::vector<double>> test_output(output.begin() + train_size, output.end());
    res.push_back(train_input);
    res.push_back(train_output);
    res.push_back(test_input);
    res.push_back(test_output);
    return res;
}

void Data::normalizeData(std::vector<std::vector<std::vector<double>>>* _train_test)
{
    std::vector<std::vector<std::vector<double>>> train_test = *_train_test;
    double max[4] = {train_test[0][0][0], train_test[1][0][0], train_test[2][0][0], train_test[3][0][0]};
    for(int k = 0; k < train_test.size(); k++){
        for(int i = 0; i < train_test[k].size(); i++){
             for(int j = 0; j < train_test[k][i].size(); j++){
                 if(fabs(train_test[k][i][j]) > max[k])
                     max[k] = fabs(train_test[k][i][j]);
             }
        }
    }
    for(int k = 0; k < train_test.size(); k++){
        for(int i = 0; i < train_test[k].size(); i++){
            for(int j = 0; j < train_test[k][i].size(); j++){
                train_test[k][i][j] = train_test[k][i][j]/max[k];
            }
        }
    }
    *_train_test = train_test;
}

QList<QString> Data::byteArraysToStrings(QList<QByteArray> listBA)
{
    QList<QString> listS;
    for(int i = 0; i < listBA.length(); i++){
        listS.append(listBA[i].constData());
    }
    return listS;
}
