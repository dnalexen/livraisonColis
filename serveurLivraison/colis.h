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
    Colis(int, int, int, QString, QString, float, QString);
    Colis(QByteArray);
    ~Colis();

    QString getID() const;
    int getHauteur() const;
    int getLargeur() const;
    int getLongueur() const;
    QString getNom() const;
    QString getPays() const;
    float getPoids() const;
    QString getType() const;

    QByteArray toJson();    
    void info();
protected:
    QString mID;
    int mHauteur;
    int mLargeur;
    int mLongueur;
    QString mNom;
    QString mPays;
    float mPoids;
    QString mType;
};

#endif // COLIS_H
