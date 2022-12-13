#include "colis.h"

Colis::Colis(int hauteur, int largeur,
             int longueur, QString nom,
             QString pays, int poids,
             int type)
{
    mID = QUuid::createUuid().toString(QUuid::WithoutBraces);
    mHauteur = hauteur;
    mLargeur = largeur;
    mLongueur = longueur;
    mNom = nom;
    mPays = pays;
    mPoids = poids;
    mType = type;
}

Colis::Colis(QByteArray)
{

}

QByteArray Colis::toJson()
{
    return NULL;
}

QString Colis::getID() const
{
    return mID;
}

int Colis::getHauteur() const
{
    return mHauteur;
}

int Colis::getLargeur() const
{
    return mLargeur;
}

int Colis::getLongueur() const
{
    return mLongueur;
}

QString Colis::getNom() const
{
    return mNom;
}

QString Colis::getPays() const
{
    return mPays;
}

int Colis::getPoids() const
{
    return mPoids;
}

int Colis::getType() const
{
    return mType;
}
