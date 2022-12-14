#include "camion.h"

/**
 * @brief Camion::Camion
 * @param pays
 * @param poidsMax
 * @param volumeMax
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
 * @return
 */
QString Camion::getID() const
{
    return mID;
}

/**
 * @brief Camion::getColisList
 * @return
 */
QList<Colis> Camion::getColisList() const
{
    return mColisList;
}

/**
 * @brief Camion::getPays
 * @return
 */
QString Camion::getPays() const
{
    return mPays;
}

/**
 * @brief Camion::getPoids
 * @return
 */
float Camion::getPoids() const
{
    return mPoids;
}

/**
 * @brief Camion::getPoidsMax
 * @return
 */
float Camion::getPoidsMax() const
{
    return mPoidsMax;
}

/**
 * @brief Camion::getVolume
 * @return
 */
float Camion::getVolume() const
{
    return mVolume;
}

/**
 * @brief Camion::getVolumeMax
 * @return
 */
float Camion::getVolumeMax() const
{
    return mVolumeMax;
}

/**
 * @brief Camion::addColis
 * @param c
 * @return
 */
bool Camion::addColis(Colis& c)
{
    float volumeColis = c.getHauteur() * c.getLargeur() * c.getLongueur();

    //qDebug() << "Poids: " << mPoids;
    //qDebug() << "Volume: " << mVolume;

    if(
        ((mPoids + c.getPoids()) < mPoidsMax)
            &&
        ((mVolume + volumeColis) < mVolumeMax)
       )
    {
       //qDebug() << "in";
       mColisList.append(c);
       mVolume += volumeColis;
       mPoids += c.getPoids();

       //qDebug() << "Poids: " << mPoids;
       //qDebug() << "Volume: " << mVolume;

       return true;
    }

    return false;
}

/**
 * @brief Camion::toString
 * @return
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
