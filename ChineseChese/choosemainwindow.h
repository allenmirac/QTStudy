#ifndef CHOOSEMAINWINDOW_H
#define CHOOSEMAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "chessboard.h"
#include "robotgame.h"
#include "networkgame.h"

class ChooseMainWindow : public QDialog
{
    Q_OBJECT
public:
    explicit ChooseMainWindow(QWidget *parent = nullptr);

signals:

private:
    QPushButton* m_buttons[3];
    ChessBoard* m_pAgainstYourself;
    RobotGame* m_pRobotGame;
    NetworkGame* m_pNetworkGame;
};

#endif // CHOOSEMAINWINDOW_H
