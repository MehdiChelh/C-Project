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

void Data::openCSV(QString pathToCSV)
{
    QFile file(pathToCSV);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.errorString();
    }

    QStringList wordList;
    QList<QByteArray> lines = file.readAll().split('\n');
    //On stock l'entête dans entete :
    columns_name = lines[0].split(',');
    qDebug() << columns_name;
    //On commence à 1 pour ne pas prendre en compte l'entête
    for(int i = 1; i < lines.length(); i++){
        QList<QByteArray> liste = lines[i].split(',');
        for(int e = 0; e < liste.length(); e++){
            if(liste[e] != ""){
                QString datemax = "3000-12-12";
                QString datemin = "0-0-0";
                if((e == 1) && Data::isInferior(liste[0], datemax) && Data::isInferior(datemin, liste[0])){
                    //pour l'instant on mets juste l'open et le high "bêtement" dans l'input
                    const double arr[] = {liste[1].toDouble(), liste[2].toDouble()};
                    std::vector<double> vec (arr, arr + sizeof(arr) / sizeof(arr[0]) );
                    input.push_back(vec);
//                    date.append(liste[0]);
                }
            }
        }
    }
}

QList<QByteArray> Data::getColumnsName(){
    return columns_name;
}

QList<QByteArray> Data::getDate(){
    return date;
}

std::vector<std::vector <double>> Data::getInput(){
    return input;
}
