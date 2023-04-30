#include "mypushbutton.h"
#include <QPainter>
#include <QPropertyAnimation>
#include <QTimer>

MyPushbutton::MyPushbutton(QWidget *parent) : QPushButton(parent)
{
    this->setFlat(true);
}

MyPushbutton::MyPushbutton(QString str, QWidget *parent){
//    this = new QPushButton(str, parent);
    this->setText(str);
    this->setParent(parent);
    this->setFlat(true);

//    connect(this, &MyPushbutton::released, [=]{
//        this->animationUp();
//    });
}

void MyPushbutton::animationUp()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry", this);
    animation->setStartValue(this->geometry());
    animation->setEndValue(QRect(this->x(), this->y()-10, this->width(), this->height()));
    animation->setDuration(100);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MyPushbutton::animationDown()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry", this);
    animation->setStartValue(this->geometry());
    animation->setEndValue(QRect(this->x(), this->y()+10, this->width(), this->height()));
    animation->setDuration(100);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MyPushbutton::setBtnPix(QString url)
{
    btnPix = url;
}

void MyPushbutton::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(btnPix);
    painter.drawPixmap(this->width()/2-pix.width()/2, this->height()*3/4-pix.height(),pix.width(), pix.height(), pix);
    painter.drawText(0, 0, this->width(), this->height(), Qt::AlignCenter,this->text());
}
