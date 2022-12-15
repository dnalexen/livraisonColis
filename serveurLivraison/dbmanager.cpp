#include "dbmanager.h"

DbManager::DbManager(const QString& path)
{

}

DbManager::~DbManager()
{

}

bool DbManager::createTable(QString tableName)
{
    return false;
}

bool DbManager::addColis(const Colis &colis)
{
    return false;
}

bool DbManager::removeColis(const Colis &colis)
{
    return false;
}

bool DbManager::colisExists(const Colis &colis) const
{
    return false;
}

bool DbManager::addCamion(const Camion &camion)
{
    return false;
}

bool DbManager::removeCamion(const Camion &camion)
{
    return false;
}

bool DbManager::camionExists(const Camion &camion) const
{
    return false;
}

