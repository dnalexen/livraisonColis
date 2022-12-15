#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QSqlDatabase>
#include "colis.h"
#include "camion.h"

/**
 * \class DbManager
 *
 * \brief SQL Database Manager class
 *
 * DbManager sets up the connection with SQL database
 * and performs some basics queries. The class requires
 * existing SQL database. You can create it with sqlite:
 */
class DbManager
{
public:
    /**
     * @brief Constructor
     *
     * Constructor sets up connection with db and opens it
     * @param path - absolute path to db file
     */
    DbManager(const QString& path);

    /**
     * @brief Destructor
     *
     * Close the db connection
     */
    ~DbManager();

    bool isOpen() const;

    /**
     * @brief Creates a new table if it doesn't already exist
     * @return true - the table has been created successfully, false - the table has not been created
     */
    bool createTable(QString tableName);

    /**
     * @brief Ajoute un colis à la table tableColis de la base de données Livraison
     * @param colis - objet de la classe Colis
     * @return true - colis ajouté, false - colis pas ajouté
     */
    bool addColis(const Colis& colis);

    /**
     * @brief Supprime un colis de la table tableColis de la base de données Livraison
     * @param colis - objet de la classe Colis
     * @return true - colis supprimé, false - colis pas supprimé
     */
    bool removeColis(const Colis& colis);

    /**
     * @brief Vérifie si le colis existe dans la table tableColis de la base de données Livraison
     * @param colis - objet de la classe Colis
     * @return true - colis existe, false - colis n'existe pas
     */
    bool colisExists(const Colis& colis) const;

    /**
     * @brief Ajoute un camion à la table tableCamion de la base de données Livraison
     * @param camion - objet de la classe Camion
     * @return true - camion ajouté, false - camion pas ajouté
     */
    bool addCamion(const Camion& camion);

    /**
     * @brief Supprime un camion de la table tableCamion de la base de données Livraison
     * @param camion - objet de la classe Camion
     * @return true - camion supprimé, false - camion pas supprimé
     */
    bool removeCamion(const Camion& camion);

    /**
     * @brief Vérifie si le camion existe dans la table tableCamion de la base de données Livraison
     * @param camion - objet de la classe Camion
     * @return true - camion existe, false - camion n'existe pas
     */
    bool camionExists(const Camion& camion) const;

private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
