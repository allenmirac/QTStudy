#ifndef CHESSBOARD_H
#define CHESSBOARD_H

/***
 *      ┌─┐       ┌─┐ + +
 *   ┌──┘ ┴───────┘ ┴──┐++
 *   │                 │
 *   │       ───       │++ + + +
 *   ███████───███████ │+
 *   │                 │+
 *   │       ─┴─       │
 *   │                 │
 *   └───┐         ┌───┘
 *       │         │
 *       │         │   + +
 *       │         │
 *       │         └──────────────┐
 *       │                        │
 *       │                        ├─┐
 *       │                        ┌─┘
 *       │                        │
 *       └─┐  ┐  ┌───────┬──┐  ┌──┘  + + + +
 *         │ ─┤ ─┤       │ ─┤ ─┤
 *         └──┴──┘       └──┴──┘  + + + +
 *                神兽保佑
 *               代码无BUG!
 */

#include <QMainWindow>
#include <QPaintEvent>
#include <QTimer>
#include <QTime>
#include <QPoint>
#include <QPainter>
#include <QVector>
#include <QMessageBox>
#include "chesspieces.h"
#include "chessstep.h"
#include "chesssound.h"

namespace Ui {
class ChessBoard;
}

class ChessBoard : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChessBoard(QWidget *parent = nullptr);
    ~ChessBoard();

    void init();

    bool isRed(int id);
    bool isDead(int id);
    void killStone(int id);
    void reviveStone(int id);
    void moveStone(int moveid, int row, int col);
    bool sameColor(int moveId, int killId);
    int getStoneId(int row, int col);

    int  getStoneCountAtLine(int row1, int col1, int row2, int col2);
    void whoWin();
    bool isChecked(QPoint pt, int& row, int& col);
    int relation(int row1, int col1, int row2, int col2);
    QPoint getRealPoint(QPoint pt);
    bool isGeneral();

private:
    bool hongMenFeast();
    bool havePieces(int row, int col);
    void reset();
    void winMessageBox(QString title, QString msg);

public:
    QPoint center(int row, int col);
    QPoint center(int id);

    //绘制
    virtual void paintEvent(QPaintEvent *);
    void drawChessPieces(QPainter& painter, int id);
    void drawLastStep(QPainter &painter, QVector<ChessStep*>& steps);
    void drawTextStep();

    //移动规则
    bool canMove(int moveId, int killId, int row, int col);
    bool canMoveJIANG(int moveId, int killId, int row, int col);
    bool canMoveSHI(int moveId, int killId, int row, int col);
    bool canMoveXIANG(int moveId, int killId, int row, int col);
    bool canMoveMA(int moveId, int killId, int row, int col);
    bool canMoveCHE(int moveId, int killId, int row, int col);
    bool canMovePAO(int moveId, int killId, int row, int col);
    bool canMoveBING(int moveId, int killId, int row, int col);
    bool canSelect(int id);

    //鼠标移动相关
    virtual void mouseReleaseEvent(QMouseEvent *ev);
    void click(QPoint pt);
    virtual void clickPieces(int id, int row, int col);
    void trySelectStone(int id);
    void tryMoveStone(int killid, int row, int col);
    void doMoveStone(int moveid, int killid, int row, int col);
    void saveStep(int moveid, int killid, int row, int col, QVector<ChessStep*>& steps);
    QString textStep(int moveid, int row, int col);

    void backOne();
    void back(ChessStep* step);
    virtual void back();

    ChessPieces m_chessPieces[32];
    QVector<ChessStep*> m_chessSteps;
    ChessSound m_Chessvoice;
    int m_radius;
    int m_offset;
    int m_distance;
    int m_selectID;         //选中棋子[-1:选棋子 || 非-1:走棋子]
    int m_checkedID;        //给robot函数做辅助，表示第二次[点击]其他的棋子
    bool m_isRed;
    bool m_isTcpServer;
    bool m_isOver;
    bool m_isShowStep;
    QString textStepsRecord;

private:
    Ui::ChessBoard *ui;

    QTimer *m_timer;
    QTime *m_timeRecord;
    bool m_isStart;

signals:
    void toMenu();
private slots:
    void updateTime();
    void on_ptnStart_clicked();
    void on_ptnRefresh_clicked();
    void on_ptnRestart_clicked();
    void on_ptnBack_clicked();
    void on_ptnShowSteps_clicked();
    void on_ptnToMenu_clicked();
};

#endif // CHESSBOARD_H
