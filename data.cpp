#include "data.h"

Data::Data()
{

}

bool Data::isInferior(QString date1, QString date2)
{
    QStringList date1List = date1.split("-");
    QStringList date2List = date2.split("-");
    if(date1List[0] < date2List[0]){
        return true;
    }
    else{
        if(date1List[0] == date2List[0] && (date1List[1] < date2List[1])){
            return true;
        }
        else{
            if(date1List[0] == date2List[0] && (date1List[1] == date2List[1]) && (date1List[2] <= date2List[2])){
                return true;
            }
            else{
                return false;
            }
        }
    }
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

    QFile file(pathToCSV);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.errorString();
    }


    input_col_names = selectedInputColumns;
    input_col_names.removeAll(dateLabel);

    output_col_names = outputColumns;
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
//    for(int i = 0; i < outputColumns.length(); i++){
//        input_col_names.removeAll(outputColumns[i]);
//        input_col_names.append(QStringLiteral("OUTPUT_%1 [%2]").arg(i).arg(outputColumns[i]));
//        selectedOutputIndices.append(i);
//    }
    qDebug() << input_col_names;
    qDebug() << selectedInputIndices;
//    //On commence à 1 pour ne pas prendre en compte la première ligne (en suppose qu'elle contient le nom des colonnes)
    for(int i = 1; i < lines.length(); i++){
        QList<QByteArray> liste = lines[i].split(',');
        if(liste.length() >= selectedInputIndices.last()){
            std::vector<double> vecInput;
            std::vector<double> vecOutput;
            Q_FOREACH (const int& indice, selectedInputIndices){
                vecInput.push_back(liste[indice].toDouble());
            }
            Q_FOREACH (const int& indice, selectedOutputIndices){
                vecOutput.push_back(liste[indice].toDouble());
            }
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
    qDebug() << "ok1";
    int index = input_col_names.indexOf(column_name);
    std::vector<std::vector<double>> new_input;
    qDebug() << "ok2";
    for(int i = 0; i < input.size() - 1; i++){
        std::vector<double> vec;
        qDebug() << i;
        for(int j = 0; j < input[i].size(); j++){
            if(j==index){
                vec.push_back(input[i+1][j]);
            }
            else{
                vec.push_back(input[i][j]);
            }
            qDebug()<<j;
        }
        new_input.push_back(vec);
    }
    qDebug() << "ok3";
    input = new_input;
    output.pop_back();
}


QList<QString> Data::getDate(){
    return date;
}

std::vector<std::vector <double>> Data::getInput(){
    return input;
}

QList<QString> Data::byteArraysToStrings(QList<QByteArray> listBA)
{
    QList<QString> listS;
    for(int i = 0; i < listBA.length(); i++){
        listS.append(listBA[i].constData());
    }
    return listS;
}
