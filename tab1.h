#ifndef TAB1_H
#define TAB1_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QIntValidator>
#include <QGridLayout>
#include <QPainter>
#include <QPaintEvent>
#include <QtGlobal>
#include <vector>
#include <QObject>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QLabel>
#include <QDebug>
#include <QDialog>
#include <QTableWidget>
#include <QTextEdit>
#include <QColor>
#include <QSyntaxHighlighter>
#include <QGroupBox>
#include <QListWidget>
#include <curl/curl.h>
#include <Python/Python.h>
//#include "PythonQt3.1/src/PythonQt.h"
#include "drawnn.h"

class Tab1 : public QWidget
{
    Q_OBJECT
public:
    Tab1();
    ~Tab1();
public slots:
    void resetInputFormNeurons();
    void loadData();
    void selectData();
    void enablingDisablingButtons();
    void seeData();
    void DataPreprocessDialog();
    void QuandlDialog();
private:
    QGridLayout *grid;
    QPushButton *load_data_button;
    QPushButton *add_layer_button;
    QPushButton *pop_layer_button;
    QPushButton *learning_button;
    QLineEdit * inputFormNeurons;
    QLabel *labelForDebug;
    QString data;
    DrawNN *paintWidget;
};


class MyHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    MyHighlighter(QTextDocument * parent);
    void highlightBlock(const QString &text);
private:
    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;
    QTextCharFormat keywordFormat;
    QTextCharFormat quotationFormat;
    QTextCharFormat functionFormat;
    QTextCharFormat singleLineCommentFormat;
};

#endif // TAB1_H
