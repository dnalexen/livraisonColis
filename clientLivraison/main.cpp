/**
* @file main.cpp
* fichier principal du programme in C++.
* Ce programme est la partie client qui
* permet d'envoyer les colis à la partie serveur.
* @author Alexandre Djossou
* @date 15 deécembre 2022
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
