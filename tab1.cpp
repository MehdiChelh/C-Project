#include "tab1.h"

Tab1::Tab1() : QWidget()
{
    grid = new QGridLayout(this);
    this->setLayout(grid);

    //Widget contenant le painter affichant le NN
    paintWidget = new DrawNN(this);
    grid -> addWidget(paintWidget, 1, 0, 1, 6);


    // Juste pour le design de la section de selection des données
    QGroupBox *data_selection_groupbox = new QGroupBox(this);
    data_selection_groupbox->setTitle(QString("Selection des données"));
    //data_selection_groupbox->setStyleSheet("font-size: 18px");
    grid -> addWidget(data_selection_groupbox, 0, 0, 1, 2);

    QHBoxLayout *data_selection_layout = new QHBoxLayout(data_selection_groupbox);
    data_selection_groupbox->setLayout(data_selection_layout);

    //Bouton pour ouvrir la boite de dialogue pour charger les données
    load_data_button = new QPushButton("Load external data", data_selection_groupbox);
    load_data_button -> setCursor(Qt::PointingHandCursor);
    QObject::connect(load_data_button, SIGNAL(clicked()), this, SLOT(loadData()));
    data_selection_layout -> addWidget(load_data_button);

    QPushButton *select_data_button = new QPushButton("Select data", data_selection_groupbox);
    select_data_button -> setCursor(Qt::PointingHandCursor);
    QObject::connect(select_data_button, SIGNAL(clicked()), this, SLOT(selectData()));
    data_selection_layout -> addWidget(select_data_button);

    QLabel *labelNeurons = new QLabel(this);
    labelNeurons->setText("Ajouter une couche :");
    grid->addWidget(labelNeurons, 0,2);

    //Bouton pour ajouter une couche au NN
    add_layer_button = new QPushButton("+", this);
    add_layer_button -> setCursor(Qt::PointingHandCursor);
    QObject::connect(add_layer_button, SIGNAL(clicked()), paintWidget, SLOT(addLayer()));
    QObject::connect(add_layer_button, SIGNAL(clicked()), this, SLOT(enablingDisablingButtons()));
    QObject::connect(add_layer_button, SIGNAL(clicked()), this, SLOT(resetInputFormNeurons()));
    grid -> addWidget(add_layer_button, 0, 4);

    //Input pour le nombre de neurones du NN à ajouter
    inputFormNeurons = new QLineEdit(this);
    inputFormNeurons->setPlaceholderText("");
    inputFormNeurons->setValidator(new QIntValidator(inputFormNeurons));
    QObject::connect(inputFormNeurons, SIGNAL(textChanged(QString)), paintWidget, SLOT(getNumberOfNeurons(QString)));
    QObject::connect(inputFormNeurons, SIGNAL(returnPressed()), add_layer_button, SIGNAL(clicked()));
    grid -> addWidget(inputFormNeurons, 0,3);

    //Bouton pour supprimer la dernière couche du NN
    pop_layer_button = new QPushButton("Supprimer le dernier layer");
    pop_layer_button -> setCursor(Qt::PointingHandCursor);
    pop_layer_button->setDisabled(paintWidget->getNNlayers().size() == 0);
    qDebug() << paintWidget->getNNlayers().size();
    QObject::connect(pop_layer_button, SIGNAL(clicked()), paintWidget, SLOT(popLayer()));
    QObject::connect(pop_layer_button, SIGNAL(clicked()), this, SLOT(enablingDisablingButtons()));
    grid -> addWidget(pop_layer_button, 0, 5);

    //Bouton pour visualiser les données
    QPushButton *data_preprocess_button = new QPushButton("Data preprocessing");
    data_preprocess_button -> setCursor(Qt::PointingHandCursor);
    QObject::connect(data_preprocess_button, SIGNAL(clicked()), this, SLOT(DataPreprocessDialog()));
    grid -> addWidget(data_preprocess_button, 2, 0);

    //Bouton pour visualiser les données
    QPushButton *see_data_button = new QPushButton("Visualiser les données");
    see_data_button -> setCursor(Qt::PointingHandCursor);
    QObject::connect(see_data_button, SIGNAL(clicked()), this, SLOT(seeData()));
    grid -> addWidget(see_data_button, 2, 1);

    //Bouton qui lance le learning
    learning_button = new QPushButton("Entrainer le réseau");
    learning_button -> setCursor(Qt::PointingHandCursor);
    learning_button -> setDisabled(true);
    QObject::connect(learning_button, SIGNAL(clicked()), qApp, SLOT(quit()));
    grid -> addWidget(learning_button, 2, 5);
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
    struct search {
        static void get()
        {
            qDebug() << "nto";
        }
    };

    QDialog *dialog = new QDialog();
    dialog->setWindowTitle(QString("Selection des données provenant de Quandl"));
    QGridLayout *grid = new QGridLayout();
    dialog->setLayout(grid);

    QLineEdit *quandlSearch = new QLineEdit(dialog);
    quandlSearch->setPlaceholderText("");
    grid->addWidget(quandlSearch, 0,0);

    QPushButton *search_button = new QPushButton(dialog);
    search_button->setText(QString("Rechercher"));
    search_button->setCursor(Qt::PointingHandCursor);
//    QObject::connect(search_button, SIGNAL(clicked()), this, SLOT(search::get()));
    grid->addWidget(search_button, 0, 1);

    QListWidget *listWidget = new QListWidget(dialog);

    new QListWidgetItem(tr("Oak"), listWidget);
    new QListWidgetItem(tr("Fir"), listWidget);
    new QListWidgetItem(tr("Pine"), listWidget);

    grid->addWidget(listWidget, 1, 0, 1, 2);

//    CURL *curl;
//    CURLcode res;

//    curl = curl_easy_init();
//    if(curl) {
//        curl_easy_setopt(curl, CURLOPT_URL, "https://www.quandl.com/api/v3/databases.csv?api_key=kuExaMxAa629HY7dRvgH");

//        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

//        res = curl_easy_perform(curl);
//        if(res != CURLE_OK)
//            fprintf(stderr, "curl_easy_perform() failed: %s\n",
//                    curl_easy_strerror(res));

//        curl_easy_cleanup(curl);
//    }

    dialog->show();
}

void Tab1::DataPreprocessDialog()
{
    QDialog *dialog = new QDialog();
    dialog->setWindowTitle(QString("Python code editor for data preprocessing "));
    QGridLayout *grid = new QGridLayout();
    dialog->setLayout(grid);
    dialog -> resize(700, 700*9/16);

    QTextEdit *code = new QTextEdit(dialog);
    code->setStyleSheet("QTextEdit { background: rgb(60, 60, 60); "
                        "selection-background-color: rgb(233, 99, 0); "
                        "color:rgb(255,255,255) }");
    code->setTabStopWidth(20);
    code->setText("import pandas\n\n"
                  "def main(data):\n\t#Your code\n\t#Data is a pandas dataframe\n"
                  "\tdata.to_csv(new_file_name, sep=\"\\t\")\n\n"
                  "main(pandas.read_csv(file_name))");
    MyHighlighter *highlighter = new MyHighlighter(code->document());
    grid -> addWidget(code, 0, 0, 1, 2);

    QTextEdit *console = new QTextEdit(dialog);
    console -> setReadOnly(true);
    grid -> addWidget(console, 1, 0, 1, 2);

    QPushButton *run_code_btn = new QPushButton("Run", dialog);
    run_code_btn->setCursor(Qt::PointingHandCursor);
    grid->addWidget(run_code_btn, 2, 1);

    QPushButton *save_code_btn = new QPushButton("Enregistrer", dialog);
    save_code_btn->setCursor(Qt::PointingHandCursor);
    grid->addWidget(save_code_btn, 2, 0);


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

MyHighlighter::MyHighlighter(QTextDocument *parent): QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    keywordFormat.setForeground(QBrush(QColor(249, 135, 255)));
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\bimport\\b" << "\\bdef\\b"
                    << "\\bfrom\\b" << "\\breturn\\b";
    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegExp(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    quotationFormat.setForeground(QBrush(QColor(57,247,117)));
    rule.pattern = QRegExp("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    functionFormat.setFontItalic(true);
    functionFormat.setForeground(QBrush(QColor(41,255,244)));
    rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);

    singleLineCommentFormat.setForeground(QBrush(QColor(200,200,200)));
    rule.pattern = QRegExp("#[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);
}
void MyHighlighter::highlightBlock(const QString &text)
{
    QTextCharFormat myClassFormat;
    myClassFormat.setFontWeight(QFont::Bold);
    myClassFormat.setForeground(Qt::darkMagenta);
    QString pattern = "\\bMy[A-Za-z]+\\b";


    QRegExp expression(pattern);
    int index = text.indexOf(expression);
    while (index >= 0) {
        int length = expression.matchedLength();
        setFormat(index, length, myClassFormat);
        index = text.indexOf(expression, index + length);
    }


    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }
}


void Tab1::seeData()
{
    QDialog *dialog = new QDialog();
    dialog->setWindowTitle(QString("Visualisation des données"));
    QGridLayout *grid = new QGridLayout();
    dialog->setLayout(grid);
    dialog -> resize(500, 500*9/16);
    QTableWidget *table = new QTableWidget(30, 30, dialog);
    grid -> addWidget(table);
    dialog->show();
}

Tab1::~Tab1()
{
    delete grid;
    delete load_data_button;
    delete add_layer_button;
}
