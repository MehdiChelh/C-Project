#include "quandldialog.h"

QuandlDialog::QuandlDialog() : QDialog()
{
    this->setWindowTitle(QString("Selection des données provenant de Quandl"));
    this->resize(500, 500*9/16);

    grid = new QGridLayout();
    this->setLayout(grid);

    searchKeywords = new QLineEdit(this);
    searchKeywords -> setPlaceholderText("Ex: Apple");
    grid->addWidget(searchKeywords, 0,0);

    search_button = new QPushButton(this);
    search_button->setText(QString("Rechercher"));
    search_button->setCursor(Qt::PointingHandCursor);
//    QObject::connect(search_button, SIGNAL(clicked()), this, SLOT(disableButtons()));
    grid->addWidget(search_button, 0, 1);

    listWidget = new QTreeWidget(this);
    listWidget->setColumnCount(4);
    QStringList columnsLabel;
    columnsLabel << "Name" << "ID" << "Oldest date" << "Newest date";
    listWidget->setHeaderLabels(columnsLabel);
    listWidget->resize(500, 200);
    grid->addWidget(listWidget, 1, 0, 1, 2);

    select_dataset = new QPushButton(this);
    select_dataset->setText("Selectionner");
    select_dataset->setCursor(Qt::PointingHandCursor);
    grid->addWidget(select_dataset, 2, 0, 1, 2);

    search = new QuandlSearch(searchKeywords, listWidget);
    QObject::connect(search_button, SIGNAL(clicked()), search, SLOT(searchResponse()));
    QObject::connect(select_dataset, SIGNAL(clicked()), search, SLOT(selectItem()));

    this->show();
}

void QuandlDialog::disableButtons()
{
    select_dataset->setDisabled(true);
    search_button->setDisabled(true);
}

QuandlDialog::~QuandlDialog()
{
    delete listWidget;
    delete grid;
}
