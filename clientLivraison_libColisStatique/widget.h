#ifndef WIDGET_H
#define WIDGET_H

#include <QRandomGenerator>
#include <QTcpSocket>
#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

/**
 * @class Widget
 * @brief Widget affiche une fenêtre
 */
class Widget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructeur de la classe Widget
     * @param parent: pointeur null
     */
    Widget(QWidget *parent = nullptr);

    /**
     * Destructeur de la classe Widget
     */
    ~Widget();

private slots:
    /**
     * @brief envoisColis
     * Cette méthode permet d'envoyer un colis
     * au serveur.
     */
    void envoisColis();

    /**
     * @brief Connected
     * Cette méthode permet d'activer le bouton
     * Envoyer lorsque le client est connecté.
     */
    void Connected();

    /**
     * @brief Widget::Disconnected
     * Cette méthode permet de désactiver le bouton
     * Envoyer lorsque le client est déconnecté.
     */
    void Disconnected();

private:
    Ui::Widget *ui; //Pointeur d'un objet de la classe Widget
    QTcpSocket* mSock; //Pointeur du client TCP
};
#endif // WIDGET_H
