#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include "dbmanager.h"

DbManager::DbManager()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("../serveurLivraison_libColisStatique/Livraison.db");

    if (!m_db.open())
    {
        qDebug() << "Erreur: échec de la connexion avec la Base de Données";
    }
    else
    {
        qDebug() << "Base de Données: connexion ok";
        QSqlQuery query(m_db);
        query.exec("PRAGMA foreign_keys = ON;");
    }
}

DbManager::~DbManager()
{
    if (m_db.isOpen())
    {
        m_db.close();
    }
}

bool DbManager::isOpen() const
{
    return m_db.isOpen();
}

bool DbManager::createTable(QString tableName)
{
    bool success = false;

    QSqlQuery query;
    QString queryString;
    if (tableName == "tableColis")
        queryString = QString("CREATE TABLE %1 (IdColis TEXT PRIMARY KEY, IdCamion TEXT NOT NULL, "
                              "Nom TEXT, Pays TEXT, Type TEXT, Hauteur FLOAT, Largeur FLOAT, "
                              "Longueur FLOAT, Poids FLOAT, "
                              "FOREIGN KEY (IdCamion) REFERENCES tableCamion(Id));").arg(tableName);
    if (tableName == "tableCamion")
        queryString = QString("CREATE TABLE %1 (Id TEXT PRIMARY KEY, Pays TEXT, Poids FLOAT, "
                              "Poids_max FLOAT, Volume FLOAT, Volume_max FLOAT);").arg(tableName);
    query.prepare(queryString);

    if (!query.exec())
    {
        qDebug() << QString("La table %1 n'a pas été créée: elle existe déjà.").arg(tableName);
        success = false;
    }
    else
        success = true;
    return success;
}

bool DbManager::addColis(Colis* ptrC, QString idCamion)
{
    bool success = false;
    if (!colisExists(ptrC->getID()))
    {
        QSqlQuery queryAdd;
        QString queryString;
        queryString = QString("INSERT INTO tableColis (IdColis, IdCamion, Nom, Pays, Type, Hauteur, Largeur, Longueur, Poids) "
                              "VALUES (:idColis, :idCamion, :nom, :pays, :type, :hauteur, :largeur, :longueur, :poids)");
        queryAdd.prepare(queryString);
        queryAdd.bindValue(":idColis", ptrC->getID());
        queryAdd.bindValue(":idCamion", idCamion);
        queryAdd.bindValue(":nom", ptrC->getNom());
        queryAdd.bindValue(":pays", ptrC->getPays());
        queryAdd.bindValue(":type", ptrC->getType());
        queryAdd.bindValue(":hauteur", ptrC->getHauteur());
        queryAdd.bindValue(":largeur", ptrC->getLargeur());
        queryAdd.bindValue(":longueur", ptrC->getLongueur());
        queryAdd.bindValue(":poids", ptrC->getPoids());

        if (queryAdd.exec())
        {
            success = true;

        }
        else
        {
            qDebug() << "Echec de l'ajout du colis: " << queryAdd.lastError();
        }
    }
    else
    {
        qDebug() << "Le colis existe déjà dans la table tableColis.";
    }
    return success;
}

bool DbManager::removeColis(const QString &id)
{
    bool success = false;

    if (colisExists(id))
    {
        QSqlQuery queryDelete;
        queryDelete.prepare("DELETE FROM tableColis WHERE IdColis = (:id)");
        queryDelete.bindValue(":id", id);
        success = queryDelete.exec();

        if (!success)
            qDebug() << "Echec de la suppression du colis: " << queryDelete.lastError();
    }
    else
        qDebug() << "Echec de la suppression du colis: le colis n'existe pas.";

    return success;
}

bool DbManager::colisExists(const QString& id) const
{
    bool exists = false;

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT IdColis FROM tableColis WHERE IdColis = (:id)");
    checkQuery.bindValue(":id", id);

    if (checkQuery.exec())
    {
        if (checkQuery.next())
        {
            exists = true;
        }
    }
    else
    {
        qDebug() << "Echec de la vérification du colis: " << checkQuery.lastError();
    }

    return exists;
}

void DbManager::printColis(const QString& id) const
{
    if (colisExists(id))
    {
        QSqlQuery printQuery;
        printQuery.prepare("SELECT * FROM tableColis WHERE IdColis = (:id)");
        printQuery.bindValue(":id", id);
        printQuery.exec();

        while (printQuery.next())
        {
            QString IdColis = printQuery.value(0).toString();
            QString IdCamion = printQuery.value(1).toString();
            QString nom = printQuery.value(2).toString();
            QString pays = printQuery.value(3).toString();
            QString type = printQuery.value(4).toString();
            float hauteur = printQuery.value(5).toFloat();
            float largeur = printQuery.value(6).toFloat();
            float longueur = printQuery.value(7).toFloat();
            float poids = printQuery.value(8).toFloat();
            qDebug() << "ID Colis:" << IdColis << "ID Camion:" << IdCamion << ", nom:"
                     << nom << ", pays:" << pays << ", type:" << type << ", hauteur:"
                     << hauteur << ", largeur:" << largeur << ", longueur:"
                     << longueur << ", poids:" << poids;
        }
    }
    else
    {
        qDebug() << "Echec d'impression: le colis n'existe pas.";
    }
}

bool DbManager::addCamion(Camion* ptrCA)
{
    bool success = false;
    if (!camionExists(ptrCA->getID()))
    {
        QSqlQuery queryAdd;
        QString queryString;
        queryString = QString("INSERT INTO tableCamion (Id, Pays, Poids, Poids_max, Volume, Volume_max) "
                              "VALUES (:id, :pays, :poids, :poids_max, :volume, :volume_max)");
        queryAdd.prepare(queryString);
        queryAdd.bindValue(":id", ptrCA->getID());
        queryAdd.bindValue(":pays", ptrCA->getPays());
        queryAdd.bindValue(":poids", ptrCA->getPoids());
        queryAdd.bindValue(":poids_max", ptrCA->getPoidsMax());
        queryAdd.bindValue(":volume", ptrCA->getVolume());
        queryAdd.bindValue(":volume_max", ptrCA->getVolumeMax());

        if (queryAdd.exec())
        {
            success = true;
        }
        else
        {
            qDebug() << "Echec de l'ajout du camion: " << queryAdd.lastError();
        }
    }
    else
    {
        qDebug() << "Le camion existe déjà dans la table tableCamion.";
    }
    return success;
}

bool DbManager::removeCamion(const QString &id)
{
    bool success = false;

    if (camionExists(id))
    {
        QSqlQuery queryDelete;
        queryDelete.prepare("DELETE FROM tableCamion WHERE Id = (:id)");
        queryDelete.bindValue(":id", id);
        success = queryDelete.exec();

        if (!success)
            qDebug() << "Echec de la suppression du camion: " << queryDelete.lastError();
    }
    else
        qDebug() << "Echec de la suppression du camion: le camion n'existe pas.";

    return success;
}

bool DbManager::camionExists(const QString& id) const
{
    bool exists = false;

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT Id FROM tableCamion WHERE Id = (:id)");
    checkQuery.bindValue(":id", id);

    if (checkQuery.exec())
    {
        if (checkQuery.next())
        {
            exists = true;
        }
    }
    else
    {
        qDebug() << "Echec de la vérification du camion: " << checkQuery.lastError();
    }

    return exists;
}

void DbManager::printCamion(const QString &id) const
{
    if (camionExists(id))
    {
        QSqlQuery printQuery;
        printQuery.prepare("SELECT * FROM tableCamion WHERE Id = (:id)");
        printQuery.bindValue(":id", id);
        printQuery.exec();

        while (printQuery.next())
        {
            QString ID = printQuery.value(0).toString();
            QString pays = printQuery.value(1).toString();
            float poids = printQuery.value(2).toFloat();
            float poidsMax = printQuery.value(3).toFloat();
            float volume = printQuery.value(4).toFloat();
            float volumeMax = printQuery.value(5).toFloat();
            qDebug() << "ID:" << ID << ", pays:" << pays <<
                        ", poids:" << poids << ", poids max:"
                     << poidsMax << ", volume:" << volume
                     << ", volume max:" << volumeMax ;
        }
    }
    else
    {
        qDebug() << "Echec d'impression: le camion n'existe pas.";
    }
}

bool DbManager::updatePoidsCamion(const QString &id, float poids) const
{
    bool update = false;

    if (camionExists(id))
    {
        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE tableCamion SET Poids = (:poids) WHERE Id = (:id)");
        updateQuery.bindValue(":id", id);
        updateQuery.bindValue(":poids", poids);

        if (updateQuery.exec())
        {
            update = true;
        }
        else
        {
            qDebug() << "Echec de la mise à jour du poids du camion: " << updateQuery.lastError();
        }
    }
    else
    {
        qDebug() << "Echec de la mise à jour du poids: le camion n'existe pas.";
    }
    return update;
}

bool DbManager::updateVolumeCamion(const QString &id, float volume) const
{
    bool update = false;

    if (camionExists(id))
    {
        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE tableCamion SET Volume = (:volume) WHERE Id = (:id)");
        updateQuery.bindValue(":id", id);
        updateQuery.bindValue(":volume", volume);

        if (updateQuery.exec())
        {
            update = true;
        }
        else
        {
            qDebug() << "Echec de la mise à jour du volume du camion: " << updateQuery.lastError();
        }
    }
    else
    {
        qDebug() << "Echec de la mise à jour du volume: le camion n'existe pas.";
    }
    return update;
}

