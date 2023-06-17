#include "choosemainwindow.h"

ChooseMainWindow::ChooseMainWindow(QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle("选择游戏方式");
    this->setFixedSize(250,120);
    this->setWindowIcon(QIcon(":/images/chess.svg"));

    QVBoxLayout* lay = new QVBoxLayout(this);
    lay->addWidget(m_buttons[0] = new QPushButton("玩家自己对战"));
    lay->addWidget(m_buttons[1] = new QPushButton("玩家和AI对战"));
    lay->addWidget(m_buttons[2] = new QPushButton("双人网络对战"));

    /*游戏方式一: 自己和自己下棋【同一台PC机器】*/
    connect(m_buttons[0], &QPushButton::clicked,[=](){
        this->hide();
        m_pAgainstYourself = new ChessBoard();
        m_pAgainstYourself->setWindowTitle("玩家自己对战");
        m_pAgainstYourself->show();

        //返回主窗口
        connect(m_pAgainstYourself,&ChessBoard::toMenu,[=](){
            m_pAgainstYourself->close();
            this->show();
        });
    });

    /*游戏方式二: 自己和电脑下棋【同一台PC机器】*/
    connect(m_buttons[1], &QPushButton::clicked,[=](){
        this->hide();

        m_pRobotGame = new RobotGame();
        m_pRobotGame->setWindowTitle("玩家和AI对战");
        m_pRobotGame->show();

        //返回主窗口
        connect(m_pRobotGame,&ChessBoard::toMenu,[=](){
            m_pRobotGame->close();
            this->show();
        });
    });

    /*游戏方式三: 双人局域网下棋【可在局域网下不同台PC机器】*/
    connect(m_buttons[2], &QPushButton::clicked,[=](){
        this->hide();

        QMessageBox::StandardButtons ret = QMessageBox::question(NULL, "提示", "是否作为服务器启动[选择红方]?");

        bool bServer = false;
        if(ret == QMessageBox::Yes)
            bServer = true;

        m_pNetworkGame = new NetworkGame(bServer);
        m_pNetworkGame->setWindowTitle("双人网络对战");
        m_pNetworkGame->show();

        //返回主窗口
        connect(m_pNetworkGame,&ChessBoard::toMenu,[=](){
            m_pNetworkGame->close();
            this->show();
        });
    });
}
