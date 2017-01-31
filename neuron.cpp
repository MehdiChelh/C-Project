#include "neuron.h"

Neuron::Neuron(unsigned numOutputs, unsigned myIndex)
{
    for (unsigned c = 0; c < numOutputs; ++c) {
        m_output_weight.push_back(double());
        m_output_delta_weight.push_back(double());
        m_output_weight.back() = rand() / double(RAND_MAX);
    }

    m_myIndex = myIndex;
}

//calcul de l output dans un neurone a partir des poids et inputs lies a la couche precedente
void Neuron::Feed_Forward(const Layer &prevLayer)
{
    double sum = 0.0;

    for (unsigned n = 0; n < prevLayer.size(); ++n) {
        sum += prevLayer[n].Get_Output_val() *
            prevLayer[n].m_output_weight[m_myIndex];
    }

    m_output_value = Neuron::activation_fuction(sum);
}

//fonction d activation
double Neuron::activation_fuction(double x)
{

    return tanh(x);
}

//calcul de delta dans les hidden layers
void Neuron::Calc_Hidden_Grad(const Layer &nextLayer)
{
    double sum = 0.0;

    for (unsigned n = 0; n < nextLayer.size() - 1; ++n) {
        sum += m_output_weight[n] * nextLayer[n].m_delta;
    }
    m_delta = sum * (1 - (m_output_value*m_output_value));
}

//mis a jour des poids
void Neuron::update_input_weights(Layer &prevLayer, double alpha, double eta)
{
    for (unsigned n = 0; n < prevLayer.size(); ++n) {
        Neuron &neuron = prevLayer[n];
        double oldDeltaWeight = neuron.m_output_delta_weight[m_myIndex];
        // eta et alpha sont les parametres a definir par l utilisateur de l interface graphique
        double newDeltaWeight = eta*neuron.Get_Output_val()*m_delta + alpha*oldDeltaWeight;

        neuron.m_output_delta_weight[m_myIndex] = newDeltaWeight;
        neuron.m_output_weight[m_myIndex] += newDeltaWeight;
    }
}

//calcul de delta dans l ouput layer
void Neuron::Calc_Output_Grad(double targetVal)
{
    double delta = targetVal - m_output_value;
    m_delta = delta * (1 - (m_output_value*m_output_value));
}
