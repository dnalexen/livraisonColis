#include "widget.h"
#include "./ui_widget.h"
#include "ColisStatique.h"
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

/**
 * @brief Widget::Widget
 * @param parent
 */
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QSettings settings("../clientLivraison_libColisStatique/settings.ini", QSettings::IniFormat);

    hauteurPetit = settings.value("Petit/Hauteur", "settings").toFloat();
    largeurPetit = settings.value("Petit/Largeur", "settings").toFloat();
    longueurPetit = settings.value("Petit/Longueur", "settings").toFloat();

    hauteurMoyen = settings.value("Moyen/Hauteur", "settings").toFloat();
    largeurMoyen = settings.value("Moyen/Largeur", "settings").toFloat();
    longueurMoyen = settings.value("Moyen/Longueur", "settings").toFloat();

    hauteurGrand = settings.value("Grand/Hauteur", "settings").toFloat();
    largeurGrand = settings.value("Grand/Largeur", "settings").toFloat();
    longueurGrand = settings.value("Grand/Longueur", "settings").toFloat();

    setWindowTitle("client");
    mSock = new QTcpSocket(this);
    mSock->connectToHost("127.0.0.1",9090);

    ui->comboBoxType->addItems(QStringList {"Petit", "Moyen", "Grand"});

    ui->comboBoxPays->addItems(QStringList {"Allemagne", "Espagne", "France"});

    connect(mSock, SIGNAL(connected()), this, SLOT(Connected()));
    connect(mSock, SIGNAL(Disconnected()), this, SLOT(Disconnected()));
    connect(ui->pushButtonEnvoyer, SIGNAL(clicked(bool)), this, SLOT(envoisColis()));
}

/**
 * @brief Widget::~Widget
 */
Widget::~Widget()
{
    delete mSock;
    delete ui;
}

/**
 * @brief Widget::envoisColis
 * Cette méthode permet d'envoyer un colis
 * au serveur.
 */
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
    poids = (float)(QRandomGenerator::global()->bounded(1, 500))/10;

    ui->lineEditHauteur->setText(QString::number(hauteur));
    ui->lineEditLargeur->setText(QString::number(largeur));
    ui->lineEditLongueur->setText(QString::number(longueur));
    ui->lineEditPoids->setText(QString::number(poids, 'f', 1));
    ui->lineEditVolume->setText(QString::number(volume));

    Colis monColis(hauteur, largeur, longueur, nom, pays, poids, type);

    mSock->write(monColis.toJson());
}

/**
 * @brief Widget::Connected
 * Cette méthode permet d'activer le bouton
 * Envoyer lorsque le client est connecté.
 */
void Widget::Connected()
{
    ui->pushButtonEnvoyer->setEnabled(true);
}

/**
 * @brief Widget::Disconnected
 * Cette méthode permet de désactiver le bouton
 * Envoyer lorsque le client est déconnecté.
 */
void Widget::Disconnected()
{
    ui->pushButtonEnvoyer->setEnabled(false);
}

