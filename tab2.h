#ifndef TAB2_H
#define TAB2_H

#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QGridLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QObject>

class Tab2 : public QWidget
{
    Q_OBJECT
public:
    Tab2();
    ~Tab2();
public slots:
    void loadData();
private:
    QGridLayout *grid;
    QPushButton *load_data_button;
    QPushButton *output_file_button;
    QString data;
};

#endif // TAB2_H
