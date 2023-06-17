#ifndef ROBOTGAME_H
#define ROBOTGAME_H

#include <QVector>
#include "chessboard.h"
#include "chessstep.h"

class RobotGame : public ChessBoard
{
public:
    RobotGame();
    ~RobotGame();

    void chooseOrMovePieces(int tempID, int& row, int& col);
    void saveStep(int selectedId, int checkedID, int row, int col, QVector<ChessStep*>& steps);
    void getAllPossibleMoveStep(QVector<ChessStep*>& steps);
    void getAllPossibleMoveStepAndNoKill(QVector<ChessStep*>& steps);
    virtual void mousePressEvent(QMouseEvent *);
    void clickPieces(int checkedID, int& row, int& col);
    void fakeMove(ChessStep* step);
    void unFakeMove(ChessStep* step);
    int calcScore();
    ChessStep* getBestMove();
    void machineChooseAndMovePieces();
};

#endif // ROBOTGAME_H
