#include "robotgame.h"

RobotGame::RobotGame()
{

}

RobotGame::~RobotGame()
{

}

void RobotGame::chooseOrMovePieces(int tempID, int &row, int &col)
{
    if(m_selectID == -1){
        if(m_chessPieces[m_checkedID].m_isRed){
            m_selectID = tempID;
        }else{
            m_selectID = -1;
            return;
        }
    }else{
        if(canMove(m_selectID, m_checkedID, row, col)){
            m_chessPieces[m_selectID].m_row = row;
            m_chessPieces[m_selectID].m_col = col;
            if(m_checkedID != -1)
                m_chessPieces[m_checkedID].m_isDead = true;

            m_selectID = -1;
            m_isRed = !m_isRed;
        }
    }
    whoWin();
    update();
}

void RobotGame::saveStep(int selectedID, int checkedID, int row, int col, QVector<ChessStep *> &steps)
{
    ChessStep* step = new ChessStep;
    step->m_rowFrom = m_chessPieces[selectedID].m_row;
    step->m_colFrom = m_chessPieces[selectedID].m_col;
    step->m_rowTo = row;
    step->m_colTo = col;
    step->m_moveID = selectedID;
    step->m_killID = checkedID;

    steps.append(step);
}

void RobotGame::getAllPossibleMoveStep(QVector<ChessStep *> &steps)
{
    for(int id = 0; id<16; id++){
        if(m_chessPieces[id].m_isDead)
            continue;

        for(int row=0; row<10; row++){
            for(int col=0; col<9; col++){
                int i = 16;             //机器人是黑方
                for( ; i <= 31; i++){
                    if(m_chessPieces[i].m_row == row && m_chessPieces[i].m_col == col && m_chessPieces[i].m_isDead == false)
                        break;
                }

                if(i!=32){
                    if(canMove(id, i, row, col))
                        saveStep(id, i, row, col, steps);
                }
            }
        }
    }
}

// 该函数实现了一个棋类游戏中所有未死亡的棋子在棋盘上所有能够不吃子移动的走法的获取
void RobotGame::getAllPossibleMoveStepAndNoKill(QVector<ChessStep *> &steps)
{
    for(int id = 0; id<16; id++){
        if(m_chessPieces[id].m_isDead)
            continue;

        for(int row=0; row<10; row++){
            for(int col=0; col<9; col++){
                int i = 0;
                for( ; i <= 31; i++){
                    if(m_chessPieces[i].m_row == row && m_chessPieces[i].m_col == col && m_chessPieces[i].m_isDead == false)
                        break;
                }

                if(id < 16 && i ==32){//-1??????
                    if(canMove(id, -1, row, col))
                        saveStep(id, -1, row, col, steps);
                }
            }
        }
    }
}

void RobotGame::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() != Qt::LeftButton)
        return;

    int row, col;
    bool bIsChecked=isChecked(ev->pos(), row, col);
    if(!bIsChecked)
        return;

    m_checkedID = -1;

    int i =0;
    for( ; i < 32; i++)
    {
        if(m_chessPieces[i].m_row == row && m_chessPieces[i].m_col == col && m_chessPieces[i].m_isDead == false)
            break;
    }

    if(0<=i && i<32)
        m_checkedID = i;

    clickPieces(m_checkedID, row, col);

    if(m_isRed) //红方玩家时间
    {
        chooseOrMovePieces(i, row, col);
        if(!m_isRed) //黑方紧接着进行游戏
        {
            machineChooseAndMovePieces();
        }
    }
}

void RobotGame::clickPieces(int checkedID, int &row, int &col)
{
    if(m_isRed)
    {
        chooseOrMovePieces(checkedID, row, col);

        if(!m_isRed)
            machineChooseAndMovePieces();
    }
}

void RobotGame::fakeMove(ChessStep *step)
{
    if(step->m_killID != -1)
        m_chessPieces[step->m_killID].m_isDead = true;

    m_chessPieces[step->m_moveID].m_row = step->m_rowTo;
    m_chessPieces[step->m_moveID].m_col = step->m_colTo;
    m_isRed = !m_isRed;
}

void RobotGame::unFakeMove(ChessStep *step)
{
    if(step->m_killID != -1)
        m_chessPieces[step->m_killID].m_isDead = false;

    m_chessPieces[step->m_moveID].m_row = step->m_rowFrom;
    m_chessPieces[step->m_moveID].m_col = step->m_colFrom;
    m_isRed = !m_isRed;
}

int RobotGame::calcScore()
{
    //enum m_emTYPE{JIANG, SHI, XIANG, MA, CHE, PAO, BING};
    //黑棋分数 - 红棋分数
    int redGrossScore = 0;
    int blackGrossScore = 0;

    static int chessScore[]={200, 20, 40, 60, 100, 80, 10};

    for(int i=0; i<16; i++)
    {
        if(m_chessPieces[i].m_isDead)
            continue;
        blackGrossScore += chessScore[m_chessPieces[i].m_emType];
    }

    for(int i=16; i<32; i++)
    {
        if(m_chessPieces[i].m_isDead)
            continue;
        redGrossScore += chessScore[m_chessPieces[i].m_emType];
    }

    return (blackGrossScore - redGrossScore);
}

ChessStep *RobotGame::getBestMove()
{
    int maxScore = -10000;
    ChessStep* retStep = NULL;

    //有可击杀的红棋子就走击杀红棋子最优的一步
    // 1.看看有那些步骤可以走
    QVector<ChessStep*> steps;
    getAllPossibleMoveStep(steps);   // 黑棋吃红棋的所有可能的步骤

    //没有可击杀的红棋子就走最后的一步
    QVector<ChessStep*> stepsAndNoKill;
    getAllPossibleMoveStepAndNoKill(stepsAndNoKill);   // 黑棋移动所有可能的步骤(不吃红棋子)

    //2.试着走一下
    for(QVector<ChessStep*>::iterator it = steps.begin(); it!=steps.end(); it++)
    {
        ChessStep* step = *it;
        fakeMove(step);
        int score = calcScore();   //3.计算最好的局面分
        unFakeMove(step);

        if(score > maxScore)
        {
            maxScore = score;
            retStep = step;
        }
    }

    if(retStep != NULL)
        return retStep;

    //2.试着走一下
    //从这种不击杀红棋子，只是单纯移动黑棋steps里面，随机抽选一种进行下棋
    int nStepsCount = stepsAndNoKill.count();
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime())); //随机数种子, 0~MAX
    int temp =qrand()% nStepsCount;
    QVector<ChessStep*>::iterator it = stepsAndNoKill.begin();
    retStep = it[temp];

    if(retStep == NULL)
        whoWin();

    return retStep;
}

void RobotGame::machineChooseAndMovePieces()
{
    ChessStep* step = getBestMove();

    if(step->m_killID == -1)  //黑棋没有可以击杀的红棋子，只好走能够走的过程中最后一步棋
    {
        m_chessPieces[step->m_moveID].m_row = step->m_rowTo;
        m_chessPieces[step->m_moveID].m_col = step->m_colTo;
    }
    else //黑棋有可以击杀的红棋子，故击杀红棋子
    {
        m_chessPieces[step->m_killID].m_isDead = true;
        m_chessPieces[step->m_moveID].m_row = m_chessPieces[step->m_killID].m_row;
        m_chessPieces[step->m_moveID].m_col = m_chessPieces[step->m_killID].m_col;
        m_selectID = -1;
    }

    m_isRed = !m_isRed;
}













