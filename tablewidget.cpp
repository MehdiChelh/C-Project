#include "tablewidget.h"

TableWidget::TableWidget(Data* data, QWidget* parent) : QTableWidget(parent)
{
    this->setColumnCount(1);
    this->setRowCount(1);
    this->setItem(0, 0, new QTableWidgetItem("No data"));

}

void TableWidget::fill(Data* data)
{
    QList<QString> columns_name = data->getColumnsName();
    QList<QString> date = data->getDate();
    std::vector<std::vector <double>> input = data->getInput();
    int cols = std::max(columns_name.length(), 1);
    int rows = std::max((int)input.size(), 1);

    this->setColumnCount(cols);
    this->setRowCount(rows);
    qDebug() << input.size();
    qDebug() << date.size();
    for(int i = 0; i < columns_name.length(); i ++)
        this->setHorizontalHeaderItem(i, new QTableWidgetItem(QString(columns_name[i])));
    for(int i = 0; i < input.size(); i ++)
        this->setVerticalHeaderItem(i, new QTableWidgetItem(QString(date[i])));
    for(int i = 0; i < input.size(); i++){
        for(int j = 0; j < input[i].size(); j++){
            this->setItem(i, j, new QTableWidgetItem(QString::number(input[i][j])));
        }
    }
    qDebug() << "Construction";
}
