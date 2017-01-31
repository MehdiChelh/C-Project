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
typedef std::vector<Neuron> Layer;



class Neural_Net
{
public:
    Neural_Net(const vector<unsigned> &topology);
    void Feed_Forward(const vector<double> &inputVals);
    void Generalized_Delta_Rule(const vector<double> &targetVals, double alpha, double eta);
    void Get_Results(vector<double> &resultVals);
    void CalculateRMSE(const vector<double> &targetVals);
    double Get_Error() { return m_error; }

private:
    vector<Layer> m_id_layer_neuron; // m_id_layer_neuron[layerNum][neuronNum]
    double m_error;
};


#endif // NEURAL_NET_H
