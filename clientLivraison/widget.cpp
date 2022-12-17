#include "widget.h"
#include "./ui_widget.h"
#include "colis.h"
#include <QSettings>

float hauteurPetit;
float largeurPetit;
float longueurPetit;

float hauteurMoyen;
float largeurMoyen;
float longueurMoyen;

float hauteurGrand;
float largeurGrand;
float longueurGrand;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //Lecture des dimensions des colis
    QSettings settings("../clientLivraison/settings.ini", QSettings::IniFormat);

    hauteurPetit = settings.value("Petit/Hauteur", "settings").toFloat();
    largeurPetit = settings.value("Petit/Largeur", "settings").toFloat();
    longueurPetit = settings.value("Petit/Longueur", "settings").toFloat();

    hauteurMoyen = settings.value("Moyen/Hauteur", "settings").toFloat();
    largeurMoyen = settings.value("Moyen/Largeur", "settings").toFloat();
    longueurMoyen = settings.value("Moyen/Longueur", "settings").toFloat();

    hauteurGrand = settings.value("Grand/Hauteur", "settings").toFloat();
    largeurGrand = settings.value("Grand/Largeur", "settings").toFloat();
    longueurGrand = settings.value("Grand/Longueur", "settings").toFloat();

    setWindowTitle("Client"); //Nommage de la fenêtre client

    //Connexion du client au serveur
    mSock = new QTcpSocket(this);
    mSock->connectToHost("127.0.0.1",9090);

    //Remplissage des combobox
    ui->comboBoxType->addItems(QStringList {"Petit", "Moyen", "Grand"});
    ui->comboBoxPays->addItems(QStringList {"Allemagne", "Espagne", "France"});

    //Déclenchement des méthodes SLOT en fonction du SIGNAL
    connect(mSock, SIGNAL(connected()), this, SLOT(Connected()));
    connect(mSock, SIGNAL(Disconnected()), this, SLOT(Disconnected()));
    connect(ui->pushButtonEnvoyer, SIGNAL(clicked(bool)), this, SLOT(envoisColis()));
}

Widget::~Widget()
{
    delete mSock;
    delete ui;
}

void Widget::envoisColis()
{
    float hauteur, largeur, longueur, volume;
    float poids;

    QString nom = ui->lineEditNom->text();
    QString pays = ui->comboBoxPays->currentText();
    QString type = ui->comboBoxType->currentText();

    if(type == "Petit")
    {
        hauteur = hauteurPetit;
        largeur = largeurPetit;
        longueur = longueurPetit;
    }else if(type == "Moyen"){
        hauteur = hauteurMoyen;
        largeur = largeurMoyen;
        longueur = longueurMoyen;
    }else {
        hauteur = hauteurGrand;
        largeur = largeurGrand;
        longueur = longueurGrand;
    }
    volume = hauteur * largeur * longueur;    

    Colis monColis(hauteur, largeur, longueur, nom, pays, type);

    poids = monColis.getPoids();

    ui->lineEditHauteur->setText(QString::number(hauteur) + " m");
    ui->lineEditLargeur->setText(QString::number(largeur) + " m");
    ui->lineEditLongueur->setText(QString::number(longueur) + " m");
    ui->lineEditPoids->setText(QString::number(poids, 'f', 1) + " kg");
    ui->lineEditVolume->setText(QString::number(volume, 'f', 2) + " m³");

    mSock->write(monColis.toJson()); //Envoi des données du colis au serveur
}

void Widget::Connected()
{
    ui->pushButtonEnvoyer->setEnabled(true);
}

void Widget::Disconnected()
{
    ui->pushButtonEnvoyer->setEnabled(false);    
}

