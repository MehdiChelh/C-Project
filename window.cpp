#include "window.h"
#include "tab1.h"
#include "tab2.h"

Window::Window() : QTabWidget()
{
    const int width = 800;
    const int height = width*9/16;
    resize(width, height);

    tab1 = new Tab1();
    const QString label ="Train";
    this->addTab(tab1, label);

    tab2 = new Tab2();
    const QString label2 ="Test";
    this->addTab(tab2, label2);

}

Window::~Window()
{
    delete button;
    delete tab1;
    delete tab2;
}
