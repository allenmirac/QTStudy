#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include "DoTcpServer.h"

namespace Ui {
class ChatRoomServerUI;
}

class Server : public QWidget
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = 0);
    ~Server();

private:
    int port;		//端口号，与客户端相同
    void showServerHostIP();	//显示服务器ip地址

    DoTcpServer* server;	//定义一个全局的server对象

public slots:
    void cleanBtn_Slots();	//清屏按钮
    void serverUIAddUser_Slots(QString, QString, QString, QString);
    void serverUIDeleteUser_Slots(QString);
    void serverUIChatMessage_Slots(QString);
private:
    void closeEvent(QCloseEvent *event);	//重写关闭窗口函数

private:
    Ui::ChatRoomServerUI *ui;
};

#endif // SERVER_H
