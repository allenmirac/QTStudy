#include "exprogressbar.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ExProgressBar w;
    w.show();
    return a.exec();
}
