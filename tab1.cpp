#include "tab1.h"

Tab1::Tab1() : QWidget()
{
    data = new Data();
    qDebug() << data->isFilled();
    grid = new QGridLayout(this);
    this->setLayout(grid);


    //Widget permettant d'afficher les données
    table = new TableWidget(data, this);
    grid -> addWidget(table, 2, 0, 1, 2);

    // Juste pour le design de la section de selection des données
    QGroupBox *data_selection_groupbox = new QGroupBox(this);
    data_selection_groupbox->setTitle(QString("Selection des données"));
    //data_selection_groupbox->setStyleSheet("font-size: 18px");
    grid -> addWidget(data_selection_groupbox, 0, 0, 1, 2);

    QHBoxLayout *data_selection_layout = new QHBoxLayout(data_selection_groupbox);
    data_selection_groupbox->setLayout(data_selection_layout);

    //Bouton pour ouvrir la boite de dialogue pour charger les données
    load_data_button = new QPushButton("Load custom data", data_selection_groupbox);
    load_data_button -> setCursor(Qt::PointingHandCursor);
    QObject::connect(load_data_button, SIGNAL(clicked()), this, SLOT(loadCustomData()));
    data_selection_layout -> addWidget(load_data_button);

    QLabel* orLabel = new QLabel(this);
    orLabel->setText("or");
    orLabel->setAlignment(Qt::AlignCenter);
    data_selection_layout->addWidget(orLabel);

    QPushButton *select_data_button = new QPushButton("Select data", data_selection_groupbox);
    select_data_button -> setCursor(Qt::PointingHandCursor);
    QObject::connect(select_data_button, SIGNAL(clicked()), this, SLOT(selectData()));
    data_selection_layout -> addWidget(select_data_button);

    TrainTestLabel* label = new TrainTestLabel(this);
    grid->addWidget(label, 1, 0);

    QSlider* slider = new QSlider(Qt::Horizontal, this);
    slider->setTickInterval(100);
    slider->setValue(50);
    slider->setMinimum(1);
    QObject::connect(slider, SIGNAL(valueChanged(int)), label, SLOT(setCustomText(int)));
    grid->addWidget(slider, 1, 1);

    int train = slider->value();
    QString labelText = "<b>Train/Test : </b>";
    labelText.append(QStringLiteral("%1/%2").arg(train).arg(100-train));
    label->setText(labelText);



    //Widget contenant le painter affichant le NN
    paintWidget = new DrawNN(this);
    grid -> addWidget(paintWidget, 1, 2, 2, 4);

    QGroupBox *manage_layers = new QGroupBox(this);
    manage_layers->setTitle(QString("Ajouter/supprimer des couches du réseau de neurones"));
    //data_selection_groupbox->setStyleSheet("font-size: 18px");
    grid -> addWidget(manage_layers, 0, 2, 1, 4);

    QHBoxLayout *manage_layers_layout = new QHBoxLayout(manage_layers);
    manage_layers->setLayout(manage_layers_layout);

    QLabel *labelNeurons = new QLabel(this);
    labelNeurons->setText("Ajouter une couche :");
    manage_layers_layout->addWidget(labelNeurons);


    //Input pour le nombre de neurones du NN à ajouter
    inputFormNeurons = new QLineEdit(this);
    inputFormNeurons->setPlaceholderText("Nombre de neurones");
    inputFormNeurons->setValidator(new QIntValidator(inputFormNeurons));
    QObject::connect(inputFormNeurons, SIGNAL(textChanged(QString)), paintWidget, SLOT(getNumberOfNeurons(QString)));
    manage_layers_layout -> addWidget(inputFormNeurons);

    //Bouton pour ajouter une couche au NN
    add_layer_button = new QPushButton("+", this);
    add_layer_button -> setCursor(Qt::PointingHandCursor);
    QObject::connect(add_layer_button, SIGNAL(clicked()), paintWidget, SLOT(addLayer()));
    QObject::connect(add_layer_button, SIGNAL(clicked()), this, SLOT(enablingDisablingButtons()));
    QObject::connect(add_layer_button, SIGNAL(clicked()), this, SLOT(resetInputFormNeurons()));
    manage_layers_layout -> addWidget(add_layer_button);

    QObject::connect(inputFormNeurons, SIGNAL(returnPressed()), add_layer_button, SIGNAL(clicked()));

    //Bouton pour supprimer la dernière couche du NN
    pop_layer_button = new QPushButton("Supprimer le dernier layer");
    pop_layer_button -> setCursor(Qt::PointingHandCursor);
    pop_layer_button->setDisabled(paintWidget->getNNlayers().size() == 0);
    qDebug() << paintWidget->getNNlayers().size();
    QObject::connect(pop_layer_button, SIGNAL(clicked()), paintWidget, SLOT(popLayer()));
    QObject::connect(pop_layer_button, SIGNAL(clicked()), this, SLOT(enablingDisablingButtons()));
    manage_layers_layout -> addWidget(pop_layer_button);



    //Bouton pour faire un prétraitement des données
    QPushButton *data_preprocess_button = new QPushButton("Data preprocessing");
    data_preprocess_button -> setCursor(Qt::PointingHandCursor);
    QObject::connect(data_preprocess_button, SIGNAL(clicked()), this, SLOT(DataPreprocessDialog()));
    grid -> addWidget(data_preprocess_button, 3, 0);


    //Bouton qui lance le learning
    learning_button = new QPushButton("Entrainer le réseau");
    learning_button -> setCursor(Qt::PointingHandCursor);
    learning_button -> setDisabled(true);
//    QObject::connect(learning_button, SIGNAL(clicked()), qApp, SLOT(quit()));
    TrainDialog *tesst = new TrainDialog();
    QObject::connect(learning_button, SIGNAL(clicked()), tesst, SLOT(Test()));
    grid -> addWidget(learning_button, 3, 5);
}
void Tab1::resetInputFormNeurons(){
    inputFormNeurons->clear();
}
void Tab1::enablingDisablingButtons(){
    pop_layer_button->setEnabled(paintWidget->getNNlayers().size() > 0);
    learning_button->setEnabled(paintWidget->getNNlayers().size() > 0);
}
void Tab1::loadCustomData()
{

    pathToCSV = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "*.csv");
    if(pathToCSV != ""){
        QMessageBox::information(this, "Fichier", "Vous avez sélectionné :\n" + pathToCSV.split("/").last());
        QList<QByteArray> columns = data->getColumnsOfCSV(pathToCSV);
        QList<QString> col = Data::byteArraysToStrings(columns);
        QList<QString> selectedColumns = selectItemsDialog("Select columns to keep", col);
        QList<QString> dateColumnLabel = selectItemsDialog("Select date label", col);
        QList<QString> outputColumns = selectItemsDialog("Select the output labels", selectedColumns);
        if(dateColumnLabel.length() == 1 && outputColumns.length() >= 1){
            data->openCSV(pathToCSV, selectedColumns, dateColumnLabel[0], outputColumns);
            table->fill(data);
        }
    }
}

void Tab1::selectData()
{
//    QStringList items;
//    items << tr("Sélectionner le type de données") << tr("Financières avec l'API Quandl") << tr("NOAA");
    QDialog *dialog = new QDialog();
    dialog->setWindowTitle(QString("Selection les données"));
    QHBoxLayout *grid = new QHBoxLayout();
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setLayout(grid);

    QPushButton *NOAA = new QPushButton("Données météo", dialog);
    grid ->addWidget(NOAA);

    QPushButton *quandl = new QPushButton("Données provenant de Quandl", dialog);
    QObject::connect(quandl, SIGNAL(clicked()), this, SLOT(QuandlDialog()));
    QObject::connect(quandl, SIGNAL(clicked()), dialog, SLOT(close()));
    grid ->addWidget(quandl);

    dialog->show();
}

void Tab1::QuandlDialog()
{
    class QuandlDialog* quandlDialog = new class QuandlDialog(data, table);
    quandlDialog->show();
}

void Tab1::DataPreprocessDialog()
{
    PreprocDialog* dialog = new PreprocDialog();
    dialog->show();


    /*Py_Initialize();
    PyObject *pModule = PyImport_AddModule("__main__");
    PyRun_SimpleString("from time import time,ctime\n"
                       "print('Today is', ctime(time()))\n");
    Py_Finalize();


    PythonQt::init();
    PythonQtObjectPtr mainModule =
                      PythonQt::self()->getMainModule();
    QVariant result = mainModule.evalScript(
                    mainModule, "19*2+4", Py_eval_input);
    qDebug() << result;*/
}

QList<QString> Tab1::selectItemsDialog(QString title, QList<QString> items)
{
    QDialog* selectColumnsDialog = new QDialog();
    selectColumnsDialog->setWindowTitle(title);
    QGridLayout* dialogGrid = new QGridLayout(selectColumnsDialog);
    selectColumnsDialog->setLayout(dialogGrid);
    QListWidget* listWidget = new QListWidget();
    for(int i = 0; i < items.length(); i++){
        listWidget->addItem(items[i]);
    }
    listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    dialogGrid->addWidget(listWidget, 0, 0);
    QPushButton* close_button = new QPushButton("Select", selectColumnsDialog);
    QObject::connect(close_button, SIGNAL(clicked()), selectColumnsDialog, SLOT(close()));
    dialogGrid->addWidget(close_button, 1, 0);
    if(selectColumnsDialog->exec() == QDialog::Accepted){
        //La condition dans le if permet d'attendre la fermeture de la boit de dialogue
        qDebug() << "DialogCode : Accepted";
    }
    QList<QListWidgetItem*> selectedItems = listWidget->selectedItems();
    QList<QString> selectedRows;
    for(int i = 0; i < selectedItems.length(); i++){
        selectedRows.append(selectedItems[i]->text());
    }
    return selectedRows;
}

Tab1::~Tab1()
{
    delete grid;
    delete load_data_button;
    delete add_layer_button;
    delete data;
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
