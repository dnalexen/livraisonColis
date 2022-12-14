#ifndef CAMION_H
#define CAMION_H

#include <QObject>
#include <QUuid>
#include <QMap>
#include "colis.h"

class Camion
{
public:
    Camion(QString, QString, int, int);

    QString getID() const;
    QMap<QString, Colis> getColisMap() const;
    QString getPays() const;
    float getPoids() const;
    int getPoidsMax() const;
    int getVolume() const;
    int getVolumeMax() const;

    bool addColis(Colis);

protected:
    QString mID;
    QMap<QString, Colis> mColisMap;
    QString mPays;
    float mPoids;
    int mPoidsMax;
    int mVolume;
    int mVolumeMax;
};

#endif // CAMION_H
