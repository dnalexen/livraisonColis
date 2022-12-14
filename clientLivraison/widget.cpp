#include "widget.h"
#include "./ui_widget.h"
#include "colis.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("client");
    mSock = new QTcpSocket(this);
    mSock->connectToHost("127.0.0.1",9090);

    ui->comboBoxType->addItems(QStringList {"Petit", "Moyen", "Grand"});

    ui->comboBoxPays->addItems(QStringList {"Allemagne", "Espagne", "France"});

    connect(mSock, SIGNAL(connected()), this, SLOT(Connected()));
    connect(mSock, SIGNAL(Disconnected()), this, SLOT(Disconnected()));
    connect(ui->pushButtonEnvoyer, SIGNAL(clicked(bool)), this, SLOT(envoisColis()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::envoisColis()
{
    int hauteurPetit = 20;
    int largeurPetit = 30;
    int longueurPetit = 40;

    int hauteurMoyen = 25;
    int largeurMoyen = 35;
    int longueurMoyen = 45;

    int hauteurGrand = 30;
    int largeurGrand = 40;
    int longueurGrand = 50;

    int hauteur, largeur, longueur, volume;
    double poids;

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

void Widget::Connected()
{
    ui->pushButtonEnvoyer->setEnabled(true);
    qDebug() << "connecté";
}

void Widget::Disconnected()
{
    ui->pushButtonEnvoyer->setEnabled(false);
    qDebug() << "déconnecté";
}

