/**
* @file main.cpp
* fichier principal du programme in C++.
* Ce programme est la partie serveur qui
* permet de réceptionner les colis envoyés
* par la partie client, de les charger dans
* un camion et d'imprimer le bordereau de
* transport du camion.
* @author Alexandre Djossou
* @date 15 décembre 2022
* @version 1.0
* @copyright GNU Public License
*/
#include "widget.h"

#include <QApplication>

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

    return a.exec();
}
