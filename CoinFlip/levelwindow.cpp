#include "levelwindow.h"
#include "mypushbutton.h"
#include <QPushButton>

LevelWindow::LevelWindow(QWidget *parent) : MainMenuWindow(parent)
{
    this->setWindowTitle("关卡");
    QPushButton *backBtn = new QPushButton("Back", this);
    backBtn->setIcon(QIcon(":/res/back.ico"));
    //  backBtn->setFlat(true);
    backBtn->move(this->width()-backBtn->width(), this->height()-backBtn->height());
    connect(backBtn, &QPushButton::clicked, this, &LevelWindow::backBtnClicked);

    int width = 80;
    int height = 80;
    for(int i=0; i<12; i++){
        MyPushbutton *levelBtn = new MyPushbutton(QString::number(i+1), this);
        levelBtn->setBtnPix(":/res/LevelIcon.png");
        levelBtn->move(i%4*width+30, i/4*height+200);
        levelBtn->resize(width, height);
    }
}
