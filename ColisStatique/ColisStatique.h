#ifndef COLIS_H
#define COLIS_H

#include <QObject>
#include <QWidget>
#include <QUuid>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QRandomGenerator>

/**
 * @class Colis
 * @brief La classe Colis crée un colis et
 * donne des informations sur ce colis.
 */
class Colis
{
public:
    /**
     * @brief Colis
     * Ce constructeur de la classe Colis
     * permet de créer un colis.
     * @param hauteur: hauteur du colis
     * @param largeur: largeur du colis
     * @param longueur: longeur du colis
     * @param nom: nom du destinataire
     * @param pays: pays de destination
     * @param type: type d'emballage du colis
     */
    Colis(float hauteur=0, float largeur=0,
          float longueur=0, QString nom=0,
          QString pays="", QString type="Petit");

    /**
     * @brief Colis
     * Constructeur par copie de la classe
     * Colis qui prend en paramètre un json
     * QByteArray qui contient les paramètres du colis
     * à créer.
     * @param colisByteArray
     */
    Colis(QByteArray&);

    /**
     * @brief ~Colis
     * Desctructeur de la classe Colis
     */
    ~Colis();

    /**
     * @brief getID
     * Cette méthode retourne l'ID du colis.
     * @return QString
     */
    QString getID() const;

    /**
     * @brief getHauteur
     * Cette méthode retourne la hauteur du colis.
     * @return float
     */
    float getHauteur() const;

    /**
     * @brief getLargeur
     * Cette méthode retourne la largeur du colis.
     * @return float
     */
    float getLargeur() const;

    /**
     * @brief getLongueur
     * Cette méthode retourne la longueur du colis.
     * @return float
     */
    float getLongueur() const;

    /**
     * @brief getNom
     * Cette méthode retourne le nom du destinataire
     * du colis.
     * @return QString
     */
    QString getNom() const;

    /**
     * @brief getPays
     * Cette méthode retourne le pays de
     * destination du colis.
     * @return QString
     */
    QString getPays() const;

    /**
     * @brief getPoids
     * Cette méthode retourne le poids du colis.
     * @return float
     */
    float getPoids() const;

    /**
     * @brief getType
     * Cette méthode retourne le type d'emballage
     * du colis.
     * @return QString
     */
    QString getType() const;

    /**
     * @brief toJson
     * Cette méthode retourne un json au format
     * QByteArray qui contient les attributs
     * d'un objet de la classe Colis.
     * @return QByteArray
     */
    QByteArray toJson();

    /**
     * @brief toString
     * Cette méthode retourne toutes les informations
     * du colis.
     * @return QString
     */
    QString toString();

    /**
     * @brief operator %
     * Cette méthode surcharge l'opérateur % et
     * permet de connaitre la somme des poids
     * de deux colis.
     * @param c: objet Colis
     * @return float
     */
    float operator%(const Colis)const;

    /**
     * @brief operator$
     * Cette méthode surcharge l'opérateur $ et
     * permet de connaitre la somme des volumes
     * de deux colis.
     * @param c: objet Colis
     * @return float
     */
    float operator$(const Colis)const;

protected:
    QString mID; //Id du colis
    float mHauteur; //Hauteur du colis en mètre
    float mLargeur; //Largeur du colis en mètre
    float mLongueur; //Longueur du colis en mètre
    QString mNom; //Nom du destinataire du colis
    QString mPays; //Pays de destination du colis
    float mPoids; //Poids du colis en kg
    QString mType; //Type du colis (Petit / Moyen / Grand)
};

#endif // COLIS_H
