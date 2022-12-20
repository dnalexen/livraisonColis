#include "widget.h"
#include "./ui_widget.h"

#define POIDS_MAX 500
#define VOLUME_MAX 40000

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("Serveur"); //Nommage de la fenêtre serveur

    //Entête colonnes tables
    QStringList listEntetes = {"Nom", "Type", "Poids(kg)"};
    ui->tableWidgetAllemagne->setHorizontalHeaderLabels(listEntetes);
    ui->tableWidgetFrance->setHorizontalHeaderLabels(listEntetes);
    ui->tableWidgetEspagne->setHorizontalHeaderLabels(listEntetes);

    //Etablissement du serveur TCP
    mServer = new QTcpServer(this);
    connect(mServer,SIGNAL(newConnection()),this,SLOT(clientConnected()));
    mServer->listen(QHostAddress::Any,9090);

    //Création des tables tableCamion et tableColis dans la BD Livraison
    mDB->createTable("tableCamion");
    mDB->createTable("tableColis");
}

Widget::~Widget()
{
    delete mServer;
    delete ui;

    for(int i=0; i<mListCamions.size(); i++)
        delete mListCamions[i];

    delete mDB;
}

void Widget::clientConnected()
{
    QTcpSocket* sockClient = mServer->nextPendingConnection();
    mClients << sockClient;
    connect(sockClient,SIGNAL(readyRead()),this,SLOT(colisArrive()));
    connect(sockClient,SIGNAL(disconnected()),this,SLOT(clientDisconnected()));
}

void Widget::clientDisconnected()
{
    QTcpSocket* sock = (QTcpSocket*)sender();
    mClients.removeAll(sock);
    sock->deleteLater();
}

void Widget::colisArrive()
{
    //Lecture des données transférées par le client
    QTcpSocket* sock = (QTcpSocket*)sender();
    QByteArray data = sock->readAll();
    Colis c(data);

    //Liste des destinations actuelles
    QStringList destinationsCamionsList;
    bool succesAjoutColis=false;
    for(int i=0; i<mListCamions.size(); i++)
        destinationsCamionsList.append(mListCamions[i]->getPays());

    //Création du camion - Ajout du colis
    if(!destinationsCamionsList.contains(c.getPays()))
    {
        Camion* ptrCamion = new Camion(c.getPays(), POIDS_MAX, VOLUME_MAX);
        mDB->addCamion(ptrCamion);
        succesAjoutColis = ptrCamion->addColis(c);
        if(succesAjoutColis)
        {
            mDB->addColis(&c, ptrCamion->getID());
            mDB->updatePoidsCamion(ptrCamion->getID(), ptrCamion->getPoids());
            mDB->updateVolumeCamion(ptrCamion->getID(), ptrCamion->getVolume());
            miseAJourFenetre(ptrCamion->getPays(), ptrCamion->getPoids(), ptrCamion->getVolume(), c);
        }
        mListCamions.append(ptrCamion);
    }
    else
    {
        for(int i=0; i<mListCamions.size(); i++)
        {
            if(mListCamions[i]->getPays() == c.getPays())
            {
                succesAjoutColis = mListCamions[i]->addColis(c);
                if(succesAjoutColis)
                {
                    mDB->addColis(&c, mListCamions[i]->getID());
                    mDB->updatePoidsCamion(mListCamions[i]->getID(), mListCamions[i]->getPoids());
                    mDB->updateVolumeCamion(mListCamions[i]->getID(), mListCamions[i]->getVolume());
                    miseAJourFenetre(mListCamions[i]->getPays(), mListCamions[i]->getPoids(), mListCamions[i]->getVolume(), c);
                }
                if(!succesAjoutColis)
                {
                    envoiCamion(mListCamions[i]);
                    if(mListCamions[i]->getPays() == "Allemagne")
                    {
                        ui->tableWidgetAllemagne->clear();
                        ui->tableWidgetAllemagne->setRowCount(0);
                        ui->tableWidgetAllemagne->setHorizontalHeaderLabels(QStringList{"Nom", "Type", "Poids(kg)"});
                        ui->lineEditPoidsCamionAllemagne->setText("0");
                        ui->lineEditVolumeCamionAllemagne->setText("0");                        
                    }
                    else if(mListCamions[i]->getPays() == "Espagne")
                    {
                        ui->tableWidgetEspagne->clear();
                        ui->tableWidgetEspagne->setRowCount(0);
                        ui->tableWidgetEspagne->setHorizontalHeaderLabels(QStringList{"Nom", "Type", "Poids(kg)"});
                        ui->lineEditPoidsCamionEspagne->setText("0");
                        ui->lineEditVolumeCamionEspagne->setText("0");                        
                    }
                    else if(mListCamions[i]->getPays() == "France")
                    {
                        ui->tableWidgetFrance->clear();
                        ui->tableWidgetFrance->setRowCount(0);
                        ui->tableWidgetFrance->setHorizontalHeaderLabels(QStringList{"Nom", "Type", "Poids(kg)"});
                        ui->lineEditPoidsCamionFrance->setText("0");
                        ui->lineEditVolumeCamionFrance->setText("0");                        
                    }
                    mListCamions.removeAt(i);
                    Camion* ptrCamion = new Camion(c.getPays(), POIDS_MAX, VOLUME_MAX);
                    mDB->addCamion(ptrCamion);
                    succesAjoutColis = ptrCamion->addColis(c);
                    if(succesAjoutColis)
                    {
                        mDB->addColis(&c, ptrCamion->getID());
                        mDB->updatePoidsCamion(ptrCamion->getID(), ptrCamion->getPoids());
                        mDB->updateVolumeCamion(ptrCamion->getID(), ptrCamion->getVolume());
                        miseAJourFenetre(ptrCamion->getPays(), ptrCamion->getPoids(), ptrCamion->getVolume(), c);
                    }
                    mListCamions.append(ptrCamion);
                }
                break;
            }
        }
    }
}

void Widget::envoiCamion(Camion* ptrCamion)
{
    //Création du dossier bordereauxTransport
    if(!QDir("../serveurLivraison_libColisStatique/bordereauxTransport").exists())
        QDir().mkdir("../serveurLivraison_libColisStatique/bordereauxTransport");

    //Génération du bordereau de transport au format .txt
    QString filename = "../serveurLivraison_libColisStatique/bordereauxTransport/" + ptrCamion->getID();
    QFile file(filename + ".txt");
    if(!file.open(QFile::WriteOnly |
                      QFile::Text))
    {
        qDebug() << "Impossible d'ouvrir le fichier pour écriture";
        return;
    }

    QTextStream out(&file);
    out << "Bordereau de transport\n\n";
    out << "Information du camion:\n";
    out << ptrCamion->toString();
    out << "\n\nInformation des colis:\n";
    int i = 1;
    for(auto colis : ptrCamion->getColisList())
    {
        out << QString::number(i) + "- " + colis.toString() + "\n";
        i++;
    }
    file.flush();
    file.close();

    //Génération du bordereau de transport en format PDF
    QPdfWriter pdf(filename + ".pdf");
    QPainter painter(&pdf);

    painter.setPen(Qt::black);

    QFont font = painter.font();
    font.setPixelSize(250);
    painter.setFont(font);

    QString cheminImage;
    int largeurImage, hauteurImage;

    if(ptrCamion->getPays() == "Allemagne")
    {
        cheminImage = "../serveurLivraison_libColisStatique/images/allemagne.jpeg";
        largeurImage = 275;
        hauteurImage = 183;
    }
    else if(ptrCamion->getPays() == "Espagne")
    {
        cheminImage = "../serveurLivraison_libColisStatique/images/espagne.jpeg";
        largeurImage = 270;
        hauteurImage = 187;
    }
    else if(ptrCamion->getPays() == "France")
    {
        cheminImage = "../serveurLivraison_libColisStatique/images/france.jpeg";
        largeurImage = 221;
        hauteurImage = 228;
    }

    int y = 100;

    painter.drawText(100, y, "Bordereau de transport - " + ptrCamion->getPays());

    y +=300;
    painter.drawPixmap(QRect(100, y, largeurImage*4, hauteurImage*4), QPixmap(cheminImage));

    y += hauteurImage*4;
    font.setPixelSize(200);
    painter.setFont(font);
    y +=400;
    painter.drawText(100, y, "Information du camion:");

    font.setPixelSize(140);
    painter.setFont(font);
    y +=250;
    painter.drawText(100, y, ptrCamion->toString());

    font.setPixelSize(200);
    painter.setFont(font);
    y +=400;
    painter.drawText(100, y, "Information des colis:");

    font.setPixelSize(140);
    painter.setFont(font);
    i=1;
    QString line;
    for(auto colis : ptrCamion->getColisList())
    {
        y +=250;
        line = QString::number(i) + "- " + colis.toString();
        painter.drawText(100, y, line);
        i++;
    }

    painter.end();

    delete ptrCamion;
}

void Widget::miseAJourFenetre(QString pays, float poids, float volume, Colis c)
{
    if(pays=="Allemagne")
    {
        int nbRows = ui->tableWidgetAllemagne->rowCount();
        ui->tableWidgetAllemagne->setRowCount(nbRows+1);
        ui->tableWidgetAllemagne->setCellWidget(nbRows, 0, new QLabel(c.getNom()));
        ui->tableWidgetAllemagne->setCellWidget(nbRows, 1, new QLabel(c.getType()));
        ui->tableWidgetAllemagne->setCellWidget(nbRows, 2, new QLabel(QString::number(c.getPoids(), 'f', 1)));
        ui->lineEditPoidsCamionAllemagne->setText(QString::number(poids, 'f', 1) + " kg");
        ui->lineEditVolumeCamionAllemagne->setText(QString::number(volume, 'f', 1) + " m³");
    } else if(pays=="Espagne"){
        int nbRows = ui->tableWidgetEspagne->rowCount();
        ui->tableWidgetEspagne->setRowCount(nbRows+1);
        ui->tableWidgetEspagne->setCellWidget(nbRows, 0, new QLabel(c.getNom()));
        ui->tableWidgetEspagne->setCellWidget(nbRows, 1, new QLabel(c.getType()));
        ui->tableWidgetEspagne->setCellWidget(nbRows, 2, new QLabel(QString::number(c.getPoids(), 'f', 1)));
        ui->lineEditPoidsCamionEspagne->setText(QString::number(poids, 'f', 1) + " kg");
        ui->lineEditVolumeCamionEspagne->setText(QString::number(volume, 'f', 1) + " m³");
    } else {
        int nbRows = ui->tableWidgetFrance->rowCount();
        ui->tableWidgetFrance->setRowCount(nbRows+1);
        ui->tableWidgetFrance->setCellWidget(nbRows, 0, new QLabel(c.getNom()));
        ui->tableWidgetFrance->setCellWidget(nbRows, 1, new QLabel(c.getType()));
        ui->tableWidgetFrance->setCellWidget(nbRows, 2, new QLabel(QString::number(c.getPoids(), 'f', 1)));
        ui->lineEditPoidsCamionFrance->setText(QString::number(poids, 'f', 1) + " kg");
        ui->lineEditVolumeCamionFrance->setText(QString::number(volume, 'f', 1) + " m³");
    }
}



