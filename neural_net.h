#ifndef NEURAL_NET_H
#define NEURAL_NET_H

#include <QObject>
#include <QDebug>
#include <QProgressBar>
#include <cassert>
#include <math.h>
#include "testresult.h"
#include "neuron.h"

using namespace std;

class Neuron;
typedef std::vector<Neuron> Layer;//un layer est defini comme un vecteur de neurones



class Neural_Net
{
public:
    Neural_Net(const vector<unsigned> &topology);
    void Feed_Forward(const vector<double> &inputVals);//fonction qui se charge de l etape feed-forward
    void Generalized_Delta_Rule(const vector<double> &targetVals, double alpha, double eta);//fonction qui se charge de l etape de back propoagatopn
    void Get_Results(vector<double> &resultVals);
    void CalculateRMSE(const vector<double> &targetVals);//calcul de l erreur quadratique moyenne
    double Get_Error() { return m_error; }

private:
    vector<Layer> m_id_layer_neuron; //donne acces aux neurones dans le reseau
    double m_error;//erreur quadratique moyenne
};


#endif // NEURAL_NET_H
