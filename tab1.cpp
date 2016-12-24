#include "tab1.h"

Tab1::Tab1() : QWidget()
{
    grid = new QGridLayout();
    this->setLayout(grid);

    //Bouton pour ouvrir la boite de dialogue pour charger les données
    load_data_button = new QPushButton("Load data");
    load_data_button -> setCursor(Qt::PointingHandCursor);
    QObject::connect(load_data_button, SIGNAL(clicked()), qApp, SLOT(quit()));
    grid -> addWidget(load_data_button, 0, 0);

    //Input pour le nombre de neurones du NN à ajouter
    QLineEdit *txt = new QLineEdit(this);
    txt->setPlaceholderText("Entrer le nombre de neurones du layer");
    txt->setValidator(new QIntValidator(txt));
    grid -> addWidget(txt, 0,1);

    //Bouton pour ajouter une couche au NN
    add_layer_button = new QPushButton("Ajouter layer");
    add_layer_button -> setCursor(Qt::PointingHandCursor);
    QObject::connect(add_layer_button, SIGNAL(clicked()), qApp, SLOT(quit()));
    grid -> addWidget(add_layer_button, 0, 2);

    DrawNN *paintWidget = new DrawNN(this);

    grid -> addWidget(paintWidget, 1, 1);

}
Tab1::~Tab1()
{
    delete grid;
    delete load_data_button;
    delete add_layer_button;
}
DrawNN::DrawNN(QWidget *parent) : QWidget(parent)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    NNlayers.push_back(64);
    NNlayers.push_back(32);
    NNlayers.push_back(16);
    NNlayers.push_back(8);
    NNlayers.push_back(4);
    NNlayers.push_back(2);
    NNlayers.push_back(1);
    NNlayers.push_back(1);
    NNlayers.push_back(1);
    NNlayers.push_back(1);
    NNlayers.push_back(1);
}
void DrawNN::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    int nLayers = NNlayers.size();
    const int WIDTH = painter.device()->width();
    const int HEIGHT = painter.device()->height();
    //maxNeuronsPerLayer représente le nombre maximum de neurones par layers
    //c'est max(NNlayers)
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
    float xSpace = (WIDTH - NNlayers.size()*ellipse_size)/(NNlayers.size()+1);
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
//    painter.scale(scale, scale);
//    const QString ok = QString(WIDTH);
//    painter.drawText(17, 30, ok);
}
void DrawNN::wheelEvent ( QWheelEvent * event )
{
    scale+=(event->delta()/120); //or use any other step for zooming
}
