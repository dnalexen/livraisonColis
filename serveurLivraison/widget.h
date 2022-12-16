#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QPdfWriter>
#include <QPainter>
#include "camion.h"
#include "colis.h"
#include "dbmanager.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

/**
 * @brief La classe Widget
 */
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void clientConnected();
    void clientDisconnected();
    void dataIsComing();
    void envoiCamion(Camion*);
    void miseAJourFenetre(QString, float, float, Colis);
private:
    Ui::Widget *ui;
    QTcpServer* mServer;
    QList<QTcpSocket*> mClients;
    QList<Camion*> mListCamions;
    DbManager* mDB = new DbManager();
};
#endif // WIDGET_H
