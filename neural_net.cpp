#include "neural_net.h"


using namespace std;



Neural_Net::Neural_Net(const vector<unsigned> &topology)
{
    unsigned numLayers = topology.size();//nombre de layers
    for (unsigned layerNum = 0; layerNum < numLayers; ++layerNum) {
        m_id_layer_neuron.push_back(Layer());
        unsigned numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1];

        // maintenant que nous avons les layer, on les remplit de neurones
        // on ajoute aussi un bias neuron dans chaque layer
        for (unsigned neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum) {
            m_id_layer_neuron.back().push_back(Neuron(numOutputs, neuronNum));
        }

        // on force le bias neuron a avoir un ouput egal a 1
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

    // On assigne les input values aux input neurons
    for (unsigned i = 0; i < inputVals.size(); ++i) {
        m_id_layer_neuron[0][i].Set_Output_Val(inputVals[i]);
    }

    // on feed-forward
    for (unsigned layerNum = 1; layerNum < m_id_layer_neuron.size(); ++layerNum) {
        Layer &prevLayer = m_id_layer_neuron[layerNum - 1];
        for (unsigned n = 0; n < m_id_layer_neuron[layerNum].size() - 1; ++n) {
            m_id_layer_neuron[layerNum][n].Feed_Forward(prevLayer);
        }
    }
}

void Neural_Net::CalculateRMSE(const vector<double> &targetVals) //calcul de l'erreur quadratique moyenne
{
    Layer &outputLayer = m_id_layer_neuron.back();
    m_error = 0.0;

    for (unsigned n = 0; n < outputLayer.size() - 1; ++n) {
        double delta = targetVals[n] - outputLayer[n].Get_Output_val();
        m_error += delta * delta;
    }
    m_error /= outputLayer.size() - 1;
    m_error = sqrt(m_error); // erreur quadratique moyenne
}

void Neural_Net::Generalized_Delta_Rule(const vector<double> &targetVals, double alpha, double eta)
{
    // calcul de l erreur quadratique moyenne
    CalculateRMSE(targetVals);
    Layer &outputLayer = m_id_layer_neuron.back();

    // mise a jour de delta pour l output layer

    for (unsigned n = 0; n < outputLayer.size() - 1; ++n) {
        outputLayer[n].Calc_Output_Grad(targetVals[n]);
    }

    // mise a jour de delta pour les hidden layers

    for (unsigned layerNum = m_id_layer_neuron.size() - 2; layerNum > 0; --layerNum) {
        Layer &hiddenLayer = m_id_layer_neuron[layerNum];
        Layer &nextLayer = m_id_layer_neuron[layerNum + 1];

        for (unsigned n = 0; n < hiddenLayer.size(); ++n) {
            hiddenLayer[n].Calc_Hidden_Grad(nextLayer);
        }
    }

    // on met a jour les poids

    for (unsigned layerNum = m_id_layer_neuron.size() - 1; layerNum > 0; --layerNum) {
        Layer &layer = m_id_layer_neuron[layerNum];
        Layer &prevLayer = m_id_layer_neuron[layerNum - 1];

        for (unsigned n = 0; n < layer.size() - 1; ++n) {
            layer[n].update_input_weights(prevLayer, alpha, eta);
        }
    }
}

