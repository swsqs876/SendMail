#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    clientsocket = new QTcpSocket();
    connect(clientsocket,SIGNAL(connected()),this,SLOT(doConnected()));
    connect(clientsocket,SIGNAL(readyRead()),this,SLOT(doReadAndSendNextOrder()));

}

Widget::~Widget()
{
    delete ui;
    delete clientsocket;
}

void Widget::on_SignIn_pressed()
{
    clientsocket->connectToHost(ui->host->text(),ui->port->text().toInt(),QTcpSocket::ReadWrite);
}

void Widget::doConnected()
{
    qDebug() << __FUNCTION__ ;
}

void Widget::doReadAndSendNextOrder()
{
    qDebug() << clientsocket->readAll();
}

void Widget::on_sendOrder_pressed()
{
    qDebug() << "on_sendOrder_pressed :" << ui->lineEditOrder->text().toLocal8Bit();
    clientsocket->write(ui->lineEditOrder->text().toLocal8Bit().append("\r\n"));
}

void Widget::on_sendUserName_pressed()
{
    qDebug() << "sendUserName";
    clientsocket->write(ui->userName->text().toLocal8Bit().toBase64().append("\r\n"));
}

void Widget::on_sendPassword_pressed()
{
    qDebug() << "sendPassword";
    clientsocket->write(ui->password->text().toLocal8Bit().toBase64().append("\r\n"));
}

void Widget::on_sendContext_pressed()
{
    qDebug() << "sendContext";
    clientsocket->write(ui->textEdit->toPlainText().toLocal8Bit().append("\r\n"));
}
