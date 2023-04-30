#include "mainmenuwindow.h"
#include "ui_mainmenuwindow.h"
#include <QPainter>

MainMenuWindow::MainMenuWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainMenuWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(QString("翻金币"));
    this->setWindowIcon(QIcon(":/res/coin0001.ico"));
    this->setFixedSize(350, 600);

}

MainMenuWindow::~MainMenuWindow()
{
    delete ui;
}

void MainMenuWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix(":/res/Level1.jpg");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
}



