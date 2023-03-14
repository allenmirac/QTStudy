#include "register.h"
#include "ui_register.h"
#include <QMessageBox>

Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterUI)
{
    ui->setupUi(this);

    socketConnect = SocketConnect::GetIntance(); //获取Socket的单例

    connect(ui->btn_OK, SIGNAL(clicked()), this, SLOT(btnOK_Slots()));			//确定按钮
    connect(ui->btn_Cancel, SIGNAL(clicked()), this, SLOT(btnCancel_Slots()));	//取消按钮
    connect(socketConnect, SIGNAL(userRegister_Signals(QString)),
            this, SLOT(userRegister_Slots(QString)));	//接收账号槽函数
}

Register::~Register()
{
    delete ui;
}

//确定按钮
void Register::btnOK_Slots()
{
    //检查输入是否为空
    if (ui->name_R->text().isEmpty() || ui->password_R->text().isEmpty())
    {
        QMessageBox::information(this, "提示", "请输入名字或密码");
        return;
    }

    //取得账号和密码
    QString username = ui->name_R->text();
    QString password = ui->password_R->text();

    //检查两次密码是否相同
    if (password == ui->passwordSure_R->text())
    {
        socketConnect->userName_Register = username;
        socketConnect->userPassword_Register = password;

        //连接服务器并发送数据给服务器
        if (!socketConnect->hostAddress->setAddress(socketConnect->serverIP))
        {
            return;
        }
        socketConnect->connectToHost(*socketConnect->hostAddress, socketConnect->port);
        if (socketConnect->waitForConnected())
        {
            socketConnect->sendRequest(RequestTypeEnum::USERREGISTER);
        }
        else
        {
            QMessageBox::information(this, "提示", "连接服务器失败！");
            return;
        }
    }
    else
    {
        QMessageBox::information(this, "提示", "两次输入的密码不正确！");
        return;
    }
}

//取消按钮
void Register::btnCancel_Slots()
{
    this->reject();
}

//接收账号槽函数
void Register::userRegister_Slots(QString account)
{
    QMessageBox::information(this, "注册成功！", "注册成功！你的账号为：\n" + account);
    socketConnect->disconnectFromHost();
    this->accept();
}
