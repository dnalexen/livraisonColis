#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QPdfWriter>
#include <QPainter>
#include "camion.h"
#include "dbmanager.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

/**
 * @class Widget
 * @brief Widget affiche la fenêtre du serveur
 */
class Widget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructeur de la classe Widget
     * @param parent: pointeur null
     */
    Widget(QWidget *parent = nullptr);

    /**
     * Destructeur de la classe Widget
     */
    ~Widget();

private slots:
    /**
     * @brief clientConnected
     * Cette méthode gère la connection
     * d'un client au serveur.
     */
    void clientConnected();

    /**
     * @brief clientDisconnected
     * Cette méthode gère la déconnection
     * d'un client du serveur.
     */
    void clientDisconnected();

    /**
     * @brief colisArrive
     * Cette méthode permet de réceptionner un colis
     * et le charger dans un camion.
     */
    void colisArrive();

    /**
     * @brief envoiCamion
     * Cette méthode permet de générer le bordereau
     * de transport d'un Camion.
     * @param ptrCamion: pointeur d'un Camion
     */
    void envoiCamion(Camion* ptrCamion);

    /**
     * @brief miseAJourFenetre
     * Cette méthode met à jour l'interface de
     * chargement des camions.
     * @param pays: pays de destination du camion
     * @param poids: poids du camion
     * @param volume: volume du camion
     * @param c: colis ajouté au camion
     */
    void miseAJourFenetre(QString pays, float poids, float volume, Colis c);
private:
    Ui::Widget *ui; //Pointeur d'un objet de la classe Widget
    QTcpServer* mServer; //Pointeur du serveur TCP
    QList<QTcpSocket*> mClients; //Liste de clients connectés au serveur TCP
    QList<Camion*> mListCamions; //Liste de camions
    DbManager* mDB = new DbManager(); //Connexion à la Base de Données Livraison
};
#endif // WIDGET_H
