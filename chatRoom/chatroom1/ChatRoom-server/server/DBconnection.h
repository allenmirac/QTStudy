#pragma once

#include <QtSql>
#include <QDebug>

//�������ݿ�
static bool createConnection()
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName("localhost");
	db.setPort(3306);
	db.setUserName("root");
	db.setPassword("123456");
	db.setDatabaseName("chatroom");
	bool ok = db.open();
	db.exec("SET NAMES 'GBK'");
	if (!ok)
	{
        qDebug()<<"false"<<endl;
		return false;
	}
	else
	{
        qDebug()<<"true"<<endl;
		return true;
	}
}


