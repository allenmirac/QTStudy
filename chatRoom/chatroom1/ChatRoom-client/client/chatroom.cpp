#include "chatroom.h"
#include "ui_chatroom.h"
#include <QMessageBox>
#include <QKeyEvent>

ChatRoom::ChatRoom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatRoomUI)
{
    ui->setupUi(this);

    //获取Socket的单例
    chatRoom = SocketConnect::GetIntance();
    connect(chatRoom, SIGNAL(noticeAllClient_Signals(QString, QString)), this, SLOT(noticeAllClient_Slots(QString, QString)));
    connect(chatRoom, SIGNAL(updateAllUser_Signals(QString, QString)), this, SLOT(updateAllUser_Slots(QString, QString)));
    connect(chatRoom, SIGNAL(userExit_Signals(QString, QString)), this, SLOT(userExit_Slots(QString, QString)));

    ui->sendLineEdit->setFocusPolicy(Qt::StrongFocus);
    ui->sendLineEdit->setFocus();
    ui->sendLineEdit->installEventFilter(this);  //设置完后自动调用其eventFilter函数
    connect(ui->sendBtn, SIGNAL(clicked()), this, SLOT(sendMessageBtn_Slots()));						//发送消息
    connect(chatRoom, SIGNAL(chatMessage_Signals(QString)), this, SLOT(chatMessage_Slots(QString)));//聊天消息
}

ChatRoom::~ChatRoom()
{
    delete ui;
}

//接收服务器传来的登录到聊天室信息的槽函数
void ChatRoom::noticeAllClient_Slots(QString thisProgramUserName, QString userEnterMsg)
{
    if (userNameSwitch)
    {
        //设置名字
        ui->clientName->setText(thisProgramUserName);
        userNameSwitch = 0;
    }
    //用户进入聊天室信息
    ui->listWidget->setTextColor(Qt::blue);
    ui->listWidget->append(userEnterMsg);
}

//接收服务器更新的所有在线用户信息的槽函数
void ChatRoom::updateAllUser_Slots(QString userAccountName, QString userComputerIP)
{
    bool isEmpty = ui->tableWidget->findItems(userAccountName, Qt::MatchExactly).isEmpty();
    if (isEmpty)
    {
        QTableWidgetItem* updata_n = new QTableWidgetItem(userAccountName);
        QTableWidgetItem* updata_i = new QTableWidgetItem(userComputerIP);
        ui->tableWidget->insertRow(0);
        ui->tableWidget->setItem(0, 0, updata_n);
        ui->tableWidget->setItem(0, 1, updata_i);

        //更新在线用户数
        ui->onlineNumber->setText(QString("%1").arg(ui->tableWidget->rowCount()));
    }
}

//接收服务器传来的聊天消息的槽函数
void ChatRoom::chatMessage_Slots(QString message)
{
    ui->listWidget->setTextColor(Qt::black);
    ui->listWidget->append(message);
}


//发送消息
void ChatRoom::sendMessageBtn_Slots()
{
    if (ui->sendLineEdit->toPlainText() == "")
    {
        QMessageBox::information(this, "ERROR", "请输入内容！");
        return;
    }

    if (chatRoom->waitForConnected())
    {
        //发送聊天消息
        chatRoom->chatMessage_Request = ui->sendLineEdit->toPlainText();
        chatRoom->sendRequest(RequestTypeEnum::CHATMESSAGE);
    }

    ui->sendLineEdit->clear();
    ui->sendLineEdit->setFocus();
}

//关闭窗口重写函数
void ChatRoom::closeEvent(QCloseEvent * event)
{
    if (chatRoom->waitForConnected())
    {
        //用户退出处理-----修改数据库数据
        chatRoom->sendRequest(RequestTypeEnum::USEREXITHANDLE);
    }
    QMessageBox::information(this, "information", "退出成功！");
    chatRoom->disconnectFromHost();
}

//接收服务器把数据库数据修改后传给客户端的信息
void ChatRoom::userExit_Slots(QString userExitName, QString userExitMsg)
{
    //用户离开聊天室信息
    ui->listWidget->setTextColor(Qt::gray);
    ui->listWidget->append(userExitMsg);
    ui->listWidget->setTextColor(Qt::black);

    //用户表格信息删除
    int row = ui->tableWidget->findItems(userExitName, Qt::MatchExactly).first()->row();
    ui->tableWidget->removeRow(row);

    //更新在线用户数
    ui->onlineNumber->setText(QString("%1").arg(ui->tableWidget->rowCount()));
}


//回车按钮事件
bool ChatRoom::eventFilter(QObject *target, QEvent *event)
{
    if (target == ui->sendLineEdit)
    {
        if (event->type() == QEvent::KeyPress)	//回车键
        {
            QKeyEvent *k = static_cast<QKeyEvent *>(event);
            if (k->key() == Qt::Key_Return)
            {
                if (ui->sendBtn->isEnabled())
                {
                    sendMessageBtn_Slots();
                    return true;
                }

            }
        }
    }
    return QWidget::eventFilter(target, event);
}
