#include "camion.h"

/**
 * @brief Camion::Camion
 * Ce constructeur de la classe Camion
 * permet de créer un camion.
 * @param pays: pays de destination du camion
 * @param poidsMax: poids maximum du camion
 * @param volumeMax: volume maximum du camion
 */
Camion::Camion(QString pays, float poidsMax, float volumeMax)
{
    mID = QUuid::createUuid().toString(QUuid::WithoutBraces);
    mPays = pays;
    mPoids = 0;
    mPoidsMax = poidsMax;
    mVolume = 0;
    mVolumeMax = volumeMax;
}

/**
 * @brief Camion::getID
 * Cette méthode retourne l'ID du camion.
 * @return QString
 */
QString Camion::getID() const
{
    return mID;
}

/**
 * @brief Camion::getColisList
 * Cette méthode retourne la liste des colis
 * du camion.
 * @return QList<Colis>
 */
QList<Colis> Camion::getColisList() const
{
    return mColisList;
}

/**
 * @brief Camion::getPays
 * Cette méthode retourne le pays de
 * destination du camion.
 * @return QString
 */
QString Camion::getPays() const
{
    return mPays;
}

/**
 * @brief Camion::getPoids
 * Cette méthode retourne le poids du
 * camion.
 * @return float
 */
float Camion::getPoids() const
{
    return mPoids;
}

/**
 * @brief Camion::getPoidsMax
 * Cette méthode retourne le poids
 * maximum du camion.
 * @return float
 */
float Camion::getPoidsMax() const
{
    return mPoidsMax;
}

/**
 * @brief Camion::getVolume
 * Cette méthode retourne le volume
 * du camion.
 * @return float
 */
float Camion::getVolume() const
{
    return mVolume;
}

/**
 * @brief Camion::getVolumeMax
 * Cette méthode retourne le volume
 * maximum du camion.
 * @return float
 */
float Camion::getVolumeMax() const
{
    return mVolumeMax;
}

/**
 * @brief Camion::addColis
 * Cette méthode permet de charger un
 * colis dans le camion.
 * @param c: objet Colis à ajouté
 * @return bool
 */
bool Camion::addColis(Colis& c)
{
    float volumeColis = c.getHauteur() * c.getLargeur() * c.getLongueur();

    if(
        ((mPoids + c.getPoids()) < mPoidsMax)
            &&
        ((mVolume + volumeColis) < mVolumeMax)
       )
    {
       mColisList.append(c);
       mVolume += volumeColis;
       mPoids += c.getPoids();

       return true;
    }
    return false;
}

/**
 * @brief Camion::toString
 * Cette méthode retourne toutes les informations
 * du camion.
 * @return QString
 */
QString Camion::toString()
{
    QString line;
    line += "ID:" + getID() + ";";
    line += "Pays:" + getPays() + ";";
    line += "Poids:" + QString::number(getPoids()) + ";";
    line += "Poids max:" + QString::number(getPoidsMax()) + ";";
    line += "Volume:" + QString::number(getVolume()) + ";";
    line += "Volume max:" + QString::number(getVolumeMax()) + ";";
    line += "Nombre de colis:" + QString::number(mColisList.size());

    return line;
}
