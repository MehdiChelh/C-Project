#include "preprocdialog.h"

PreprocDialog::PreprocDialog(): QDialog()
{
    this->setWindowTitle(QString("Python code editor for data preprocessing "));
    QGridLayout *grid = new QGridLayout();
    this->setLayout(grid);
    this -> resize(700, 700*9/16);

    QTextEdit *code = new QTextEdit(this);
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

    QTextEdit *console = new QTextEdit(this);
    console -> setReadOnly(true);
    grid -> addWidget(console, 1, 0, 1, 2);

    QSplitter* splitter = new QSplitter(Qt::Vertical, this);
    grid->addWidget(splitter, 0, 0, 1, 2);
    splitter->addWidget(code);
    splitter->addWidget(console);

    QPushButton *run_code_btn = new QPushButton("Run", this);
    run_code_btn->setCursor(Qt::PointingHandCursor);
    grid->addWidget(run_code_btn, 2, 1);

    QPushButton *save_code_btn = new QPushButton("Enregistrer", this);
    save_code_btn->setCursor(Qt::PointingHandCursor);
    grid->addWidget(save_code_btn, 2, 0);
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
