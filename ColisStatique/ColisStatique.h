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
 * @brief La classe Colis
 */
class Colis
{
public:
    Colis(float hauteur=0, float largeur=0,
          float longueur=0, QString nom=0,
          QString pays="", QString type="A");
    Colis(QByteArray&);
    ~Colis();

    QString getID() const;
    float getHauteur() const;
    float getLargeur() const;
    float getLongueur() const;
    QString getNom() const;
    QString getPays() const;
    float getPoids() const;
    QString getType() const;

    QByteArray toJson();
    QString toString();

    float operator%(const Colis)const;
    float operator$(const Colis)const;

protected:
    QString mID;
    float mHauteur;
    float mLargeur;
    float mLongueur;
    QString mNom;
    QString mPays;
    float mPoids;
    QString mType;
};

#endif // COLIS_H
