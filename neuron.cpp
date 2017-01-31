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

void Neuron::Feed_Forward(const Layer &prevLayer)
{
    double sum = 0.0;

    // Sum the previous layer's outputs (which are our inputs)
    // Include the bias node from the previous layer.

    for (unsigned n = 0; n < prevLayer.size(); ++n) {
        sum += prevLayer[n].Get_Output_val() *
            prevLayer[n].m_output_weight[m_myIndex];
    }

    m_output_value = Neuron::activation_fuction(sum);
}

double Neuron::activation_fuction(double x)
{
    // tanh - output range [-1.0..1.0]

    return tanh(x);
}

void Neuron::Calc_Hidden_Grad(const Layer &nextLayer)
{
    double sum = 0.0;

    // Sum our contributions of the errors at the nodes we feed.

    for (unsigned n = 0; n < nextLayer.size() - 1; ++n) {
        sum += m_output_weight[n] * nextLayer[n].m_delta;
    }
    m_delta = sum * (1 - (m_output_value*m_output_value));
}

void Neuron::update_input_weights(Layer &prevLayer, double alpha, double eta)
{
    // The weights to be updated are in the Connection container
    // in the neurons in the preceding layer

    for (unsigned n = 0; n < prevLayer.size(); ++n) {
        Neuron &neuron = prevLayer[n];
        double oldDeltaWeight = neuron.m_output_delta_weight[m_myIndex];

        // Individual input, magnified by the gradient and train rate:
        // Also add momentum = a fraction of the previous delta weight;
        double newDeltaWeight = eta*neuron.Get_Output_val()*m_delta + alpha*oldDeltaWeight;

        neuron.m_output_delta_weight[m_myIndex] = newDeltaWeight;
        neuron.m_output_weight[m_myIndex] += newDeltaWeight;
    }
}


void Neuron::Calc_Output_Grad(double targetVal)
{
    double delta = targetVal - m_output_value;
    m_delta = delta * (1 - (m_output_value*m_output_value));
}
