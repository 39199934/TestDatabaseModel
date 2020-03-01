#pragma once
#include "BagProtocol.h"
#include <QImage>
#include <QBuffer>
#include <QByteArray>
#include <QtCore>
class LoginUserInfo :
	public BagProtocol
{

public:
	QString name;
	QString password;
	QByteArray photo;
	QString uuid;
public:
	LoginUserInfo(QString n, QString p, QImage photo = QImage());
	LoginUserInfo(QString uuid,QString n, QString p, QByteArray photo );
	LoginUserInfo();
	LoginUserInfo(const LoginUserInfo& info);

protected:
	virtual void setValue() ;////需要继承，用于从doc中转换为本类中的value数据 在基类中调用
	virtual void setDocument();///需要继承，用于从value中转换为本类中的doc数据


	virtual QJsonObject appendToSonsJson(QJsonObject* obj); //用于子类继承，用于在父类中调用，添加个性化的数据
	virtual void appendToSonsValue(QJsonObject* obj) ; //用于子类继承，用于在父类中调用，添加个性化的数据
};

