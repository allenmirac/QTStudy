#include "exwidget.h"
#include <QApplication>
#include <QPushButton>
#include <QDebug>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ExWidget w;
    w.show();
    return a.exec();
}
