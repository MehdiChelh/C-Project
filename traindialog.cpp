#include "traindialog.h"

TrainDialog::TrainDialog(QWidget* parent): QDialog(parent)
{
    this->setWindowTitle("Train and test");

    QGridLayout* grid = new QGridLayout(this);
    this->setLayout(grid);

    QGroupBox *settings = new QGroupBox(this);
    settings->setTitle(QString("Settings of the learning :"));
    QGridLayout* groupBoxGrid = new QGridLayout(settings);
    settings->setLayout(groupBoxGrid);
    grid->addWidget(settings, 0, 0, 1, 2);

    QLabel* alphaLabel = new QLabel("ALpha : ", this);
        groupBoxGrid->addWidget(alphaLabel, 0, 0);
    QLineEdit* alphaQline = new QLineEdit(this);
        groupBoxGrid->addWidget(alphaQline, 0, 1);

    QLabel* etaLabel = new QLabel("Eta : ", this);
        groupBoxGrid->addWidget(etaLabel, 1, 0);
    QLineEdit* etaQline = new QLineEdit(this);
        groupBoxGrid->addWidget(etaQline, 1, 1);

    QLabel* nIterLabel = new QLabel("Nombre d'itérations : ", this);
        groupBoxGrid->addWidget(nIterLabel, 2, 0);
    QLineEdit* nIterQline = new QLineEdit(this);
        groupBoxGrid->addWidget(nIterQline, 2, 1);


    QGroupBox *settings2 = new QGroupBox(this);
    settings2->setTitle(QString("Splitting the dataset between train and test :"));
    QGridLayout* groupBoxGrid2 = new QGridLayout(settings2);
    settings2->setLayout(groupBoxGrid2);
    grid->addWidget(settings2, 1, 0, 1, 2);

    TrainTestLabel* label = new TrainTestLabel(this);
    groupBoxGrid2->addWidget(label, 1, 0);

    QSlider* slider = new QSlider(Qt::Horizontal, this);
    slider->setTickInterval(100);
    slider->setValue(50);
    slider->setMinimum(1);
    QObject::connect(slider, SIGNAL(valueChanged(int)), label, SLOT(setCustomText(int)));
    groupBoxGrid2->addWidget(slider, 1, 1);

    int train = slider->value();
    QString labelText = "<b>Train/Test : </b>";
    labelText.append(QStringLiteral("%1/%2").arg(train).arg(100-train));
    label->setText(labelText);

}
void TrainDialog::Test()
{
    vector<unsigned int> topo;
    topo.push_back(2);
    topo.push_back(4);
    topo.push_back(3);
    topo.push_back(1);
    Neural_Net My_Neural_Net(topo);
    qDebug() << topo[0];
    //exemple d entrainement du reseau de neuronnes avec le probleme xor
    //on met des 1 ou 0
    vector<double> Xor;
    vector<double> _Xor;
    vector<double> xor_target;//valeur a predire
    for (unsigned nb = 0; nb < 1000; ++nb) {
        Xor.push_back(rand() % 2);
        _Xor.push_back(rand() % 2);
        xor_target.push_back(Xor[nb] == _Xor[nb] ? 0 : 1);
    };
    vector <double> input_vals, result_vals, target_vals;
    input_vals.push_back(_Xor[0]);
    input_vals.push_back(Xor[0]);
    for (unsigned i = 0; i < xor_target.size(); ++i) {
        qDebug() << "valeur a predire: ";
        qDebug() << xor_target[i] << "     ";
        target_vals.push_back(xor_target[i]);
        input_vals[0] = _Xor[i];
        input_vals[1] = Xor[i];
        My_Neural_Net.Feed_Forward(input_vals);
        My_Neural_Net.Get_Results(result_vals);
        My_Neural_Net.Generalized_Delta_Rule(target_vals);

        qDebug() << "valeur predite: ";
        qDebug() << result_vals[0] << "\n";
        target_vals.clear();
    };
}


TrainTestLabel::TrainTestLabel(QWidget* parent): QLabel(parent)
{

}

void TrainTestLabel::setCustomText(int train)
{
    QString labelText = "<b>Train/Test : </b>";
    labelText.append(QStringLiteral("%1/%2").arg(train).arg(100-train));
    this->setText(labelText);
}
