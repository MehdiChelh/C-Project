#include "tablewidget.h"

TableWidget::TableWidget(Data* data, QWidget* parent) : QTableWidget(parent)
{
    this->setColumnCount(1);
    this->setRowCount(1);
    this->setItem(0, 0, new QTableWidgetItem("No data"));

}

void TableWidget::fill(Data* data)
{
    QList<QString> input_col_names = data->getInputColumnsName();
    QList<QString> output_col_names = data->getOutputColumnsName();
    qDebug() << output_col_names;
    QList<QString> date = data->getDate();
    std::vector<std::vector <double>> input = data->getInput();
    std::vector<std::vector <double>> output = data->getOutput();
    int cols = std::max(input_col_names.length() + output_col_names.length(), 1);
    int rows = std::max((int)input.size(), 1);

    this->setColumnCount(cols);
    this->setRowCount(rows);
    qDebug() << input.size();
    qDebug() << date.size();
    for(int i = 0; i < input_col_names.length(); i ++)
        this->setHorizontalHeaderItem(i, new QTableWidgetItem(QString(input_col_names[i])));
    for(int i = 0; i < output_col_names.length(); i ++)
        this->setHorizontalHeaderItem(i + input_col_names.length(), new QTableWidgetItem(QString(output_col_names[i])));
    for(int i = 0; i < input.size(); i ++)
        this->setVerticalHeaderItem(i, new QTableWidgetItem(QString(date[i])));
    for(int i = 0; i < input.size(); i++){
        for(int j = 0; j < input[i].size(); j++){
            this->setItem(i, j, new QTableWidgetItem(QString::number(input[i][j])));
        }
        for(int k = 0; k < output[i].size(); k++){
            this->setItem(i, input[i].size() + k, new QTableWidgetItem(QString::number(output[i][k])));
        }
    }
    qDebug() << "Construction";
}
