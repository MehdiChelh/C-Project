#include "traindialog.h"

TrainDialog::TrainDialog(QWidget* parent, Data* _data, std::vector<unsigned int>* _topology): QDialog(parent)
{
    data = _data;
    topology = _topology;

    this->setWindowTitle("Train and test");

    QGridLayout* grid = new QGridLayout(this);
    this->setLayout(grid);

    QGroupBox *settings = new QGroupBox(this);
    settings->setTitle(QString("Settings of the learning :"));
    QGridLayout* groupBoxGrid = new QGridLayout(settings);
    settings->setLayout(groupBoxGrid);
    grid->addWidget(settings, 0, 0);

    QLabel* alphaLabel = new QLabel("Alpha : ", this);
        groupBoxGrid->addWidget(alphaLabel, 0, 0);
    alphaQline = new QLineEdit(this);
        groupBoxGrid->addWidget(alphaQline, 0, 1);

    QLabel* etaLabel = new QLabel("Eta : ", this);
        groupBoxGrid->addWidget(etaLabel, 1, 0);
    etaQline = new QLineEdit(this);
        groupBoxGrid->addWidget(etaQline, 1, 1);

    QLabel* nIterLabel = new QLabel("Nombre d'itérations : ", this);
        groupBoxGrid->addWidget(nIterLabel, 2, 0);
    nIterQline = new QLineEdit(this);
        groupBoxGrid->addWidget(nIterQline, 2, 1);


    QGroupBox *settings2 = new QGroupBox(this);
    settings2->setTitle(QString("Splitting the dataset between train and test :"));
    QGridLayout* groupBoxGrid2 = new QGridLayout(settings2);
    settings2->setLayout(groupBoxGrid2);
    grid->addWidget(settings2, 1, 0);

    TrainTestLabel* label = new TrainTestLabel(this);
    groupBoxGrid2->addWidget(label, 1, 0);

    slider = new QSlider(Qt::Horizontal, this);
    slider->setTickInterval(100);
    slider->setValue(50);
    slider->setMinimum(1);
    QObject::connect(slider, SIGNAL(valueChanged(int)), label, SLOT(setCustomText(int)));
    groupBoxGrid2->addWidget(slider, 2, 0);
    int train = slider->value();
    QString labelText = "<b>Train/Test : </b>";
    labelText.append(QStringLiteral("%1/%2").arg(train).arg(100-train));
    label->setText(labelText);




    QPushButton* traintest_btn = new QPushButton("TRAIIIIN MOTHERFUCKER !", this);
    traintest_btn -> setCursor(Qt::PointingHandCursor);
    QObject::connect(traintest_btn, SIGNAL(clicked()), this, SLOT(TrainTest()));
    grid->addWidget(traintest_btn, 2, 0);

    QLabel* progression = new QLabel("Progression : ", this);
        progression->hide();
        QObject::connect(traintest_btn, SIGNAL(clicked()), progression, SLOT(show()));
        grid->addWidget(progression, 3, 0);

    trainProgress = new QProgressBar(this);
        trainProgress->hide();
        grid->addWidget(trainProgress, 4, 0);

    mseList = new QTreeWidget(this);
        QStringList list;
        list << QString("Iteration") << QString("MSE");
        mseList->setHeaderItem(new QTreeWidgetItem(list));
        mseList->hide();
        grid->addWidget(mseList, 5, 0);

    test_btn = new QPushButton("See performance on test dataset >", this);
        test_btn -> setCursor(Qt::PointingHandCursor);
        test_btn -> hide();
        QObject::connect(test_btn, SIGNAL(clicked()), this, SLOT(Test()));
        grid->addWidget(test_btn, 6, 0);

    test_groupbox = new QGroupBox(this);
        test_groupbox->setTitle(QString("Performance on test datset"));
        test_groupbox->hide();
        grid -> addWidget(test_groupbox, 0, 1, 7, 1);

    QVBoxLayout *test_groupbox_layout = new QVBoxLayout(test_groupbox);
        test_groupbox->setLayout(test_groupbox_layout);

    testRMSEResult = new QLabel(this);
        testRMSEResult->setText("");
        QObject::connect(test_btn, SIGNAL(clicked()), testRMSEResult, SLOT(show()));
        test_groupbox_layout->addWidget(testRMSEResult);

    testResultsList = new QTreeWidget(this);
        test_groupbox_layout->addWidget(testResultsList);
}


void TrainDialog::TrainTest()
{
    mseList->clear();
    trainProgress->setValue(0);
    QMessageBox* message;
    if(topology->size() > 0 && data->getInput().size() > 0 && data->getOutput().size()){
        if((*topology)[0] == data->getInput()[0].size())
        {
            if((*topology)[topology->size()-1] == data->getOutput()[0].size()){
                if(alphaQline->text().toDouble() > 0 && etaQline->text().toDouble() > 0 && nIterQline->text().toDouble() > 0){
                    trainProgress->show();
                    mseList->show();
                    test_btn->show();
                    double split_value = slider->value();
                    std::vector<std::vector<std::vector<double>>> train_test_data = data->splitData(split_value);
                    //On normalise les données :
                    Data::normalizeData(&train_test_data);
                    //On stock les jeux de données d'entrainement et de test dans dans vector différents
                    train_input = train_test_data[0];
                    train_output = train_test_data[1];
                    test_input = train_test_data[2];
                    test_output = train_test_data[3];
                    qDebug() << "Train input size : " << train_input.size();

                    //On paramètre la barre de progression de l'avancement du learning :
                    trainProgress->setMinimum(0);
                    trainProgress->setMaximum(nIterQline->text().toDouble()*train_input.size());
                    Train_Test = new Training_Data(*topology);
                    QObject::connect(Train_Test, SIGNAL(signalProgress(int)), trainProgress, SLOT(setValue(int)));
                    QObject::connect(Train_Test, SIGNAL(signalMSE(QString)), this, SLOT(addMSEListItem(QString)));
                    Train_Test->Train(nIterQline->text().toDouble(), alphaQline->text().toDouble(),
                                  etaQline->text().toDouble(), train_input, train_output);
                }else{
                    message = new QMessageBox(QMessageBox::Warning, "Error", "Alpha, eta and the number of iterations can't be null.");
                    message->show();
                }
            }else{
                message = new QMessageBox(QMessageBox::Warning, "Error", "The number of neurons on the output layer should be the same as the number of output variables.");
                message->show();
            }
        }else{
            message = new QMessageBox(QMessageBox::Warning, "Error", "The number of neurons on the input layer should be the same as the number of input variables.");
            message->show();
        }
    }else{
        message = new QMessageBox(QMessageBox::Warning, "Error", "You have to choose input and output data and a neural network topology.");
        message->show();
    }
}

void TrainDialog::addMSEListItem(QString val)
{
    mseList->addTopLevelItem(new QTreeWidgetItem(val.split("_")));
}


void TrainDialog::Test()
{
    test_groupbox->show();
    QList<QString> resultColumnsName;
    for(int i = 0; i < data->getOutputColumnsName().size(); i++){
        resultColumnsName.append("[Pred.] " + data->getOutputColumnsName()[i]);
    }
    testResultsList->setHeaderLabels(data->getOutputColumnsName() + resultColumnsName);
    this->resize(800, 800*9/16);
    TestResult result = Train_Test->Test(test_input, test_output);

    //On affiche le RMSE dans la fenêtre
    QString text = "The RMSE (Root Mean Square Error) value on the "
                   "test dataset is : <br/>" + QString::number(result.getRMSE());
    testRMSEResult->setText(text);
    testResultsList->show();

    //On remplit le tableau affichant les valeurs prédites
    for(int i = 0; i < test_output.size(); i++){
        QList<QString> list;
        for(int k = 0; k < test_output[i].size(); k++)
            list << QString::number(test_output[i][k]);
        for(int k = 0; k < result.getOutputValues()[i].size(); k++)
            list << QString::number(result.getOutputValues()[i][k]);
        testResultsList->addTopLevelItem(new QTreeWidgetItem(list));
    }
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
