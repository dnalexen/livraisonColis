#include "camion.h"

Camion::Camion(QString ID, QString pays, int poidsMax, int volumeMax)
{
    mID = QUuid::createUuid().toString(QUuid::WithoutBraces);
    mPays = pays;
    mPoids = 0;
    mPoidsMax = poidsMax;
    mVolume = 0;
    mVolumeMax = volumeMax;
}

QString Camion::getID() const
{
    return mID;
}

QMap<QString, Colis> Camion::getColisMap() const
{
    return mColisMap;
}

QString Camion::getPays() const
{
    return mPays;
}

float Camion::getPoids() const
{
    return mPoids;
}

int Camion::getPoidsMax() const
{
    return mPoidsMax;
}

int Camion::getVolume() const
{
    return mVolume;
}

int Camion::getVolumeMax() const
{
    return mVolumeMax;
}

bool Camion::addColis(Colis c)
{
    int volumeColis = c.getHauteur() * c.getLargeur() * c.getLongueur();

    if(mPoids + c.getPoids() < mPoidsMax
            &&
       mVolume + volumeColis < mVolumeMax)
    {
       mColisMap.insert(c.getID(), c);
       mVolume += volumeColis;
       mPoids += c.getPoids();

       return true;
    }

    return false;
}
