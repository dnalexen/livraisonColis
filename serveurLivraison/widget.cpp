#include "widget.h"
#include "./ui_widget.h"
#include "colis.h"

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
}

/**
 * @brief Widget::clientConnected
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
 */
void Widget::clientDisconnected()
{
    QTcpSocket* sock = (QTcpSocket*)sender();
    mClients.removeAll(sock);
    sock->deleteLater();
}

/**
 * @brief Widget::dataIsComing
 */
void Widget::dataIsComing()
{
    QTcpSocket* sock = (QTcpSocket*)sender();
    QByteArray data = sock->readAll();
    Colis c(data);

    //qDebug() << c.toString();

    QStringList destinationsCamionsList;
    bool colisAjoute=false;

    for(int i=0; i<mListCamions.size(); i++)
        destinationsCamionsList.append(mListCamions[i]->getPays());

    if(!destinationsCamionsList.contains(c.getPays()))
    {
        Camion* camion = new Camion(c.getPays(), POIDS_MAX, VOLUME_MAX);
        colisAjoute = camion->addColis(c);
        if(colisAjoute)
            miseAJourFenetre(camion->getPays(), camion->getPoids(), camion->getVolume(), c);
        mListCamions.append(camion);        
    }else{
        for(int i=0; i<mListCamions.size(); i++)
        {
            if(mListCamions[i]->getPays() == c.getPays())
            {
                colisAjoute = mListCamions[i]->addColis(c);
                if(colisAjoute)
                    miseAJourFenetre(mListCamions[i]->getPays(), mListCamions[i]->getPoids(), mListCamions[i]->getVolume(), c);
                if(!colisAjoute)
                {
                    envoiCamion(mListCamions[i]);
                    if(mListCamions[i]->getPays() == "Allemagne")
                    {
                        ui->tableWidgetAllemagne->clear();
                        ui->lineEditPoidsCamionAllemagne->setText("0");
                        ui->lineEditVolumeCamionAllemagne->setText("0");
                        ui->tableWidgetAllemagne->setRowCount(0);
                    } else if(mListCamions[i]->getPays() == "Espagne")
                    {
                        ui->tableWidgetEspagne->clear();
                        ui->lineEditPoidsCamionEspagne->setText("0");
                        ui->lineEditVolumeCamionEspagne->setText("0");
                        ui->tableWidgetEspagne->setRowCount(0);
                    } else {
                        ui->tableWidgetFrance->clear();
                        ui->lineEditPoidsCamionFrance->setText("0");
                        ui->lineEditVolumeCamionFrance->setText("0");
                        ui->tableWidgetFrance->setRowCount(0);
                    }
                    mListCamions.removeAt(i);
                    Camion* camion = new Camion(c.getPays(), POIDS_MAX, VOLUME_MAX);
                    colisAjoute = camion->addColis(c);
                    if(colisAjoute)
                        miseAJourFenetre(camion->getPays(), camion->getPoids(), camion->getVolume(), c);
                    mListCamions.append(camion);
                }
                break;
            }
        }
    }
}

/**
 * @brief Widget::envoiCamion
 * @param ptrCamion
 */
void Widget::envoiCamion(Camion* ptrCamion)
{
    if(!QDir("bordereauxTransport").exists())
        QDir().mkdir("bordereauxTransport");

    QString filename = "bordereauxTransport/" + ptrCamion->getID();
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
    for(auto colis : ptrCamion->getColisList())
        out << colis.toString() + "\n";
    file.flush();
    file.close();

    //Génération du bordereaux de transport en format PDF
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
        cheminImage = "/home/dnalexen/Documents/AJC_THALES/cours/11-PROJET C++/livraisonColis/serveurLivraison/images/allemagne.jpeg";
        largeurImage = 275;
        hauteurImage = 183;
    }
    else if(ptrCamion->getPays() == "Espagne")
    {
        cheminImage = "/home/dnalexen/Documents/AJC_THALES/cours/11-PROJET C++/livraisonColis/serveurLivraison/images/espagne.jpeg";
        largeurImage = 270;
        hauteurImage = 187;
    }
    else if(ptrCamion->getPays() == "France")
    {
        cheminImage = "/home/dnalexen/Documents/AJC_THALES/cours/11-PROJET C++/livraisonColis/serveurLivraison/images/france.jpeg";
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
    for(auto colis : ptrCamion->getColisList())
    {
        y +=250;
        painter.drawText(100, y, colis.toString());
    }

    painter.end();

    delete ptrCamion;
}

/**
 * @brief Widget::miseAJourFenetre
 * @param pays
 * @param poids
 * @param volume
 * @param c
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

