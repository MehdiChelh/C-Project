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

//class Neuron;
typedef std::vector<Neuron> Layer;

// ****************** class Neural_Net ******************
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




// **************** Class Training Data ********************
class Training_Data: public QObject
{
    Q_OBJECT
signals:
    void signalProgress(int);
    void signalMSE(QString);
public:
    Training_Data(std::vector<unsigned> topology);
    void Train(unsigned int nb_iteration_base, double val_alpha, double val_eta, vector<vector<double>> input_values, vector<vector<double>> target_values);
    TestResult Test(vector<vector<double>> input_values, vector<vector<double>> target_values);
    void progressValueChanged(int val){ emit signalProgress(val); }
    void newMSE(QString val){ emit signalMSE(val); }
    double Get_Output_Val_Alpha(void){ return m_val_alpha; }
    double Get_Output_Val_Eta(void) { return m_val_eta; }
    vector<double> Get_Error(void) { return m_mean_error; }
    vector<vector<double>> Get_Output_Val(void) {
        return m_result_value
            ;
    }
private:
    Neural_Net Net;
    vector<double> m_mean_error;
    double m_val_alpha;
    double m_val_eta;
    vector<vector<double>> m_result_value;
};


#endif // NEURAL_NET_H
