#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("client");
    //ui->pushButtonEnvoyer->
}

Widget::~Widget()
{
    delete ui;
}

