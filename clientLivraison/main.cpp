#include "widget.h"

#include <QApplication>
/*#include "colis.h"
#include "colisA.h"
#include "colisB.h"
#include "colisC.h"
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    /*
    ColisA monColisA(4, 3, 5, "jerome", "france", 12);
    monColisA.info();

    ColisB monColisB(4, 3, 5, "jerome", "france", 12);
    monColisB.info();

    ColisC monColisC(4, 3, 5, "jerome", "france", 12);
    monColisC.info();
    */

    return a.exec();
}
