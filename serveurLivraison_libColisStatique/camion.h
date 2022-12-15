#ifndef CAMION_H
#define CAMION_H

#include <QObject>
#include <QUuid>
#include <QList>
#include "ColisStatique.h"

/**
 * @brief La classe Camion
 */
class Camion
{
public:
    Camion(QString, float, float);

    QString getID() const;
    QList<Colis> getColisList() const;
    QString getPays() const;
    float getPoids() const;
    float getPoidsMax() const;
    float getVolume() const;
    float getVolumeMax() const;

    bool addColis(Colis&);
    QString toString();

protected:
    QString mID;
    QList<Colis> mColisList;
    QString mPays;
    float mPoids;
    float mPoidsMax;
    float mVolume;
    float mVolumeMax;
};

#endif // CAMION_H
