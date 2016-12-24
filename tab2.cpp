#include "tab2.h"

Tab2::Tab2() : QWidget()
{
    button = new QPushButton("Button by Louis Vuitton", this);
    button -> setCursor(Qt::PointingHandCursor);
    QObject::connect(button, SIGNAL(clicked()), qApp, SLOT(quit()));
}
Tab2::~Tab2()
{
    delete button;
}
