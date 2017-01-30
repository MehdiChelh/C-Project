#ifndef NEURAL_NET_H
#define NEURAL_NET_H

#include <QObject>
#include <QDebug>
#include <cassert>
#include <math.h>

class Neuron;
typedef std::vector<Neuron> Layer;

// ****************** class Neural_Net ******************
class Neural_Net
{
public:
    Neural_Net(const std::vector<unsigned> &topology);
    void Feed_Forward(const std::vector<double> &inputVals);
    void Generalized_Delta_Rule(const std::vector<double> &targetVals);
    void Get_Results(std::vector<double> &resultVals) ;
    double Get_Error() { return m_error; }

private:
    std::vector<Layer> m_id_layer_neuron; // m_id_layer_neuron[layerNum][neuronNum]
    double m_error;
};


// ****************** class Neuron ******************
class Neuron
{
public:
    Neuron(unsigned numOutputs, unsigned myIndex);
    void Set_Output_Val(double val) { m_output_value = val; }
    double Get_Output_val(void) const { return m_output_value; }
    void Feed_Forward(const Layer &prevLayer);
    void Calc_Output_Grad(double targetVal);
    void Calc_Hidden_Grad(const Layer &nextLayer);
    void update_input_weights(Layer &prevLayer);
    static double eta;   // [0.0..1.0] overall Neural_Net training rate
    static double alpha; // [0.0..n] multiplier of last weight change (momentum)

private:
    static double activation_fuction(double x);
    double m_output_value;
    std::vector<double> m_output_weight;
    std::vector<double> m_output_delta_weight;
    unsigned m_myIndex;
    double m_delta;
};



#endif // NEURAL_NET_H
