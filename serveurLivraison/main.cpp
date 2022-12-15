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
#include "dbmanager.h"
#include "colis.h"
#include "camion.h"

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

//    Colis c1(1.2, 2.3, 3.1, "Elena", "Portugal", "Moyen");
//    Colis c2(1.2, 5, 3, "Elena", "Suisse", "Petit");
//    Camion ca1("Espagne", 120, 15000);
//    Camion ca2("Allemagne", 105.9, 16000);

//    DbManager db("Livraison");
//    db.createTable("tableColis");
//    db.createTable("tableCamion");

//    db.addColis(c1);
//    db.addColis(c2);
//    db.addCamion(ca1);
//    db.addCamion(ca2);

    //qDebug() << db.updatePoidsCamion("e2359e73-eb73-42ab-a911-60c02b2b460f", 5.55);
    //qDebug() << db.updateVolumeCamion("e2359e73-eb73-42ab-a911-60c02b2b460f", 37.98);

    return a.exec();
}
