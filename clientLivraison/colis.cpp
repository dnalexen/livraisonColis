#include "colis.h"

Colis::Colis(int hauteur, int largeur,
             int longueur, QString nom,
             QString pays, int poids,
             QString type)
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

Colis::~Colis()
{

}

QByteArray Colis::toJson()
{
    QJsonObject colisObject;

    colisObject["ID"] = mID;
    colisObject["nom"] = mNom;
    colisObject["pays"] = mPays;
    colisObject["type"] = mType;
    colisObject["hauteur"] = mHauteur;
    colisObject["largeur"] = mLargeur;
    colisObject["longueur"] =  mLongueur;
    colisObject["poids"] = mPoids;

    QJsonDocument colisDocument(colisObject);

    QByteArray colisByteArray = colisDocument.toJson(QJsonDocument::Compact);

    return colisByteArray;
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

QString Colis::getType() const
{
    return mType;
}

void Colis::info()
{
    qDebug() << "ID: " << getID() << "\nNom: " << getNom() << "\nPays: "
             << getPays() << "\nType: " << getType() << "\nHauteur: "
             << getHauteur() << "\nLargeur: " << getLargeur()
             << "\nLongueur: " << getLongueur();
}
