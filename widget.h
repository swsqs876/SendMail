#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QScopedPointer>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    QString getUserName() {return this->userName;}
    QString getPassword(){return this->password;}


public slots:


private slots:
    void on_SignIn_pressed();
    void doConnected();
    void doReadAndSendNextOrder();

    void on_sendOrder_pressed();

    void on_sendUserName_pressed();

    void on_sendPassword_pressed();

    void on_sendContext_pressed();

private:
    Ui::Widget *ui;
//    QScopedPointer<QTcpSocket> clientsocket;
    QTcpSocket * clientsocket;
    QString userName;
    QString password;
};

#endif // WIDGET_H
