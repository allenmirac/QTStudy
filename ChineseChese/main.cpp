#include "mainmenuwindow.h"

#include <QApplication>
#include "chessboard.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //    MainMenuWindow w;
    //    w.show();
    ChessBoard chessBoard;
    chessBoard.show();
    return a.exec();
}
