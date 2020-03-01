#pragma once

#include <QObject>
#include "BagProtocol.h"
#include "DatabaseProtocol.h"
#include "LoginUserInfo.h"
class RegistDatabase :public DatabaseProtocol
{
	Q_OBJECT

public:
	RegistDatabase(QObject *parent);
	~RegistDatabase();

	bool appendUser( LoginUserInfo& user);
	bool removeUser(QString uuid);
	
	QVector<LoginUserInfo> searchUser(QString name);
	

protected:
	virtual bool createTable() override;
	virtual bool insert(BagProtocol* bag) override;
	virtual bool remove(QString keyString) override;
	virtual bool update(BagProtocol* bag) override;
	//virtual QVector<QJsonObject> search(const QString& keyString) override;
	
signals:
	void signalRegistHasError(QString error);



};
