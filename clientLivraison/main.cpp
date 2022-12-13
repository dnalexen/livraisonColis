#include "widget.h"

#include <QApplication>
#include "colis.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    //w.show();

    Colis monColis(4, 3, 5, "jerome", "france", 12, 'a');

    monColis.info();


    return a.exec();
}
