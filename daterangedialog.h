#ifndef DATERANGEDIALOG_H
#define DATERANGEDIALOG_H

#include <QLineEdit>
#include <QDialog>
#include <QGridLayout>

class DateRangeDialog: public QDialog
{
public:
    DateRangeDialog(QLineEdit* _datemax, QLineEdit* _datemin);
private:
    QLineEdit* datemax;
    QLineEdit* datemin;
};

#endif // DATERANGEDIALOG_H
