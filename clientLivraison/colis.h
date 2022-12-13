#ifndef COLIS_H
#define COLIS_H

#include <QObject>
#include <QWidget>
#include <QUuid>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

class Colis
{
public:
    Colis(int, int, int, QString, QString, int, int);
    Colis(QByteArray);
    QByteArray toJson();

    QString getID() const;
    int getHauteur() const;
    int getLargeur() const;
    int getLongueur() const;
    QString getNom() const;
    QString getPays() const;
    int getPoids() const;
    int getType() const;
protected:
    QString mID;
    int mHauteur;
    int mLargeur;
    int mLongueur;
    QString mNom;
    QString mPays;
    int mPoids;
    int mType;
};

#endif // COLIS_H
