#ifndef SOCKET_H
#define SOCKET_H

#include <QTcpSocket>
#include <QHostAddress>

enum RequestTypeEnum
{
    USERLOGIN, USERLOGINCHECK, UPDATEALLUSER, NOTICEALLCLIENT, USEREXITHANDLE, USEREXIT, CHATMESSAGE, USERREGISTER
};

class SocketConnect : public QTcpSocket
{
    Q_OBJECT

//单例模式
public:
    static SocketConnect *GetIntance();
private:
    static SocketConnect *instance;

public:
    //登录到服务器所需的信息
    int port;			//端口号
    QString serverIP;	//服务器ip地址
    QHostAddress *hostAddress;		//服务器地址对象

    //发送到服务器的信息
    //登录功能
    QString loaclComputerName;	//电脑名
    QString loaclComputerIP;	//ip地址
    QString userAccount;		//账号
    QString userPassword;		//密码
    int loginStatus;			//登录状态
    //聊天功能
    QString chatMessage_Request;	//要发送聊天信息
    QString chatMessage_Response;	//接收到的聊天消息
    //注册功能
    QString userName_Register;		//注册用户的名字
    QString userPassword_Register;	//注册用户的密码
    QString userAccount_Register;	//注册到用户的账号


    //接收服务器的响应信息
    int statusValidate;	//登录验证的状态：0--验证失败；1--验证成功；2--用户已登录

    QString thisProgramUserName;	//此程序的用户的唯一名字

    QString userEnterMsg;	//进入聊天室的消息
    QString userAccountName;//其他用户名字
    QString userComputerIP;	//其他用户ip地址

    QString userExitName;	//用户退出名字
    QString userExitMsg;	//用户退出消息

private:
    QString getloaclComputerIP();	//本地ip地址的获取

public:
    void sendRequest(RequestTypeEnum);	//发送请求
    void sendUserLogin();		//请求登录
    void sendChatMessage();		//发送聊天消息
    void sendUserRegister();	//请求注册
    void sendUserExitHandle();	//用户退出更新数据库处理

private slots:
    void dataReceived_Slot();	//数据来到的发出的 readyRead() 信号
signals:
    void userLoginCheck_Signals(int);				//登录验证的状态：0--验证失败；1--验证成功；2--用户已登录
signals:
    void noticeAllClient_Signals(QString, QString);	//有新用户进来时进行通知所有用户
signals:
    void updateAllUser_Signals(QString, QString);	//更新在线用户
signals:
    void userExit_Signals(QString, QString);	//退出信息
signals:
    void chatMessage_Signals(QString);	//聊天消息
signals:
    void userRegister_Signals(QString);	//用户注册


public:
    SocketConnect(QObject *parent);
    ~SocketConnect();
};

#endif // SOCKET_H
