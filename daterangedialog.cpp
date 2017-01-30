#include "daterangedialog.h"

DateRangeDialog::DateRangeDialog(QLineEdit* _datemax, QLineEdit* _datemin): QDialog()
{
    datemax = _datemax;
    datemin = _datemin;
    this->setWindowTitle("Entrer les dates de début et de fin de l'étude");
    QGridLayout* grid = new QGridLayout(this);
    this->setLayout(grid);

    grid->addWidget(datemax, 1, 1);
    grid->addWidget(datemin, 1, 2);
//    QPushButton* download_data = new QPushButton("ok", this);
//    QObject::connect(download_data, SIGNAL(clicked()), this, SLOT(close()));
//    grid->addWidget(download_data, 2, 1);
}
