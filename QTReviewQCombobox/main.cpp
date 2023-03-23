#include "exqcombobox.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ExQComboBox w;
    w.show();
    return a.exec();
}
