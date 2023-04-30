#include "startwindow.h"
#include <QPainter>
#include <QPixmap>
#include <QImage>
#include <QPushButton>
#include <mypushbutton.h>
#include <QDebug>
#include <QTimer>

StartWindow::StartWindow(QWidget *parent) : MainMenuWindow(parent)
{
    this->setWindowTitle(QString("开始场景"));

    MyPushbutton *ptnStart = new MyPushbutton("start", this);
    ptnStart->setBtnPix(":/res/MenuSceneStartButton.png");
    ptnStart->resize(120, 120);
    int x=this->width()/2 - ptnStart->width()/2;
    int y = this->height()*1.0*3/4 - ptnStart->height()/2;
    ptnStart->move(x, y);

    connect(&this->levelWindow, &LevelWindow::backBtnClicked, [=]{
        this->show();
        this->levelWindow.hide();
    });
    connect(ptnStart, &MyPushbutton::clicked, [=]{
        ptnStart->setEnabled(false);
        ptnStart->animationDown();
        QTimer::singleShot(150, [=]{
           ptnStart->animationUp();
        });
        QTimer::singleShot(300, [=]{
            ptnStart->setEnabled(true);
            this->hide();
            this->levelWindow.show();
        });
    });
}

void StartWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this); //终于找到不显示图片的原因了，原来是没有设置device
    QPixmap pix(":/res/BG.jpg");
//    pix.load(":/res/MenuSceneBg.png");// libpng warning: iCCP: known incorrect sRGB profile
//    painter.drawImage(0, 0, image);
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
    //qDebug()<<"123"<<endl;
}
