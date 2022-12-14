#include "widget.h"
#include "./ui_widget.h"

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
}

