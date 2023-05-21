#include "chesssound.h"

ChessSound::ChessSound(QObject *parent) : QObject(parent)
{

}

ChessSound::~ChessSound(){

}

void ChessSound:: voiceWin()
{
    if(m_win!= nullptr)
        this->m_win->play();
}

void ChessSound::voiceSelect()
{
    if(m_select!= nullptr)
        this->m_select->play();
}

void ChessSound:: voiceMove()
{
    if(m_move!= nullptr)
        this->m_move->play();
}

void ChessSound:: voiceEat()
{
    if(m_eat!= nullptr)
        this->m_eat->play();
}

void ChessSound:: voiceBack()
{
    if(m_back!= nullptr)
        this->m_back->play();
}

void ChessSound:: voiceGeneral()
{
    if(m_general!= nullptr)
        this->m_general->play();
}
