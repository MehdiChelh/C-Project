#include "tab2.h"

Tab2::Tab2() : QWidget()
{
    grid = new QGridLayout();
    this->setLayout(grid);

    //Bouton pour ouvrir la boite de dialogue pour charger les données
    load_data_button = new QPushButton("Load external data");
    load_data_button -> setCursor(Qt::PointingHandCursor);
    QObject::connect(load_data_button, SIGNAL(clicked()), this, SLOT(loadData()));
    grid -> addWidget(load_data_button, 0, 0);

    //Bouton pour ouvrir le fichier en output
    output_file_button = new QPushButton("See output file", this);
    output_file_button -> setCursor(Qt::PointingHandCursor);
    output_file_button->setDisabled(true);
    QObject::connect(output_file_button, SIGNAL(clicked()), qApp, SLOT(quit()));
    grid -> addWidget(output_file_button, 0, 1);
}
void Tab2::loadData()
{
    data = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "*.csv");
    if(data != ""){
        QMessageBox::information(this, "Fichier", "Vous avez sélectionné :\n" + data);
    }
}

Tab2::~Tab2()
{
    delete output_file_button;
}
