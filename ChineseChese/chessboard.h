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

    virtual void paintEvent(QPaintEvent *);
    void drawChessPieces(QPainter& painter, int id);
    void drawLastStep(QPainter &painter, QVector<ChessStep*>& steps);
    void drawTextStep();

    ChessPieces m_chessPieces[32];
    QVector<ChessStep*> m_chessSteps;
    ChessSound m_Chessvoice;
    int m_radius;
    int m_offset;
    int m_distance;
    int m_selectID;
    int m_checkedID;
    bool m_isRed;
    bool m_isTcpServer;
    bool m_isOver;
    bool m_isShowStep;
    QString textStepsRecord;

private:
    Ui::ChessBoard *ui;

    QTimer *m_timer;
    QTime m_timeRecord;
    bool m_isStart;

signals:
    void toMenu();
};

#endif // CHESSBOARD_H
