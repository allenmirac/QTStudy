#ifndef CHESSSOUND_H
#define CHESSSOUND_H

#include <QObject>
#include <QSound>

class ChessSound : public QObject
{
    Q_OBJECT
public:
    explicit ChessSound(QObject *parent = nullptr);
    ~ChessSound();

    QSound *m_win =new QSound(":/sound/WinSound.wav",this);
    QSound *m_select =new QSound(":/sound/selectChess.wav",this);
    QSound *m_move =new QSound(":/sound/moveChess.wav",this);
    QSound *m_eat =new QSound(":/sound/eatChess.wav",this);
    QSound *m_back =new QSound(":/sound/backChess.wav",this);
    QSound *m_general =new QSound(":/sound/generalSound.wav",this);

    void voiceWin();    //胜利音效
    void voiceSelect(); //选棋音效
    void voiceMove();   //移动音效
    void voiceEat();    //吃子音效
    void voiceBack();   //悔棋音效
    void voiceGeneral();//将军音效

signals:

};

#endif // CHESSSOUND_H
