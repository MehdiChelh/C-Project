#ifndef PREPROCDIALOG_H
#define PREPROCDIALOG_H

#include <QObject>
#include <QSyntaxHighlighter>
#include <QDialog>
#include <QTextEdit>
#include <QDialog>
#include <QPushButton>
#include <QGridLayout>
#include <QSplitter>

class PreprocDialog: public QDialog
{
public:
    PreprocDialog();
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

#endif // PREPROCDIALOG_H
