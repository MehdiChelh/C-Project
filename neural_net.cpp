#include "neural_net.h"


using namespace std;



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

void Neural_Net::CalculateRMSE(const vector<double> &targetVals)
{
    Layer &outputLayer = m_id_layer_neuron.back();
    m_error = 0.0;

    for (unsigned n = 0; n < outputLayer.size() - 1; ++n) {
        double delta = targetVals[n] - outputLayer[n].Get_Output_val();
        m_error += delta * delta;
    }
    m_error /= outputLayer.size() - 1; // get average error squared
    m_error = sqrt(m_error); // RMS
}

void Neural_Net::Generalized_Delta_Rule(const vector<double> &targetVals, double alpha, double eta)
{
    // Calculate overall Neural_Net error (RMS of output neuron errors)
    CalculateRMSE(targetVals);
    Layer &outputLayer = m_id_layer_neuron.back();

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
            layer[n].update_input_weights(prevLayer, alpha, eta);
        }
    }
}

