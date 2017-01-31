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
    void Generalized_Delta_Rule(const std::vector<double> &targetVals, double alpha, double eta);
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
    void update_input_weights(Layer &prevLayer, double alpha, double eta);
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


// **************** Class Training Data ********************
class Training_Data
{
public:
    Training_Data();
    void Train(std::vector<unsigned> topology,unsigned int nb_iteration_base, double val_alpha, double val_eta, std::vector<std::vector<double>> input_values, std::vector<std::vector<double>> target_values);
    double Get_Output_Val_Alpha(void){ return m_val_alpha; }
    double Get_Output_Val_Eta(void) { return m_val_eta; }
    std::vector<double> Get_Error(void) { return m_mean_error; }
    std::vector<std::vector<double>> Get_Output_Val(void) {
        return m_result_value
            ;
    }
private:
    std::vector<double> m_mean_error;
    double m_val_alpha;
    double m_val_eta;
    std::vector<std::vector<double>> m_result_value;
};


#endif // NEURAL_NET_H
