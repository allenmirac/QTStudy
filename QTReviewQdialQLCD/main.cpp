#include "exqdialqlcd.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ExQdialQLCD w;
    w.show();
    return a.exec();
}
