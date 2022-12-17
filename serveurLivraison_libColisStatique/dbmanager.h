#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QSqlDatabase>
#include "ColisStatique.h"
#include "camion.h"

/**
 * \class DbManager
 *
 * \brief classe Manager de Database SQL
 *
 * DbManager établie la connexion avec une base de données (BD) SQL
 * et exécute des requètes basiques. Pour notre programme, nous
 * utilisons une BD SQLITE3 donc si la BD n'existe pas, elle est créée.
 */
class DbManager
{
public:
    /**
     * @brief Constructeur
     *
     * Etablie la connexion avec la BD Livraison et l'ouvre.
     */
    DbManager();

    /**
     * @brief Destructeur
     *
     * Ferme la connexion à la BD
     */
    ~DbManager();

    /**
     * @brief isOpen - vérifie l'état de la connexion à la BD
     * @return true - si la connexion à la BD est ouverte, false - si la connexion à la BD est fermée
     */
    bool isOpen() const;

    /**
     * @brief createTable - Crée une table si elle n'existe pas déjà
     * @param tableName - nom de la table
     * @return true - la table a été créée avec succès, false - la table n'a pas été créée
     */
    bool createTable(QString tableName);

    /**
     * @brief Ajoute un colis à la table tableColis de la base de données Livraison
     * @param ptrC - pointeur du colis
     * @return true - colis ajouté, false - colis pas ajouté
     */
    bool addColis(Colis* ptrC, QString idCamion);

    /**
     * @brief Supprime un colis de la table tableColis de la base de données Livraison
     * @param id - id du colis
     * @return true - colis supprimé, false - colis pas supprimé
     */
    bool removeColis(const QString& id);

    /**
     * @brief Vérifie si le colis existe dans la table tableColis de la base de données Livraison
     * @param id - id du colis
     * @return true - colis existe, false - colis n'existe pas
     */
    bool colisExists(const QString& id) const;

    /**
     * @brief Imprime les informations d'un colis
     * @param id - id du colis
     */
    void printColis(const QString& id) const;

    /**
     * @brief Ajoute un camion à la table tableCamion de la base de données Livraison
     * @param ptrCA - pointeur du camion
     * @return true - camion ajouté, false - camion pas ajouté
     */
    bool addCamion(Camion* ptrCA);

    /**
     * @brief Supprime un camion de la table tableCamion de la base de données Livraison
     * @param id - id du camion
     * @return true - camion supprimé, false - camion pas supprimé
     */
    bool removeCamion(const QString& id);

    /**
     * @brief Vérifie si le camion existe dans la table tableCamion de la base de données Livraison
     * @param id - id du camion
     * @return true - camion existe, false - camion n'existe pas
     */
    bool camionExists(const QString& id) const;

    /**
     * @brief Imprime les informations d'un camion dans la base de données
     * @param id - id du camion
     */
    void printCamion(const QString& id) const;

    /**
     * @brief Mettre à jour le poids d'un camion
     * @param id - id du camion
     * @param poids - poids du camion
     * @return true - poids mis à jour, false - poids pas mis à jour
     */
    bool updatePoidsCamion(const QString& id, float poids) const;

    /**
     * @brief Mettre à jour le volume d'un camion
     * @param id - id du camion
     * @param volume - volume du camion
     * @return true - volume mis à jour, false - volume pas mis à jour
     */
    bool updateVolumeCamion(const QString& id, float volume) const;

private:
    QSqlDatabase m_db; //Connexion à la Base de Données
};

#endif // DBMANAGER_H
