#ifndef WINDOW_H
#define WINDOW_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QTabWidget>
#include "tab1.h"

class Window: public QTabWidget
{
public:
    Window();
    ~Window();
private:
    QPushButton *button;
    QWidget *tab1;
    QWidget *tab2;
};

#endif // WINDOW_H
