#include "tab1.h"

Tab1::Tab1() : QWidget()
{
    data = new Data();
    grid = new QGridLayout(this);
    this->setLayout(grid);

    grid->setColumnMinimumWidth(0, 200);
    grid->setColumnMinimumWidth(1, 200);


    //Widget permettant d'afficher les données
    table = new TableWidget(data, this);
    grid -> addWidget(table, 3, 0, 1, 2);

    // Juste pour le design de la section de selection des données
    QGroupBox *data_selection_groupbox = new QGroupBox(this);
    data_selection_groupbox->setTitle(QString("Select data"));
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

    QPushButton *select_data_button = new QPushButton("Load data from Quandl", data_selection_groupbox);
    select_data_button -> setCursor(Qt::PointingHandCursor);
    QObject::connect(select_data_button, SIGNAL(clicked()), this, SLOT(QuandlDialog()));
    data_selection_layout -> addWidget(select_data_button);


    comboBox_1 = new QComboBox(this);
        comboBox_1->addItem(tr("--No column--"));
        grid->addWidget(comboBox_1, 1, 0);

    QPushButton* duplicate_column_btn = new QPushButton("Duplicate column", this);
        duplicate_column_btn -> setCursor(Qt::PointingHandCursor);
        QObject::connect(duplicate_column_btn, SIGNAL(clicked()), this, SLOT(duplicateColumn()));
        grid->addWidget(duplicate_column_btn, 1, 1);


    comboBox_2 = new QComboBox(this);
        comboBox_2->addItem(tr("--No column--"));
        grid->addWidget(comboBox_2, 2, 0);

    QPushButton* shift_column_btn = new QPushButton("Shift column", this);
        shift_column_btn -> setCursor(Qt::PointingHandCursor);
        QObject::connect(shift_column_btn, SIGNAL(clicked()), this, SLOT(shiftColumn()));
        grid->addWidget(shift_column_btn, 2, 1);



    //Widget contenant le painter affichant le NN
    paintWidget = new DrawNN(this);
    grid -> addWidget(paintWidget, 1, 2, 3, 4);

    QGroupBox *manage_layers = new QGroupBox(this);
    manage_layers->setTitle(QString("Add/remove layers"));
    //data_selection_groupbox->setStyleSheet("font-size: 18px");
    grid -> addWidget(manage_layers, 0, 2, 1, 4);

    QHBoxLayout *manage_layers_layout = new QHBoxLayout(manage_layers);
    manage_layers->setLayout(manage_layers_layout);

//    QLabel *labelNeurons = new QLabel(this);
//    labelNeurons->setText("Ajouter une couche :");
//    manage_layers_layout->addWidget(labelNeurons);


    //Input pour le nombre de neurones du NN à ajouter
    inputFormNeurons = new QLineEdit(this);
    inputFormNeurons->setPlaceholderText("Number of neurons");
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
    pop_layer_button = new QPushButton("Remove last layer");
    pop_layer_button -> setCursor(Qt::PointingHandCursor);
    pop_layer_button->setDisabled(paintWidget->getNNlayers()->size() == 0);
    QObject::connect(pop_layer_button, SIGNAL(clicked()), paintWidget, SLOT(popLayer()));
    QObject::connect(pop_layer_button, SIGNAL(clicked()), this, SLOT(enablingDisablingButtons()));
    manage_layers_layout -> addWidget(pop_layer_button);



    //Bouton pour faire un prétraitement des données
    QPushButton *data_preprocess_button = new QPushButton("Data preprocessing");
    data_preprocess_button -> setCursor(Qt::PointingHandCursor);
    QObject::connect(data_preprocess_button, SIGNAL(clicked()), this, SLOT(DataPreprocessDialog()));
    grid -> addWidget(data_preprocess_button, 4, 0);


    //Bouton qui lance le learning
    learning_button = new QPushButton("Train the model");
    learning_button -> setCursor(Qt::PointingHandCursor);
    learning_button -> setDisabled(true);
    TrainDialog *tesst = new TrainDialog(this, data, paintWidget->getNNlayers());
    QObject::connect(learning_button, SIGNAL(clicked()), tesst, SLOT(show()));
    grid -> addWidget(learning_button, 4, 5);
}
void Tab1::resetInputFormNeurons(){
    inputFormNeurons->clear();
}
void Tab1::enablingDisablingButtons(){
    pop_layer_button->setEnabled(paintWidget->getNNlayers()->size() > 0);
    learning_button->setEnabled(paintWidget->getNNlayers()->size() > 0 && data->isFilled());
}
void Tab1::loadCustomData()
{

    pathToCSV = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "*.csv");
    if(pathToCSV != ""){
        QMessageBox::information(this, "Fichier", "Vous avez sélectionné :\n" + pathToCSV.split("/").last());
        QList<QByteArray> columns = data->getColumnsOfCSV(pathToCSV);
        QList<QString> col = Data::byteArraysToStrings(columns);
        QList<QString> dateColumnLabel = selectItemsDialog("Select date label", "Select the label associate with the date of your time serie. If your data is not a time serie just click the button bellow without selecting any label.",  col);
        QList<QString> inputColumns = selectItemsDialog("Select input labels", "Select the label(s) that you want to use as input variables in your model", col);
        QList<QString> outputColumns = selectItemsDialog("Select output labels", "Select the label(s) that you want to use as output variables in your model", col);
        if(dateColumnLabel.length() == 0)
            dateColumnLabel.append("");
        if(dateColumnLabel.length() == 1 && outputColumns.length() >= 1){
            data->openCSV(pathToCSV, inputColumns, dateColumnLabel[0], outputColumns);
            table->fill(data);
            comboBox_1->clear();
            comboBox_1->addItems(inputColumns);
            comboBox_2->clear();
            comboBox_2->addItems(inputColumns);
        }
    }
    enablingDisablingButtons();
}

void Tab1::selectData()
{
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
    class QuandlDialog* quandlDialog = new class QuandlDialog(data, table, comboBox_1, comboBox_2);
    quandlDialog->show();
    enablingDisablingButtons();
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

QList<QString> Tab1::selectItemsDialog(QString title, QString stringLabel, QList<QString> items)
{
    QDialog* selectColumnsDialog = new QDialog();
    selectColumnsDialog->setWindowTitle(title);
    QGridLayout* dialogGrid = new QGridLayout(selectColumnsDialog);
    selectColumnsDialog->setLayout(dialogGrid);
    QLabel* label = new QLabel(stringLabel, selectColumnsDialog);
    dialogGrid->addWidget(label, 0, 0);
    QListWidget* listWidget = new QListWidget(selectColumnsDialog);
    for(int i = 0; i < items.length(); i++){
        listWidget->addItem(items[i]);
    }
    listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    dialogGrid->addWidget(listWidget, 1, 0);
    QPushButton* close_button = new QPushButton("Select", selectColumnsDialog);
    QObject::connect(close_button, SIGNAL(clicked()), selectColumnsDialog, SLOT(close()));
    dialogGrid->addWidget(close_button, 2, 0);
    if(selectColumnsDialog->exec() == QDialog::Accepted){
        //La condition dans le if permet d'attendre la fermeture de la boite de dialogue
    }
    QList<QListWidgetItem*> selectedItems = listWidget->selectedItems();
    QList<QString> selectedRows;
    for(int i = 0; i < selectedItems.length(); i++){
        selectedRows.append(selectedItems[i]->text());
    }
    return selectedRows;
}

void Tab1::duplicateColumn()
{
    if(comboBox_1->currentText() != "--No column--"){
        data->duplicateColumn(comboBox_1->currentText());
        table->fill(data);
        comboBox_1->clear();
        comboBox_1->addItems(data->getInputColumnsName());
        comboBox_2->clear();
        comboBox_2->addItems(data->getInputColumnsName());
    }
}

void Tab1::shiftColumn()
{
    if(comboBox_1->currentText() != "--No column--" && data->getInput().size() > 1){
        data->shiftColumn(comboBox_2->currentText());
        table->fill(data);
        comboBox_1->clear();
        comboBox_1->addItems(data->getInputColumnsName());
        comboBox_2->clear();
        comboBox_2->addItems(data->getInputColumnsName());
    }
}

Tab1::~Tab1()
{
    delete grid;
    delete load_data_button;
    delete add_layer_button;
    delete data;
}



