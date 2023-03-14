#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
#include <QtNetwork>
#include "socket.h"

namespace Ui {
class RegisterUI;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = 0);
    ~Register();

private:
    SocketConnect *socketConnect;	//Socket单例

private slots:
    void btnOK_Slots();			//确定按钮
    void btnCancel_Slots();		//取消按钮
    void userRegister_Slots(QString);	//接收账号槽函数

private:
    Ui::RegisterUI *ui;
};

#endif // REGISTER_H
