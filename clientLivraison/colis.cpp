#include "colis.h"

Colis::Colis(float hauteur, float largeur,
             float longueur, QString nom,
             QString pays, QString type)
{
    mID = QUuid::createUuid().toString(QUuid::WithoutBraces);
    mHauteur = hauteur;
    mLargeur = largeur;
    mLongueur = longueur;
    mNom = nom;
    mPays = pays;
    mPoids = (float)(QRandomGenerator::global()->bounded(1, 500))/10;
    mType = type;
}

Colis::Colis(QByteArray& colisByteArray)
{
    QJsonObject colisObject = QJsonDocument::fromJson(colisByteArray).object();
    mID = colisObject["ID"].toString();
    mHauteur = colisObject["hauteur"].toString().toFloat();
    mLargeur = colisObject["largeur"].toString().toFloat();
    mLongueur = colisObject["longueur"].toString().toFloat();
    mNom = colisObject["nom"].toString();
    mPays = colisObject["pays"].toString();
    mPoids = colisObject["poids"].toString().toFloat();
    mType = colisObject["type"].toString();
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
    colisObject["hauteur"] = QString::number(mHauteur, 'f', 1);
    colisObject["largeur"] = QString::number(mLargeur, 'f', 1);
    colisObject["longueur"] =  QString::number(mLongueur, 'f', 1);
    colisObject["poids"] = QString::number(mPoids, 'f', 1);

    QJsonDocument colisDocument(colisObject);

    QByteArray colisByteArray = colisDocument.toJson(QJsonDocument::Compact);

    return colisByteArray;
}

QString Colis::getID() const
{
    return mID;
}

float Colis::getHauteur() const
{
    return mHauteur;
}

float Colis::getLargeur() const
{
    return mLargeur;
}

float Colis::getLongueur() const
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

float Colis::getPoids() const
{
    return mPoids;
}

QString Colis::getType() const
{
    return mType;
}

QString Colis::toString()
{
    QString line;
    line += "ID:" + getID() + ";";
    line += "Nom:" + getNom() + ";";
    line += "Pays:" + getPays() + ";";
    line += "Type:" + getType() + ";";
    line += "Hauteur:" + QString::number(getHauteur()) + ";";
    line += "Largeur:" + QString::number(getLargeur()) + ";";
    line += "Longueur:" + QString::number(getLongueur()) + ";";
    line += "Poids:" + QString::number(getPoids());

    return line;
}

float Colis::operator%(const Colis c) const
{
    return mPoids + c.mPoids;
}

float Colis::operator$(const Colis c) const
{
    return mHauteur*mLargeur*mLongueur + c.mHauteur*c.mLargeur*c.mLongueur;
}
