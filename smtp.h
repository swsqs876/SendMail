#ifndef SMTP_H
#define SMTP_H

#include <QObject>
#include <QTcpSocket>

class Smtp : public QObject
{
    Q_OBJECT
public:
    explicit Smtp(QObject *parent = nullptr);
    Smtp(QByteArray username,QByteArray password, QObject *parent = nullptr);
    virtual ~Smtp();

    enum SmtpStatus {DISCONNECTED = 0, CONNECTED, HELO, AUTH_LOGIN,
                     AUTH_LOGIN_USERNAME, AUTH_LOGIN_PWD,
                     MAIL_FROM, RECPT_TO, DATA, DATA_END, RESET, QUIT};
    Q_ENUM(SmtpStatus)

    void send(QByteArray recvaddr,QString subject,QString content);
    SmtpStatus getSMTPStatus(){return status;}
private:
    QTcpSocket * clientsocket;
    QByteArray username;
    QByteArray password;
    QByteArray recvaddr;
    QByteArray mailfrom = "mail from:<";
    QByteArray rcptto = "rcpt to:<";
    QByteArray prefrom = "from:";
    QByteArray preto = "to:";
    QByteArray presubject ="subject:";
    QString subject;                //主题
    QString content;                //发送内容
    QByteArray recvdata;            //接收到的数据

    bool isSecond = false;
    bool canExit = false;
    SmtpStatus status;

public:

signals:

public slots:
    doConnected();
    void doReadAndSendNextOrder();
};

#endif // SMTP_H
