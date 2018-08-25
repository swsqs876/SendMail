#include "smtp.h"
#include <QDebug>

Smtp::Smtp(QObject *parent)
{

}

Smtp::Smtp(QByteArray username,QByteArray password, QObject * parent)
    :QObject(parent),
      status(DISCONNECTED)
{
    if(username.contains("@163"))
    {
        this->username = username;
        this->password = password;
    }
    else {
        qDebug()<<"NOT 163";
    }
    clientsocket = new QTcpSocket();
    connect(clientsocket,SIGNAL(connected()),this,SLOT(doConnected()));
    connect(clientsocket,SIGNAL(readyRead()),this,SLOT(doReadAndSendNextOrder()));

}

void Smtp::send(QByteArray recvaddr,QString subject,QString content)
{
    this->recvaddr = recvaddr;
    this->subject = subject;
    this->content = content;
    status = DISCONNECTED;
    this->clientsocket->connectToHost("smtp.163.com",25,QTcpSocket::ReadWrite);
    clientsocket->waitForReadyRead();
}

Smtp::doConnected()
{
    qDebug() << __FUNCTION__ ;
    status = CONNECTED;
}

void Smtp::doReadAndSendNextOrder()
{
    qDebug() << "doReadAndSendNextOrder";
    recvdata = clientsocket->readAll();
    qDebug()<< recvdata;

    QByteArray usernametmp = this->username;
    QByteArray recvaddrtmp = this->recvaddr;

        if (isSecond) {
            qDebug()<< "second";
            this->clientsocket->write("rcpt to:<************@qq.com>\r\n");
            status = RECPT_TO;
            isSecond = false;
            canExit = true;
            return;
        }


    switch (status) {
    case DISCONNECTED:
        break;
    case CONNECTED:
        qDebug() << "CONNECTED";
        this->clientsocket->write("HELO smtp.163.com\r\n");
        status = HELO;
        break;
    case HELO:
        qDebug() << "HELO";
        this->clientsocket->write("AUTH LOGIN\r\n");
        status = AUTH_LOGIN;
        break;
    case AUTH_LOGIN:
        qDebug() << "AUTH_LOGIN";
        this->clientsocket->write(username.toBase64().append("\r\n"));
        status = AUTH_LOGIN_USERNAME;
        break;
    case AUTH_LOGIN_USERNAME:
        qDebug() << "AUTH_LOGIN_USERNAME";
        this->clientsocket->write(password.toBase64().append("\r\n"));
        status = AUTH_LOGIN_PWD;
        break;
    case AUTH_LOGIN_PWD:
        qDebug() << "AUTH_LOGIN_PWD";
        this->clientsocket->write(mailfrom.append(usernametmp.append(">\r\n")));
        status = MAIL_FROM;
        break;
    case MAIL_FROM:
        qDebug() << "MAIL_FROM";
        this->clientsocket->write(rcptto.append(recvaddrtmp.append(">\r\n")));
        status = RECPT_TO;
        break;
    case RECPT_TO:
        qDebug() << "RECPT_TO";
        this->clientsocket->write("data\r\n");
        status = DATA;
        break;
    case DATA:
    {
        qDebug() << "DATA";
        usernametmp = this->username;
        recvaddrtmp = this->recvaddr;

        this->clientsocket->write(prefrom.append(usernametmp.append("\r\n")));
        this->clientsocket->write(preto.append(recvaddrtmp.append("\r\n")));
        this->clientsocket->write(presubject.append(subject.toLocal8Bit().append("\r\n")));
        this->clientsocket->write("\r\n");
        this->clientsocket->write(content.toLocal8Bit().append("\r\n"));
        status = DATA_END;
        this->clientsocket->write(".\r\n");
    }
        break;
    case DATA_END:
    {
        qDebug() << "DATA_END SEND second";
        this->clientsocket->write("NOOP\r\n");
        status = RESET;
        if(canExit) {
            status = QUIT;
            this->clientsocket->write("quit\r\n");
        }
        //        this->clientsocket->write("quit\r\n");
        //        status = QUIT;
    }
        break;
    case RESET:
        qDebug() << "RESET";
        this->clientsocket->write("RSET\r\n");
        isSecond = true;
        break;
    case QUIT:
        qDebug() << "QUIT";
        status = DISCONNECTED;
        exit(0);
        break;

    default:
        break;
    }

}

Smtp::~Smtp()
{
    disconnect(clientsocket,SIGNAL(connected()),this,SLOT(doConnected()));
    disconnect(clientsocket,SIGNAL(readyRead()),this,SLOT(doReadAndSendNextOrder()));

    delete this->clientsocket;
}
