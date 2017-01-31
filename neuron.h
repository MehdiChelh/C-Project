#ifndef NEURON_H
#define NEURON_H

#include <QObject>
#include <QDebug>
#include <QProgressBar>
#include <cassert>
#include <math.h>
#include "testresult.h"
#include "neural_net.h"

using namespace std;
class Neuron;
typedef std::vector<Neuron> Layer;

class Neuron
{
public:
    Neuron(unsigned numOutputs, unsigned myIndex);
    void Set_Output_Val(double val) { m_output_value = val; }
    double Get_Output_val(void) const { return m_output_value; }
    void Feed_Forward(const Layer &prevLayer);
    void Calc_Output_Grad(double targetVal);
    void Calc_Hidden_Grad(const Layer &nextLayer);
    void update_input_weights(Layer &prevLayer, double alpha, double eta);
    static double eta;   // [0.0..1.0] overall Neural_Net training rate
    static double alpha; // [0.0..n] multiplier of last weight change (momentum)

private:
    static double activation_fuction(double x);
    double m_output_value;
    vector<double> m_output_weight;
    vector<double> m_output_delta_weight;
    unsigned m_myIndex;
    double m_delta;
};

#endif // NEURON_H
