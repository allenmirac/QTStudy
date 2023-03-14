#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "register.h"
#include "socket.h"

namespace Ui {
class LoginUI;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private:
    SocketConnect *socketConnect;	//Socket单例
    Register *registerUI;			//注册界面

private slots:
    void btnRegister_Slots();	//注册按钮
    void btnLogin_Slots();		//登录按钮
    void userLoginCheck_Slots(int);	//登录检查信息

private:
    Ui::LoginUI *ui;
};

#endif // LOGIN_H
