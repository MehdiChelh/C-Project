#include "tab1.h"

Tab1::Tab1() : QWidget()
{
    grid = new QGridLayout();
    this->setLayout(grid);

    //Widget contenant le painter affichant le NN
    paintWidget = new DrawNN(this);
    grid -> addWidget(paintWidget, 1, 0, 1, 5);

    //Bouton pour ouvrir la boite de dialogue pour charger les données
    load_data_button = new QPushButton("Load external data");
    load_data_button -> setCursor(Qt::PointingHandCursor);
    QObject::connect(load_data_button, SIGNAL(clicked()), this, SLOT(loadData()));
    grid -> addWidget(load_data_button, 0, 0);

    QPushButton *select_data_button = new QPushButton("Select data");
    select_data_button -> setCursor(Qt::PointingHandCursor);
    QObject::connect(select_data_button, SIGNAL(clicked()), this, SLOT(selectData()));
    grid -> addWidget(select_data_button, 0, 1);

    //Input pour le nombre de neurones du NN à ajouter
    inputFormNeurons = new QLineEdit(this);
    inputFormNeurons->setPlaceholderText("Entrer le nombre de neurones du layer");
    inputFormNeurons->setValidator(new QIntValidator(inputFormNeurons));
    QObject::connect(inputFormNeurons, SIGNAL(textChanged(QString)), paintWidget, SLOT(getNumberOfNeurons(QString)));
    grid -> addWidget(inputFormNeurons, 0,2);

    //Bouton pour ajouter une couche au NN
    add_layer_button = new QPushButton("Ajouter un layer");
    add_layer_button -> setCursor(Qt::PointingHandCursor);
    QObject::connect(add_layer_button, SIGNAL(clicked()), paintWidget, SLOT(addLayer()));
    QObject::connect(add_layer_button, SIGNAL(clicked()), this, SLOT(enablingDisablingButtons()));
    QObject::connect(add_layer_button, SIGNAL(clicked()), this, SLOT(resetInputFormNeurons()));
    grid -> addWidget(add_layer_button, 0, 3);

    //Bouton pour supprimer la dernière couche du NN
    pop_layer_button = new QPushButton("Supprimer le dernier layer");
    pop_layer_button -> setCursor(Qt::PointingHandCursor);
    pop_layer_button->setDisabled(paintWidget->getNNlayers().size() == 0);
    qDebug() << paintWidget->getNNlayers().size();
    QObject::connect(pop_layer_button, SIGNAL(clicked()), paintWidget, SLOT(popLayer()));
    QObject::connect(pop_layer_button, SIGNAL(clicked()), this, SLOT(enablingDisablingButtons()));
    grid -> addWidget(pop_layer_button, 0, 4);

    //Bouton pour visualiser les données
    QPushButton *see_data_button = new QPushButton("Visualiser les données");
    see_data_button -> setCursor(Qt::PointingHandCursor);
    QObject::connect(see_data_button, SIGNAL(clicked()), qApp, SLOT(quit()));
    grid -> addWidget(see_data_button, 2, 0);

    //Bouton qui lance le learning
    learning_button = new QPushButton("Entrainer le réseau");
    learning_button -> setCursor(Qt::PointingHandCursor);
    QObject::connect(learning_button, SIGNAL(clicked()), qApp, SLOT(quit()));
    grid -> addWidget(learning_button, 2, 1);
}
void Tab1::resetInputFormNeurons(){
    inputFormNeurons->clear();
}
void Tab1::enablingDisablingButtons(){
    pop_layer_button->setEnabled(paintWidget->getNNlayers().size() > 0);
    learning_button->setEnabled(paintWidget->getNNlayers().size() > 0);
}
void Tab1::loadData()
{
    data = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "*.csv");
    if(data != ""){
        QMessageBox::information(this, "Fichier", "Vous avez sélectionné :\n" + data);
    }
}

void Tab1::selectData()
{
    QStringList items;
    items << tr("Sélectionner les données") << tr("---Financières---") << tr("AAPL") << tr("GOOGL") << tr("---Météorologiques---") << tr("Paris");
    QStringList forbiddenItems;
    forbiddenItems << tr("Sélectionner les données") << tr("---Financières---") << tr("---Météorologiques---") ;
    bool ok;
    QString item = QInputDialog::getItem(this, tr("Train data"),
                                         tr("Jeux de données à mettre en entrée \n "
                                            "pour la phase d'apprentissage :"),
                                         items, 0, false, &ok);
    if (ok && !item.isEmpty() && !forbiddenItems.contains(item))
        labelForDebug->setText(item);
}

Tab1::~Tab1()
{
    delete grid;
    delete load_data_button;
    delete add_layer_button;
}
