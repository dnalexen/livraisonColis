#ifndef CAMION_H
#define CAMION_H

#include <QObject>
#include <QUuid>
#include <QList>
#include "colis.h"

/**
 * @class Camion
 * @brief La classe Camion crée un camion,
 * donne des informations sur ce camion et
 * y ajoute un colis.
 */
class Camion
{
public:
    /**
     * @brief Camion
     * Ce constructeur de la classe Camion
     * permet de créer un camion.
     * @param pays: pays de destination du camion
     * @param poidsMax: poids maximum du camion
     * @param volumeMax: volume maximum du camion
     */
    Camion(QString pays, float poidsMax, float volumeMax);

    /**
     * @brief Destructeur
     */
    ~Camion();

    /**
     * @brief getID
     * Cette méthode retourne l'ID du camion.
     * @return QString
     */
    QString getID() const;

    /**
     * @brief getColisList
     * Cette méthode retourne la liste des colis
     * du camion.
     * @return QList<Colis>
     */
    QList<Colis> getColisList() const;

    /**
     * @brief getPays
     * Cette méthode retourne le pays de
     * destination du camion.
     * @return QString
     */
    QString getPays() const;

    /**
     * @brief getPoids
     * Cette méthode retourne le poids du
     * camion.
     * @return float
     */
    float getPoids() const;

    /**
     * @brief getPoidsMax
     * Cette méthode retourne le poids
     * maximum du camion.
     * @return float
     */
    float getPoidsMax() const;

    /**
     * @brief getVolume
     * Cette méthode retourne le volume
     * du camion.
     * @return float
     */
    float getVolume() const;

    /**
     * @brief getVolumeMax
     * Cette méthode retourne le volume
     * maximum du camion.
     * @return float
     */
    float getVolumeMax() const;

    /**
     * @brief Camion::addColis
     * Cette méthode permet de charger un
     * colis dans le camion.
     * @param c: objet Colis à ajouté
     * @return bool: true - colis ajouté, false - colis pas ajouté
     */
    bool addColis(Colis&);

    /**
     * @brief Camion::toString
     * Cette méthode retourne toutes les informations
     * du camion.
     * @return QString
     */
    QString toString();

protected:
    QString mID;
    QList<Colis> mColisList;
    QString mPays;
    float mPoids;
    float mPoidsMax;
    float mVolume;
    float mVolumeMax;
};

#endif // CAMION_H
