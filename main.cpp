#include "window.h"
#include <QApplication>
#include "data/global.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    g=new Global;
    g->initThis();

    Window w;
    w.show();

    return a.exec();
}
