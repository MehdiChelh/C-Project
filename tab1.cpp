#include "tab1.h"

Tab1::Tab1() : QWidget()
{
    grid = new QGridLayout();
    this->setLayout(grid);

    //Widget contenant le painter affichant le NN
    paintWidget = new DrawNN(this);
    grid -> addWidget(paintWidget, 1, 0, 1, 6);

    //Bouton pour ouvrir la boite de dialogue pour charger les données
    load_data_button = new QPushButton("Load external data");
    load_data_button -> setCursor(Qt::PointingHandCursor);
    QObject::connect(load_data_button, SIGNAL(clicked()), this, SLOT(loadData()));
    grid -> addWidget(load_data_button, 0, 0);

    QPushButton *select_data_button = new QPushButton("Select data");
    select_data_button -> setCursor(Qt::PointingHandCursor);
    QObject::connect(select_data_button, SIGNAL(clicked()), this, SLOT(selectData()));
    grid -> addWidget(select_data_button, 0, 1);

    QLabel *labelNeurons = new QLabel(this);
    labelNeurons->setText("Ajouter une couche :");
    grid->addWidget(labelNeurons, 0,2);

    //Bouton pour ajouter une couche au NN
    add_layer_button = new QPushButton("+");
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

void Tab1::DataPreprocessDialog()
{
    QDialog *dialog = new QDialog();
    dialog->setWindowTitle(QString("Python code editor for data preprocessing "));
    QGridLayout *grid = new QGridLayout();
    dialog->setLayout(grid);
    dialog -> resize(500, 500*9/16);

    QTextEdit *code = new QTextEdit(dialog);
    code->setStyleSheet("QTextEdit { background: rgb(60, 60, 60); "
                        "selection-background-color: rgb(233, 99, 0); "
                        "color:rgb(255,255,255) }");
    code->setTabStopWidth(20);
    code->setText("def(data):\n\t#Your code\n\t#Data is a pandas dataframe\n\treturn data");
    MyHighlighter *highlighter = new MyHighlighter(code->document());
    grid -> addWidget(code);
    dialog->show();
}

MyHighlighter::MyHighlighter(QTextDocument *parent): QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    QColor color(250,0,0);
    keywordFormat.setForeground(QBrush(QColor(247,89,197)));
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
