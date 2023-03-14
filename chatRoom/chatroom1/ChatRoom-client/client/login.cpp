#include "login.h"
#include <QMessageBox>
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginUI)
{
    ui->setupUi(this);

    socketConnect = SocketConnect::GetIntance(); //获取Socket的单例
    socketConnect->port = 8030;			//设置端口号
    socketConnect->serverIP = "0.0.0.0";//初始化服务器ip地址
    ui->portLabel->setText(QString::number(socketConnect->port));
    ui->loginBtn->setFocus();


    connect(ui->registerBtn, SIGNAL(clicked()), this, SLOT(btnRegister_Slots()));			//注册按钮
    connect(ui->loginBtn, SIGNAL(clicked()), this, SLOT(btnLogin_Slots()));					//登录按钮
    connect(socketConnect, SIGNAL(userLoginCheck_Signals(int)), this, SLOT(userLoginCheck_Slots(int)));	//接收登录检查信息
}

Login::~Login()
{
    delete ui;
}

//注册按钮
void Login::btnRegister_Slots()
{
    //获取服务器ip地址
    socketConnect->serverIP = ui->serverIPLineEdit->text();

    registerUI = new Register(this);
    int ok = registerUI->exec();
}

//登录按钮
void Login::btnLogin_Slots()
{
    //获取服务器ip地址
    socketConnect->serverIP = ui->serverIPLineEdit->text();

    if (ui->accountLineEdit->text().isEmpty() || ui->passwordLineEdit->text().isEmpty())
    {
        QMessageBox::information(this, "提示", "请输入账号或密码！！");
        return;
    }
    if (ui->serverIPLineEdit->text().isEmpty())
    {
        QMessageBox::information(this, "提示", "请输入 ip 地址");
        return;
    }

    //获取账号、密码
    socketConnect->userAccount = ui->accountLineEdit->text();
    socketConnect->userPassword = ui->passwordLineEdit->text();

    //连接服务器并发送数据给服务器
    if (!socketConnect->hostAddress->setAddress(socketConnect->serverIP))
    {
        return;
    }
    socketConnect->connectToHost(*socketConnect->hostAddress, socketConnect->port);
    if (socketConnect->waitForConnected())
    {
        socketConnect->sendRequest(RequestTypeEnum::USERLOGIN);
    }
    else
    {
        QMessageBox::information(this, "提示", "连接服务器失败！");
        ui->loginBtn->setFocus();
        return;
    }
}

//登录检查信息
void Login::userLoginCheck_Slots(int ok)
{
    if (ok == 1)
    {
        qDebug() << QString::fromLocal8Bit("登录成功");
        accept();
    }
    else if (ok == 2)
    {
        QMessageBox::information(this, "提示", "你已登录，请关闭程序后再登录！");
        socketConnect->disconnectFromHost();
    }
    else
    {
        QMessageBox::information(this, "提示", "用户名或密码错误！");
        socketConnect->disconnectFromHost();
    }
}
