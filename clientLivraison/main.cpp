#include "widget.h"

#include <QApplication>
#include "colis.h"

/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();


    Colis monColisA(4, 3, 5, "jerome", "france", 12, "A");


    Colis monColisB(4, 3, 10, "jerome", "france", 27, "B");

    qDebug() <<  monColisA%monColisB;
    qDebug() <<  monColisA.operator$(monColisB);

    return a.exec();
}
