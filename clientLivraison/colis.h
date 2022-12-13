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
    Colis(int, int, int, QString, QString, int, QChar);
    Colis(QByteArray);
    QByteArray toJson();

    QString getID() const;
    int getHauteur() const;
    int getLargeur() const;
    int getLongueur() const;
    QString getNom() const;
    QString getPays() const;
    int getPoids() const;
    QChar getType() const;
    void info();
protected:
    QString mID;
    int mHauteur;
    int mLargeur;
    int mLongueur;
    QString mNom;
    QString mPays;
    int mPoids;
    QChar mType;
};

#endif // COLIS_H
