#include "traindialog.h"

TrainDialog::TrainDialog(): QDialog()
{

}
void TrainDialog::Test()
{
    vector<unsigned int> topo;
    topo.push_back(2);
    topo.push_back(4);
    topo.push_back(3);
    topo.push_back(1);
    Neural_Net My_Neural_Net(topo);
    qDebug() << topo[0];
    //exemple d entrainement du reseau de neuronnes avec le probleme xor
    //on met des 1 ou 0
    vector<double> Xor;
    vector<double> _Xor;
    vector<double> xor_target;//valeur a predire
    for (unsigned nb = 0; nb < 1000; ++nb) {
        Xor.push_back(rand() % 2);
        _Xor.push_back(rand() % 2);
        xor_target.push_back(Xor[nb] == _Xor[nb] ? 0 : 1);
    };
    vector <double> input_vals, result_vals, target_vals;
    input_vals.push_back(_Xor[0]);
    input_vals.push_back(Xor[0]);
    for (unsigned i = 0; i < xor_target.size(); ++i) {
        qDebug() << "valeur a predire: ";
        qDebug() << xor_target[i] << "     ";
        target_vals.push_back(xor_target[i]);
        input_vals[0] = _Xor[i];
        input_vals[1] = Xor[i];
        My_Neural_Net.Feed_Forward(input_vals);
        My_Neural_Net.Get_Results(result_vals);
        My_Neural_Net.Generalized_Delta_Rule(target_vals);

        qDebug() << "valeur predite: ";
        qDebug() << result_vals[0] << "\n";
        target_vals.clear();
    };
}
