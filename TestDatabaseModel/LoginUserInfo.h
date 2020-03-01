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
	virtual void setValue() ;////��Ҫ�̳У����ڴ�doc��ת��Ϊ�����е�value���� �ڻ����е���
	virtual void setDocument();///��Ҫ�̳У����ڴ�value��ת��Ϊ�����е�doc����


	virtual QJsonObject appendToSonsJson(QJsonObject* obj); //��������̳У������ڸ����е��ã���Ӹ��Ի�������
	virtual void appendToSonsValue(QJsonObject* obj) ; //��������̳У������ڸ����е��ã���Ӹ��Ի�������
};

