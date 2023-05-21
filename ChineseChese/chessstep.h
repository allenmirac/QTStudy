#ifndef CHESSSTEP_H
#define CHESSSTEP_H

#include <QObject>

class ChessStep : public QObject
{
    Q_OBJECT
public:
    explicit ChessStep(QObject *parent = nullptr);

    int m_moveID;   //移动棋子ID
    int m_killID;   //将要被击杀的棋子ID
    int m_rowFrom;  //原位置的行
    int m_colFrom;  //原位置的列
    int m_rowTo;    //目的位置的行
    int m_colTo;    //目的位置的列

signals:

};

#endif // CHESSSTEP_H
