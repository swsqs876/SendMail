#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

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

private:
    Ui::Widget *ui;
    QString userName;
    QString password;
};

#endif // WIDGET_H
