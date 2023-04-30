#include "mainmenuwindow.h"

#include <QApplication>
#include "startwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainMenuWindow w;
//    w.show();
    StartWindow start;
    start.show();
    return a.exec();
}
