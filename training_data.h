#ifndef TRAINING_DATA_H
#define TRAINING_DATA_H

#include <QObject>
#include <QDebug>
#include <QProgressBar>
#include <cassert>
#include <math.h>
#include "testresult.h"
#include "neuron.h"
#include "neural_net.h"

using namespace std;

typedef vector<Neuron> Layer;

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
    vector<vector<double>> Get_Output_Val(void) {return m_result_value;}
private:
    Neural_Net Net;
    vector<double> m_mean_error;
    double m_val_alpha;
    double m_val_eta;
    vector<vector<double>> m_result_value;
};

#endif // TRAINING_DATA_H
