#include "widget.h"
#include "./ui_widget.h"
#include "colis.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("serveur");

    mServer = new QTcpServer(this);
    connect(mServer,SIGNAL(newConnection()),this,SLOT(clientConnected()));
    mServer->listen(QHostAddress::Any,9090);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::clientConnected()
{
    QTcpSocket* sockClient = mServer->nextPendingConnection();
    mClients << sockClient;
    connect(sockClient,SIGNAL(readyRead()),this,SLOT(dataIsComing()));
    connect(sockClient,SIGNAL(disconnected()),this,SLOT(clientDisconnected()));
}

void Widget::clientDisconnected()
{
    QTcpSocket* sock = (QTcpSocket*)sender();
    mClients.removeAll(sock);
    sock->deleteLater();
}

void Widget::dataIsComing()
{
    QTcpSocket* sock = (QTcpSocket*)sender();
    QByteArray data = sock->readAll();
    Colis c(data);

    qDebug() << c.toString();

    QStringList destinationsCamionsList;
    bool colisAjoute=false;

    for(int i=0; i<mListCamions.size(); i++)
        destinationsCamionsList.append(mListCamions[i]->getPays());

    if(!destinationsCamionsList.contains(c.getPays()))
    {
        Camion* camion = new Camion(c.getPays(), 1000, 40000);
        camion->addColis(c);
        mListCamions.append(camion);
        miseAJourFenetre(camion->getPays(), camion->getPoids(), camion->getVolume(), c);
    }else{
        for(int i=0; i<mListCamions.size(); i++)
        {
            if(mListCamions[i]->getPays() == c.getPays())
            {
                colisAjoute = mListCamions[i]->addColis(c);
                miseAJourFenetre(mListCamions[i]->getPays(), mListCamions[i]->getPoids(), mListCamions[i]->getVolume(), c);
                if(!colisAjoute)
                {
                    qDebug() << "camion plein gerer le bordereau du camion";
                    envoiCamion(mListCamions[i]);
                }
            }
        }
    }

    qDebug() << "Nombre de camions:" << mListCamions.size();

    qDebug() << "----------";

    for(int i=0; i<mListCamions.size(); i++)
    {
        qDebug() << "-------------";
        qDebug() << mListCamions[i]->toString();
    }
}

void Widget::envoiCamion(Camion* ptrCamion)
{

}

void Widget::miseAJourFenetre(QString pays, float poids, float volume, Colis c)
{
    if(pays=="Allemagne")
    {
        int nbRows = ui->tableWidgetAllemagne->rowCount();
        ui->tableWidgetAllemagne->setRowCount(nbRows+1);
        ui->tableWidgetAllemagne->setCellWidget(nbRows, 0, new QLabel(c.getNom()));
        ui->tableWidgetAllemagne->setCellWidget(nbRows, 1, new QLabel(c.getType()));
        ui->tableWidgetAllemagne->setCellWidget(nbRows, 2, new QLabel(QString::number(c.getPoids(), 'f', 2)));
        ui->lineEditPoidsCamionAllemagne->setText(QString::number(poids, 'f', 2));
        ui->lineEditVolumeCamionAllemagne->setText(QString::number(volume, 'f', 2));
    } else if(pays=="Espagne"){
        int nbRows = ui->tableWidgetEspagne->rowCount();
        ui->tableWidgetEspagne->setRowCount(nbRows+1);
        ui->tableWidgetEspagne->setCellWidget(nbRows, 0, new QLabel(c.getNom()));
        ui->tableWidgetEspagne->setCellWidget(nbRows, 1, new QLabel(c.getType()));
        ui->tableWidgetEspagne->setCellWidget(nbRows, 2, new QLabel(QString::number(c.getPoids(), 'f', 2)));
        ui->lineEditPoidsCamionEspagne->setText(QString::number(poids, 'f', 2));
        ui->lineEditVolumeCamionEspagne->setText(QString::number(volume, 'f', 2));
    } else {
        int nbRows = ui->tableWidgetFrance->rowCount();
        ui->tableWidgetFrance->setRowCount(nbRows+1);
        ui->tableWidgetFrance->setCellWidget(nbRows, 0, new QLabel(c.getNom()));
        ui->tableWidgetFrance->setCellWidget(nbRows, 1, new QLabel(c.getType()));
        ui->tableWidgetFrance->setCellWidget(nbRows, 2, new QLabel(QString::number(c.getPoids(), 'f', 2)));
        ui->lineEditPoidsCamionFrance->setText(QString::number(poids, 'f', 2));
        ui->lineEditVolumeCamionFrance->setText(QString::number(volume, 'f', 2));
    }
}

