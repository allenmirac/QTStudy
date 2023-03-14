#include "login.h"
#include <QApplication>
#include "chatroom.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login l;
    ChatRoom *w = new ChatRoom();

    int ok = l.exec();

    if (ok == QDialog::Accepted)
    {
        w->show();
        return a.exec();
    }
    else
    {
        return 0;
    }
}
