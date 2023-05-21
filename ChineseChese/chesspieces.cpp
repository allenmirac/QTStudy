#include "chesspieces.h"

struct POS{
    int row;
    int col;
    ChessPieces::m_emTYPE emType;
};

POS pieces[16]={
    {0, 0, ChessPieces::CHE},
    {0, 1, ChessPieces::MA},
    {0, 2, ChessPieces::XIANG},
    {0, 3, ChessPieces::SHI},
    {0, 4, ChessPieces::JIANG},
    {0, 5, ChessPieces::SHI},
    {0, 6, ChessPieces::XIANG},
    {0, 7, ChessPieces::MA},
    {0, 8, ChessPieces::CHE},

    {2, 1, ChessPieces::PAO},
    {2, 7, ChessPieces::PAO},
    {3, 0, ChessPieces::BING},
    {3, 2, ChessPieces::BING},
    {3, 4, ChessPieces::BING},
    {3, 6, ChessPieces::BING},
    {3, 8, ChessPieces::BING}
};



ChessPieces::ChessPieces()
{

}

ChessPieces::~ChessPieces()
{

}

void ChessPieces::init(int id)
{
    if(id<16){
        m_row = pieces[id].row;
        m_col = pieces[id].col;
        m_emType = pieces[id].emType;
        m_isRed = false;
    }else{
        m_row = 9-pieces[id-16].row;
        m_col = 8-pieces[id-16].col;
        m_emType = pieces[id-16].emType;
        m_isRed = true;
    }
    m_isDead = false;
}

QString ChessPieces::getName(bool isRedSide)
{
    if(isRedSide){
        switch (m_emType) {
        case CHE:
            return "俥";
        case MA:
            return "傌";
        case PAO:
            return "炮";
        case BING:
            return "兵";
        case JIANG:
            return "帥";
        case SHI:
            return "仕";
        case XIANG:
            return "相";
        default:
            return "null";
        }
    }
    else{
        switch (m_emType) {
        case CHE:
            return "車";
        case MA:
            return "馬";
        case PAO:
            return "砲";
        case BING:
            return "卒";
        case JIANG:
            return "將";
        case SHI:
            return "士";
        case XIANG:
            return "象";
        default:
            return "null";
        }
    }
    return "ERROR";
}

QString ChessPieces::getColText(int col){
    QString colText;
    if(m_isRed)
    {
        colText= colTextRed[col];
    }
    else
    {
        colText= colTextBlack[col];
    }
    return colText;
}

/**
 * @brief ChessPieces::getRowText 得到行数的进退
 * @param row
 * @return
 */
QString ChessPieces::getRowText(int row){
    QString temp="";
    if(m_row== row)
    {
        temp.append("平");
        return temp;
    }
    if(m_row> row)
    {
        if(m_isRed){
            temp.append("进");
        }
        else
        {
            temp.append("退");
        }
    }
    else
    {
        if(m_isRed){
            temp.append("退");
        }
        else
        {
            temp.append("进");
        }
    }
    return temp;
}

/**
 * @brief ChessPieces::getMoveText 行数的变化，返回文本
 * @param rowFrom
 * @param rowTo
 * @return
 */
QString ChessPieces::getMoveText(int rowFrom, int rowTo){
    QString temp="";
        if(m_isRed)
        {
            temp.append(colTextRedTurn[abs(rowFrom-rowTo) -1]);
        }
        else
        {
            temp.append(colTextBlack[abs(rowFrom-rowTo) -1]);
        }
        return temp;
}

