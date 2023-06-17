#include "networkgame.h"

NetworkGame::NetworkGame(bool isServer)
{
    m_tcpServer = nullptr;
    m_tcpSocket = nullptr;

    if(isServer){
        m_isTcpServer = true;
        m_tcpServer = new QTcpServer(this);
        m_tcpServer->listen(QHostAddress::Any, 5555);

        connect(m_tcpServer, &QTcpServer::newConnection, this, &NetworkGame::slotNewConnection);
    } else {
        m_isTcpServer = false;
        m_tcpSocket = new QTcpSocket(this);
        m_tcpSocket->connectToHost(QHostAddress("127.0.0.1"), 5555);

        connect(m_tcpSocket, &QTcpSocket::readyRead, this, &NetworkGame::slotRecv);
    }
}

NetworkGame::~NetworkGame()
{

}

void NetworkGame::clickPieces(int id, int row, int col)
{
    if(m_isTcpServer){
        if(m_selectID == -1 && m_checkedID == -1){
            if(m_isTcpServer != m_chessPieces[id].m_isRed)
                return ;
        }
    } else {
        if(m_selectID == -1 && m_checkedID == -1){
            if(m_isTcpServer != m_chessPieces[id].m_isRed)
                return ;
        }
    }

    whoWin();

    ChessBoard::clickPieces(id, row, col);

    char array[3];
    array[0] = id;
    array[1] = row;
    array[2] = col;

    // 如果先创建的客户端，就会报错，因为构造函数没有new QTcpSocket。
    m_tcpSocket->write(array, 3);
}

void NetworkGame::slotNewConnection()
{
    if(m_isTcpServer)
        return ;
    m_tcpSocket = m_tcpServer->nextPendingConnection();
    connect(m_tcpSocket, &QTcpSocket::readyRead, this, &NetworkGame::slotRecv);
}

void NetworkGame::slotRecv()
{
    QByteArray array = m_tcpSocket->readAll();

    int checkedID = array[0];
    int row = array[1];
    int col = array[2];

    ChessBoard::clickPieces(checkedID, row, col);
}

