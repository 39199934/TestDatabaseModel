#include "LoginUserInfo.h"

LoginUserInfo::LoginUserInfo(QString n, QString p, QImage photo):
	BagProtocol(),
	name(n),
	password(p),
	uuid(BagProtocol::createUuid())
{
	//QByteArray ba;
	QBuffer buf(&this->photo);
	buf.open(QIODevice::WriteOnly);
	photo.save(&buf, "PNG");
	QJsonObject obj;
	obj.insert("name", name);
	obj.insert("password", password);
	obj.insert("uuid", uuid);
	auto str = QString::fromLocal8Bit(this->photo);
	obj.insert("photo", str);
	bag.setObject(obj);

}

LoginUserInfo::LoginUserInfo(QString uuid,QString n, QString p, QByteArray photo) :
	BagProtocol(),
	name(n),
	password(p),
	uuid(uuid),
	photo(photo)
{
	//QByteArray ba;
	
	QJsonObject obj;
	obj.insert("name", name);
	obj.insert("password", password);
	obj.insert("uuid", uuid);
	auto str = QString::fromLocal8Bit(this->photo);
	obj.insert("photo", str);
	bag.setObject(obj);

}

LoginUserInfo::LoginUserInfo():
	LoginUserInfo(BagProtocol::createUuid(),QString(),QString(),QByteArray())
{
}

LoginUserInfo::LoginUserInfo(const LoginUserInfo& info):
	LoginUserInfo(info.uuid,info.name,info.password,info.photo)
{
}


void LoginUserInfo::setValue()
{
	auto obj = bag.object();
	this->name = obj.value("name").toString();
	this->password = obj.value("password").toString();
	auto str = obj.value("photo").toString();
	this->photo = str.toLocal8Bit();
	this->uuid = obj.value("uuid").toString();
	this->appendToSonsValue(&obj);

}

void LoginUserInfo::setDocument()
{
	QJsonObject obj;
	obj.insert("name", name);
	obj.insert("password", password);
	obj.insert("uuid", uuid);
	auto str = QString::fromLocal8Bit(photo);
	obj.insert("photo",str);
	this->appendToSonsJson(&obj);
	bag.setObject(obj);
}

QJsonObject LoginUserInfo::appendToSonsJson(QJsonObject* obj)
{
	return *obj;
}

void LoginUserInfo::appendToSonsValue(QJsonObject* obj)
{
	return;
}
