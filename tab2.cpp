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

    //Bouton pour ouvrir la boite de dialogue pour charger les données
    QPushButton *predict_data_button = new QPushButton("Predict");
    predict_data_button->setDisabled(true);
    predict_data_button -> setCursor(Qt::PointingHandCursor);
    QObject::connect(predict_data_button, SIGNAL(clicked()), qApp, SLOT(quit()));
    grid -> addWidget(predict_data_button, 0, 1);

    //Bouton pour ouvrir le fichier en output
    output_file_button = new QPushButton("See output file", this);
    output_file_button -> setCursor(Qt::PointingHandCursor);
    output_file_button->setDisabled(true);
    QObject::connect(output_file_button, SIGNAL(clicked()), qApp, SLOT(quit()));
    grid -> addWidget(output_file_button, 0, 2);

    //Simple label qui sert à l'affichage de variables pour débuggage
    QTableWidget *resultsTable = new QTableWidget(this);
//    resultsTable->setFrameStyle(QFrame::Panel | QFrame::Sunken);

//    resultsTable->setText("<table bgcolor=white cellspacing=0 cellpadding=10>"
//                          "<tr><td>Results<td></tr>"
//                          "<tr><td>Loss</td><td>Metric</td></tr>"
//                          "<tr><td>0.13</td><td>87</td></tr></table>");
//    resultsTable->setAlignment( Qt::AlignCenter );
//    resultsTable->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    grid -> addWidget(resultsTable, 1, 0, 1, 3);

    /*QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addText("Hey");
    qreal height = scene->height();
    QGraphicsEllipseItem *ellipse = scene->addEllipse(0, height, 50, 50);
    ellipse->setAcceptHoverEvents(true);

    QGraphicsView *view = new QGraphicsView(scene);
    QSize size = view->size();
    grid->addWidget(view, 1, 1);
    qDebug() << "Hey";*/
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
