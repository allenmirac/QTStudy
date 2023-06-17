#ifndef NETWORKGAME_H
#define NETWORKGAME_H

#include "chessboard.h"
#include <QTcpServer>
#include <QTcpSocket>

class NetworkGame : public ChessBoard
{
public:
    NetworkGame(bool isServer);
    ~NetworkGame();

    QTcpServer* m_tcpServer;
    QTcpSocket* m_tcpSocket;

    virtual void clickPieces(int id, int row, int col) override;

public slots:
    void slotNewConnection();
    void slotRecv();
};

#endif // NETWORKGAME_H
