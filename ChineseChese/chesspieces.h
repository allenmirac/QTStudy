#ifndef CHESSPIECES_H
#define CHESSPIECES_H

#include <QString>

class ChessPieces
{
public:
    ChessPieces();
    ~ChessPieces();

    void init(int id);
    QString getName(bool isRedSide);
    QString getColText(int col);
    QString getRowText(int row);
    QString getMoveText(int rowFrom, int rowTo);
    enum m_emTYPE{JIANG, SHI, XIANG, MA, CHE, PAO, BING};

    int m_row;
    int m_col;
    int m_ID;
    bool m_isDead;
    bool m_isRed;
    m_emTYPE m_emType;

    QString colTextRed[9]={"九", "八", "七", "六", "五", "四", "三", "二", "一"};
    QString colTextBlack[9]={"1", "2", "3", "4", "5", "6", "7", "8", "9"};
    QString colTextRedTurn[9]={"一", "二", "三", "四", "五", "六", "七", "八", "九"};
};

#endif // CHESSPIECES_H
