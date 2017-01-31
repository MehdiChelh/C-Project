#include "drawnn.h"

DrawNN::DrawNN(QWidget *parent) : QWidget(parent)
{

    //const QColor *color = new QColor(0,0,0);
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    setMouseTracking(true);
}
void DrawNN::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    int nLayers = NNlayers.size();
    const int WIDTH = painter.device()->width();
    const int HEIGHT = painter.device()->height();

    if(nLayers == 0)
    {
        painter.drawText(WIDTH/2 - 190, HEIGHT/2 - 5, QString("You can add layers to the neural network with the form above."));
    }
    else{
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setBackground(QBrush(QColor(249, 135, 255)));
        painter.setBrush( QBrush( QColor(80, 80, 80)) );
        painter.setPen( Qt::NoPen );
        int maxNeuronsPerLayer = 0;
        for(int i = 0; i < nLayers; i++){
            if(NNlayers[i] > (unsigned)maxNeuronsPerLayer)
            {
                maxNeuronsPerLayer = NNlayers[i];
            }
        }
        maxNeuronsPerLayer = *max_element(NNlayers.begin(), NNlayers.end());
        ellipse_size = std::max(std::min(1.0*HEIGHT/maxNeuronsPerLayer,
                                    1.0*WIDTH/NNlayers.size()), double(4.0));
        if(rect.size() >= 2){
            float border_width = 5;
            painter.setPen( QPen(QColor(255, 80, 80), border_width, Qt::SolidLine,Qt::SquareCap, Qt::RoundJoin));
            painter.setBrush(Qt::NoBrush);
            painter.drawRect(rect[0] + border_width/2,
                    border_width/2, std::max(ellipse_size, float(4.0)) - border_width , HEIGHT-border_width +1);
            painter.setPen( Qt::NoPen );
            painter.setBrush(QBrush( QColor(80, 80, 80)) );
        }
        //dy permet d'effectuer le décallage nécessaire pour centrer les layers dans le painter
        float dy = 0;
        float dyNext = 0;//dyNext est utile uniquement si l'on décide d'afficher les arrêtes du graphe
        //xSpace correspond à l'espacement entre chaque layer
        float xSpace = (WIDTH - NNlayers.size()*ellipse_size)/(nLayers);
        delimiters.clear();
        for(int i = 0; i < nLayers; i++){
            dy = (HEIGHT - NNlayers[i]*ellipse_size)/2;
            delimiters.push_back(((xSpace + ellipse_size)*i));
            for(unsigned int j = 0; j < NNlayers[i]; j++){
                painter.drawEllipse(xSpace*i + i*ellipse_size, dy + j*ellipse_size, ellipse_size, ellipse_size);
                if(i < nLayers - 1){
                    dyNext = (HEIGHT - NNlayers[i+1]*ellipse_size)/2;
                    for(unsigned int k = 0; k < NNlayers[i+1]; k++){
    //                    painter.drawLine(xSpace*i + (i + 0.5)*ellipse_size, dy + (j + 0.5)*ellipse_size, xSpace*(i+1) + (i+1+0.5)*ellipse_size, dyNext + (k+0.5)*ellipse_size);
                    }
                }
            }
        }
    }
}
void DrawNN::mouseMoveEvent(QMouseEvent * event)
{
    int x = event->pos().x();
    int noRect = true;
    for(unsigned int i = 0; i < delimiters.size(); i++)
    {
        if(x < delimiters[i]+ellipse_size && delimiters[i] < x)
        {
            rect.push_back(delimiters[i]);
            rect.push_back(delimiters[i]+ellipse_size);
            noRect = false;
        }
    }
    if(noRect)
    {
        rect.clear();
    }
    update();
}
void DrawNN::mousePressEvent(QMouseEvent * event)
{
    int x = event->pos().x();
    for(unsigned int i = 0; i < delimiters.size(); i++)
    {
        if(x < delimiters[i]+ellipse_size && delimiters[i] < x)
        {
            QString title = "Layer n°" + QString::number(i);
            QString text = "Nombre de neurones : " + QString::number(NNlayers[i]);
            text += QString("\n\nChanger le nombre de neurones :");
            QString neurons = QInputDialog::getText(this, title, text);
            if(neurons != QString(""))
            {
                if(neurons.toInt() == 0){
                    QMessageBox::StandardButton reply = QMessageBox::question(this, "Layer n°" + QString::number(i),
                                                                              "Voulez vous supprimer ce layer ?",
                                                                              QMessageBox::Yes|QMessageBox::No);
                    if (reply == QMessageBox::Yes) {
                        NNlayers.erase(NNlayers.begin() + i);
                    }
                } else {
                    NNlayers[i] = neurons.toInt();
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
std::vector<unsigned int>* DrawNN::getNNlayers()
{
    return &NNlayers;
}
