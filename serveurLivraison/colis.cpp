#include "colis.h"
/**
 * @brief Colis::Colis
 * @param hauteur
 * @param largeur
 * @param longueur
 * @param nom
 * @param pays
 * @param poids
 * @param type
 */
Colis::Colis(float hauteur, float largeur,
             float longueur, QString nom,
             QString pays, float poids,
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

/**
 * @brief Colis::Colis
 * @param colisByteArray
 */
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

/**
 * @brief Colis::~Colis
 */
Colis::~Colis()
{

}

/**
 * @brief Colis::toJson
 * @return
 */
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

/**
 * @brief Colis::getID
 * @return
 */
QString Colis::getID() const
{
    return mID;
}

/**
 * @brief Colis::getHauteur
 * @return
 */
float Colis::getHauteur() const
{
    return mHauteur;
}

/**
 * @brief Colis::getLargeur
 * @return
 */
float Colis::getLargeur() const
{
    return mLargeur;
}

/**
 * @brief Colis::getLongueur
 * @return
 */
float Colis::getLongueur() const
{
    return mLongueur;
}

/**
 * @brief Colis::getNom
 * @return
 */
QString Colis::getNom() const
{
    return mNom;
}

/**
 * @brief Colis::getPays
 * @return
 */
QString Colis::getPays() const
{
    return mPays;
}

/**
 * @brief Colis::getPoids
 * @return
 */
float Colis::getPoids() const
{
    return mPoids;
}

/**
 * @brief Colis::getType
 * @return
 */
QString Colis::getType() const
{
    return mType;
}

/**
 * @brief Colis::toString
 * @return
 */
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

/**
 * @brief Colis::operator %
 * @param c
 * @return
 */
float Colis::operator%(const Colis c) const
{
    return mPoids + c.mPoids;
}

/**
 * @brief Colis::operator$
 * @param c
 * @return
 */
float Colis::operator$(const Colis c) const
{
    return mHauteur*mLargeur*mLongueur + c.mHauteur*c.mLargeur*c.mLongueur;
}
