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
    void Feed_Forward(const Layer &prevLayer);//permet le calcul de l ouput du neurone
    void Calc_Output_Grad(double targetVal);//permet le calcul de delta pour un neurone dans l output layer
    void Calc_Hidden_Grad(const Layer &nextLayer);//permet le calcul de delta pour un neurone dans l hidden layer
    void update_input_weights(Layer &prevLayer, double alpha, double eta);//permet de mettre a jour les poids associes au neurone
    static double eta;   // regle d apprentissage a definir par l utilisateur
    static double alpha; // momentum a definir par l utilisateur

private:
    static double activation_fuction(double x);
    double m_output_value;//valeur de sortie associe au neurone
    vector<double> m_output_weight;//vecteur des poids associes au neurone
    vector<double> m_output_delta_weight;//vecteur de difference entre le poids actuel et le poids a l etape precedente
    unsigned m_myIndex;//index du neurone
    double m_delta;//delta du neurone
};

#endif // NEURON_H
