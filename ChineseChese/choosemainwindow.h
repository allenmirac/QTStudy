#ifndef CHOOSEMAINWINDOW_H
#define CHOOSEMAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "chessboard.h"

class ChooseMainWindow : public QDialog
{
    Q_OBJECT
public:
    explicit ChooseMainWindow(QWidget *parent = nullptr);

signals:

private:
    QPushButton* m_buttons[3];
    ChessBoard* m_pAgainstYourself;
};

#endif // CHOOSEMAINWINDOW_H
