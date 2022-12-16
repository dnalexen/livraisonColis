#include "widget.h"
#include "./ui_widget.h"

#define POIDS_MAX 500
#define VOLUME_MAX 40000

/**
 * @brief Widget::Widget
 * @param parent
 */
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("serveur");

    ui->pushButtonAllemagne->setVisible(false);
    ui->pushButtonEspagne->setVisible(false);
    ui->pushButtonFrance->setVisible(false);

    mServer = new QTcpServer(this);
    connect(mServer,SIGNAL(newConnection()),this,SLOT(clientConnected()));
    mServer->listen(QHostAddress::Any,9090);

    mDB->createTable("tableColis");
    mDB->createTable("tableCamion");
}

/**
 * @brief Widget::~Widget
 */
Widget::~Widget()
{
    delete mServer;
    delete ui;

    for(int i=0; i<mListCamions.size(); i++)
        delete mListCamions[i];

    delete mDB;
}

/**
 * @brief Widget::clientConnected
 * Cette méthode gère la connection
 * d'un client au serveur.
 */
void Widget::clientConnected()
{
    QTcpSocket* sockClient = mServer->nextPendingConnection();
    mClients << sockClient;
    connect(sockClient,SIGNAL(readyRead()),this,SLOT(dataIsComing()));
    connect(sockClient,SIGNAL(disconnected()),this,SLOT(clientDisconnected()));
}

/**
 * @brief Widget::clientDisconnected
 * Cette méthode gère la déconnection
 * d'un client du serveur.
 */
void Widget::clientDisconnected()
{
    QTcpSocket* sock = (QTcpSocket*)sender();
    mClients.removeAll(sock);
    sock->deleteLater();
}

/**
 * @brief Widget::dataIsComing
 * Cette méthode permet de réceptionner un colis
 * et le charger dans un camion.
 */
void Widget::dataIsComing()
{
    QTcpSocket* sock = (QTcpSocket*)sender();
    QByteArray data = sock->readAll();
    Colis c(data);

    //qDebug() << c.toString();

    QStringList destinationsCamionsList;
    bool succesAjoutColis=false;

    for(int i=0; i<mListCamions.size(); i++)
        destinationsCamionsList.append(mListCamions[i]->getPays());

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
    }else{
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
                        ui->lineEditPoidsCamionAllemagne->setText("0");
                        ui->lineEditVolumeCamionAllemagne->setText("0");
                        ui->tableWidgetAllemagne->setRowCount(0);
                    }
                    else if(mListCamions[i]->getPays() == "Espagne")
                    {
                        ui->tableWidgetEspagne->clear();
                        ui->lineEditPoidsCamionEspagne->setText("0");
                        ui->lineEditVolumeCamionEspagne->setText("0");
                        ui->tableWidgetEspagne->setRowCount(0);
                    }
                    else if(mListCamions[i]->getPays() == "France")
                    {
                        ui->tableWidgetFrance->clear();
                        ui->lineEditPoidsCamionFrance->setText("0");
                        ui->lineEditVolumeCamionFrance->setText("0");
                        ui->tableWidgetFrance->setRowCount(0);
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

/**
 * @brief Widget::envoiCamion
 * Cette méthode permet de générer le bordereau
 * de transport d'un Camion.
 * @param ptrCamion: pointeur d'un Camion
 */
void Widget::envoiCamion(Camion* ptrCamion)
{
    if(!QDir("../serveurLivraison_libColisStatique/bordereauxTransport").exists())
        QDir().mkdir("../serveurLivraison_libColisStatique/bordereauxTransport");

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

    font.setPixelSize(150);
    painter.setFont(font);
    y +=250;
    painter.drawText(100, y, ptrCamion->toString());

    font.setPixelSize(200);
    painter.setFont(font);
    y +=400;
    painter.drawText(100, y, "Information des colis:");

    font.setPixelSize(150);
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

/**
 * @brief Widget::miseAJourFenetre
 * Cette méthode met à jour l'interface de
 * chargement des camions.
 * @param pays: pays de destination du camion
 * @param poids: poids du camion
 * @param volume: volume du camion
 * @param c: colis ajouté au camion
 */
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



