#include "neural_net.h"

double Neuron::eta = 0.15;    // overall Neural_Net learning rate, [0.0..1.0]
double Neuron::alpha = 0.5;   // momentum, multiplier of last deltaWeight, [0.0..1.0]

using namespace std;



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

void Neuron::update_input_weights(Layer &prevLayer)
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





Neural_Net::Neural_Net(const vector<unsigned> &topology)
{
    unsigned numLayers = topology.size();
    for (unsigned layerNum = 0; layerNum < numLayers; ++layerNum) {
        m_id_layer_neuron.push_back(Layer());
        unsigned numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1];

        // We have a new layer, now fill it with neurons, and
        // add a bias neuron in each layer.
        for (unsigned neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum) {
            m_id_layer_neuron.back().push_back(Neuron(numOutputs, neuronNum));
            qDebug() << "Made a Neuron!\n";
        }

        // Force the bias node's output to 1.0 (it was the last neuron pushed in this layer):
        m_id_layer_neuron.back().back().Set_Output_Val(1.0);
    }
}

void Neural_Net::Get_Results(vector<double> &resultVals)
{
    resultVals.clear();

    for (unsigned n = 0; n < m_id_layer_neuron.back().size() - 1; ++n) {
        resultVals.push_back(m_id_layer_neuron.back()[n].Get_Output_val());
    }
}

void Neural_Net::Feed_Forward(const vector<double> &inputVals)
{
    assert(inputVals.size() == m_id_layer_neuron[0].size() - 1);

    // Assign (latch) the input values into the input neurons
    for (unsigned i = 0; i < inputVals.size(); ++i) {
        m_id_layer_neuron[0][i].Set_Output_Val(inputVals[i]);
    }

    // forward propagate
    for (unsigned layerNum = 1; layerNum < m_id_layer_neuron.size(); ++layerNum) {
        Layer &prevLayer = m_id_layer_neuron[layerNum - 1];
        for (unsigned n = 0; n < m_id_layer_neuron[layerNum].size() - 1; ++n) {
            m_id_layer_neuron[layerNum][n].Feed_Forward(prevLayer);
        }
    }
}

void Neural_Net::Generalized_Delta_Rule(const vector<double> &targetVals)
{
    // Calculate overall Neural_Net error (RMS of output neuron errors)

    Layer &outputLayer = m_id_layer_neuron.back();
    m_error = 0.0;

    for (unsigned n = 0; n < outputLayer.size() - 1; ++n) {
        double delta = targetVals[n] - outputLayer[n].Get_Output_val();
        m_error += delta * delta;
    }
    m_error /= outputLayer.size() - 1; // get average error squared
    m_error = sqrt(m_error); // RMS

    // Calculate output layer gradients

    for (unsigned n = 0; n < outputLayer.size() - 1; ++n) {
        outputLayer[n].Calc_Output_Grad(targetVals[n]);
    }

    // Calculate hidden layer gradients

    for (unsigned layerNum = m_id_layer_neuron.size() - 2; layerNum > 0; --layerNum) {
        Layer &hiddenLayer = m_id_layer_neuron[layerNum];
        Layer &nextLayer = m_id_layer_neuron[layerNum + 1];

        for (unsigned n = 0; n < hiddenLayer.size(); ++n) {
            hiddenLayer[n].Calc_Hidden_Grad(nextLayer);
        }
    }

    // For all layers from outputs to first hidden layer,
    // update connection weights

    for (unsigned layerNum = m_id_layer_neuron.size() - 1; layerNum > 0; --layerNum) {
        Layer &layer = m_id_layer_neuron[layerNum];
        Layer &prevLayer = m_id_layer_neuron[layerNum - 1];

        for (unsigned n = 0; n < layer.size() - 1; ++n) {
            layer[n].update_input_weights(prevLayer);
        }
    }
}
