#include "camion.h"

Camion::Camion(QString pays, float poidsMax, float volumeMax)
{
    mID = QUuid::createUuid().toString(QUuid::WithoutBraces);
    mPays = pays;
    mPoids = 0;
    mPoidsMax = poidsMax;
    mVolume = 0;
    mVolumeMax = volumeMax;
}

Camion::~Camion()
{

}

QString Camion::getID() const
{
    return mID;
}

QList<Colis> Camion::getColisList() const
{
    return mColisList;
}

QString Camion::getPays() const
{
    return mPays;
}

float Camion::getPoids() const
{
    return mPoids;
}

float Camion::getPoidsMax() const
{
    return mPoidsMax;
}

float Camion::getVolume() const
{
    return mVolume;
}

float Camion::getVolumeMax() const
{
    return mVolumeMax;
}

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
