#include "ColisStatique.h"
/**
 * @brief Colis::Colis
 * Ce constructeur de la classe Colis
 * permet de créer un colis.
 * @param hauteur: hauteur du colis
 * @param largeur: largeur du colis
 * @param longueur: longeur du colis
 * @param nom: nom du destinataire
 * @param pays: pays de destination
 * @param type: type d'emballage du colis
 */
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

/**
 * @brief Colis::Colis
 * Constructeur par copie de la classe
 * Colis qui prend en paramètre un json
 * QByteArray qui contient les paramètres du colis
 * à créer.
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
 * Desctructeur de la classe Colis
 */
Colis::~Colis()
{

}

/**
 * @brief Colis::toJson
 * Cette méthode retourne un json au format
 * QByteArray qui contient les attributs
 * d'un objet de la classe Colis.
 * @return QByteArray
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
 * Cette méthode retourne l'ID du colis.
 * @return QString
 */
QString Colis::getID() const
{
    return mID;
}

/**
 * @brief Colis::getHauteur
 * Cette méthode retourne la hauteur du colis.
 * @return float
 */
float Colis::getHauteur() const
{
    return mHauteur;
}

/**
 * @brief Colis::getLargeur
 * Cette méthode retourne la largeur du colis.
 * @return float
 */
float Colis::getLargeur() const
{
    return mLargeur;
}

/**
 * @brief Colis::getLongueur
 * Cette méthode retourne la longueur du colis.
 * @return float
 */
float Colis::getLongueur() const
{
    return mLongueur;
}

/**
 * @brief Colis::getNom
 * Cette méthode retourne le nom du destinataire
 * du colis.
 * @return QString
 */
QString Colis::getNom() const
{
    return mNom;
}

/**
 * @brief Colis::getPays
 * Cette méthode retourne le pays de
 * destination du colis.
 * @return QString
 */
QString Colis::getPays() const
{
    return mPays;
}

/**
 * @brief Colis::getPoids
 * Cette méthode retourne le poids du colis.
 * @return float
 */
float Colis::getPoids() const
{
    return mPoids;
}

/**
 * @brief Colis::getType
 * Cette méthode retourne le type d'emballage
 * du colis.
 * @return QString
 */
QString Colis::getType() const
{
    return mType;
}

/**
 * @brief Colis::toString
 * Cette méthode retourne toutes les informations
 * du colis.
 * @return QString
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
 * Cette méthode surcharge l'opérateur % et
 * permet de connaitre la somme des poids
 * de deux colis.
 * @param c: objet Colis
 * @return float
 */
float Colis::operator%(const Colis c) const
{
    return mPoids + c.mPoids;
}

/**
 * @brief Colis::operator$
 * Cette méthode surcharge l'opérateur $ et
 * permet de connaitre la somme des volumes
 * de deux colis.
 * @param c: objet Colis
 * @return float
 */
float Colis::operator$(const Colis c) const
{
    return mHauteur*mLargeur*mLongueur + c.mHauteur*c.mLargeur*c.mLongueur;
}
