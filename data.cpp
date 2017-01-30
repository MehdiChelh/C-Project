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

void Data::openCSV(QString pathToCSV, QList<QString> selectedColumns, QString dateLabel, QList<QString> outputColumns)
{
    int dateIndice;
    QList<int> selectedInputIndices;

    QFile file(pathToCSV);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.errorString();
    }

    QStringList wordList;
    QList<QByteArray> lines = file.readAll().split('\n');
    //On stock l'entête dans entete :
    columns_name = selectedColumns;
    columns_name.removeAll(dateLabel);

    QList<QByteArray> entete = lines[0].split(',');
    for(int i = 0; i < entete.length(); i++)
    {
        if(columns_name.contains(entete[i]) && entete[i] != dateLabel){
            selectedInputIndices.append(i);
        }
        if(dateLabel == entete[i])
        {
            dateIndice = i;
        }
    }
    for(int i = 0; i < outputColumns.length(); i++){
        int indice = columns_name.indexOf(outputColumns[i]);
        columns_name[indice] = QStringLiteral("OUTPUT_%1 [%2]").arg(i).arg(outputColumns[i]);
    }
    qDebug() << columns_name;
    qDebug() << selectedInputIndices;
//    //On commence à 1 pour ne pas prendre en compte la première ligne (en suppose qu'elle contient le nom des colonnes)
    std::vector<double> vec;
    for(int i = 1; i < lines.length(); i++){
        QList<QByteArray> liste = lines[i].split(',');
        if(liste.length() >= selectedInputIndices.last()){
            vec.clear();
            Q_FOREACH (const int& indice, selectedInputIndices){
                vec.push_back(liste[indice].toDouble());
            }
            date.push_back(liste[dateIndice]);
            input.push_back(vec);
        }
    }
}

QList<QString> Data::getColumnsName(){
    return columns_name;
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
