#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QTcpSocket>
#include <QListWidget>
#include <QGridLayout>
#include <QHostAddress>

class Dialog : public QDialog
{
    Q_OBJECT //这里一定要加上，使用了信号与槽函数

public:
    Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    QGridLayout *mainLayout;
    QListWidget *contentListWidget;
    QPushButton *signINBtn;
    QPushButton *signUpBtn;
    QPushButton *disconnectBtn;

    int port;
    QHostAddress *serverIP;
    QTcpSocket *tcpSocket;
public slots:
    void slotSignin();
    void slotSignup();
    void slotDisconnect();
    void dataReceived();
};

#endif // DIALOG_H
