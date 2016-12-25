#include "drawnn.h"

DrawNN::DrawNN(QWidget *parent) : QWidget(parent)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}
void DrawNN::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    int nLayers = NNlayers.size();
    const int WIDTH = painter.device()->width();
    const int HEIGHT = painter.device()->height();
    //maxNeuronsPerLayer représente le nombre maximum de neurones par layers

    if(nLayers > 0)
    {
        int maxNeuronsPerLayer = 0;
        for(int i = 0; i < nLayers; i++){
            if(NNlayers[i] > maxNeuronsPerLayer)
            {
                maxNeuronsPerLayer = NNlayers[i];
            }
        }
        maxNeuronsPerLayer = *max_element(NNlayers.begin(), NNlayers.end());
        float ellipse_size = std::min(0.95*HEIGHT/maxNeuronsPerLayer,
                                    0.95*WIDTH/NNlayers.size());
        //dy permet d'effectuer le décallage nécessaire pour centrer les layers dans le painter
        float dy = 0;
        float dyNext = 0;//dyNext est utile uniquement si l'on décide d'afficher les arrêtes du graphe
        //xSpace correspond à l'espacement entre chaque layer
        float xSpace = (WIDTH - NNlayers.size()*ellipse_size)/(nLayers);
        for(int i = 0; i < nLayers; i++){
            dy = (HEIGHT - NNlayers[i]*ellipse_size)/2;
            for(int j = 0; j < NNlayers[i]; j++){
                painter.drawEllipse(xSpace*i + i*ellipse_size, dy + j*ellipse_size, ellipse_size, ellipse_size);
                if(i < nLayers - 1){
                    dyNext = (HEIGHT - NNlayers[i+1]*ellipse_size)/2;
                    for(int k = 0; k < NNlayers[i+1]; k++){
    //                    painter.drawLine(xSpace*i + (i + 0.5)*ellipse_size, dy + (j + 0.5)*ellipse_size, xSpace*(i+1) + (i+1+0.5)*ellipse_size, dyNext + (k+0.5)*ellipse_size);
                    }
                }
            }
        }
    }
}
void DrawNN::addLayer()
{
    if(number_of_neurons_for_new_layer > 0){
        NNlayers.push_back(number_of_neurons_for_new_layer);
        update();
    }
}
void DrawNN::popLayer()
{
    if(NNlayers.size() > 0){
        NNlayers.pop_back();
        update();
    }
}

void DrawNN::getNumberOfNeurons(QString _entry)
{
    number_of_neurons_for_new_layer = _entry.toInt();
}
