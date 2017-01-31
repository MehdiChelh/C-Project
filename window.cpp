#include "window.h"

Window::Window() : QTabWidget()
{
    const int width = 950;
    const int height = width*9/16;
    resize(width, height);

    tab1 = new Tab1();
    const QString label ="Train/Test";
    this->addTab(tab1, label);

}

Window::~Window()
{
    delete button;
    delete tab1;
    delete tab2;
}
