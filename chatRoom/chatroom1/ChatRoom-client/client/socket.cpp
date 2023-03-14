#include "socket.h"
#include <QHostInfo>
#include <QDataStream>

//单例模式
SocketConnect *SocketConnect::instance = NULL;
SocketConnect *SocketConnect::GetIntance()
{
    if (instance == NULL)
    {
        instance = new SocketConnect(0);
    }
    return instance;
}

//构造函数
SocketConnect::SocketConnect(QObject *parent)
    : QTcpSocket(parent)
{
    hostAddress = new QHostAddress();	//初始化服务器地址对象

    //接收数据，时刻检测，只要Socket可读就会触发
    connect(this, SIGNAL(readyRead()), this, SLOT(dataReceived_Slot()));
}

SocketConnect::~SocketConnect()
{
}


//请求
void SocketConnect::sendRequest(RequestTypeEnum type)
{
    switch (type)
    {
    case USERLOGIN:
        sendUserLogin();
        break;
    case CHATMESSAGE:
        sendChatMessage();
        break;
    case USERREGISTER:
        sendUserRegister();
        break;
    case USEREXITHANDLE:
        sendUserExitHandle();
        break;
    default:
        break;
    }
}
//接收，emit之后，chatRoom的Socket的单例会收到信号
void SocketConnect::dataReceived_Slot()
{
    while (bytesAvailable() > 0)
    {
        bytesAvailable();
        QDataStream in(this);

        int type;
        in >> type;
        switch (type)
        {
        case USERLOGINCHECK:
            in >> statusValidate;
            emit userLoginCheck_Signals(statusValidate);
            break;
        case NOTICEALLCLIENT:
            in >> thisProgramUserName >> userEnterMsg;
            emit noticeAllClient_Signals(thisProgramUserName, userEnterMsg);
            break;
        case UPDATEALLUSER:
            in >> userAccountName >> userComputerIP;
            emit updateAllUser_Signals(userAccountName, userComputerIP);
            break;
        case USEREXIT:
            in >> userExitName >> userExitMsg;
            emit userExit_Signals(userExitName, userExitMsg);
            break;
        case CHATMESSAGE:
            in >> chatMessage_Response;
            emit chatMessage_Signals(chatMessage_Response);
            break;
        case USERREGISTER:
            in >> userAccount_Register;
            emit userRegister_Signals(userAccount_Register);
            break;
        default:
            break;
        }
    }
}

//请求登录
void SocketConnect::sendUserLogin()
{
    loginStatus = 0;
    loaclComputerName = QHostInfo::localHostName();
    loaclComputerIP = getloaclComputerIP();

    //使用QByteArray对象来暂存要发送的数据，使用 QDataStream 将要发送的数据 写入QByteArray对象中。
    QByteArray messageData;
    QDataStream out(&messageData, QIODevice::WriteOnly);
    out << USERLOGIN << loaclComputerName << loaclComputerIP << userAccount << userPassword << loginStatus;
    write(messageData);
}

//发送聊天消息
void SocketConnect::sendChatMessage()
{
    QByteArray messageData;
    QDataStream out(&messageData, QIODevice::WriteOnly);
    out << CHATMESSAGE << chatMessage_Request;
    write(messageData);
}

//请求注册
void SocketConnect::sendUserRegister()
{
    QByteArray messageData;
    QDataStream out(&messageData, QIODevice::WriteOnly);
    out << USERREGISTER << userName_Register << userPassword_Register;
    write(messageData);
}

//用户退出更新数据库处理
void SocketConnect::sendUserExitHandle()
{
    QByteArray messageData;
    QDataStream out(&messageData, QIODevice::WriteOnly);
    out << USEREXITHANDLE;
    write(messageData);
}

//本地ip地址的获取
QString SocketConnect::getloaclComputerIP()
{

    QHostInfo hostInformation = QHostInfo::fromName(loaclComputerName);
    QList<QHostAddress> clientList = hostInformation.addresses();

    QString ip;
    for (int i = 0; i < clientList.length(); i++)
    {
        qDebug() << clientList[i].toString();
        if (clientList[i].protocol() == QAbstractSocket::IPv4Protocol)
        {
            ip = clientList[i].toString();
        }
    }

    return ip;
}



