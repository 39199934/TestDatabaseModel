#include "RegistDatabase.h"

RegistDatabase::RegistDatabase(QObject *parent)
	: DatabaseProtocol("registUser",parent)
{
	if (!db.tables().contains(dbTableName)) {
		this->createTable();
	}

	//CREATE TABLE `chatSql`.`login`( `uuid` CHAR(36) NOT NULL, `name` CHAR(20) NOT NULL, `password` CHAR(20) NOT NULL, `photo` LONGBLOB, PRIMARY KEY (`uuid`) ) CHARSET=utf8;
}

RegistDatabase::~RegistDatabase()
{
}

bool RegistDatabase::appendUser( LoginUserInfo& user)
{
	auto users = searchUser(user.name);
	if (!users.isEmpty()) {
		emit signalRegistHasError(QString::fromLocal8Bit("对不起，数据库存在相同的用户名"));
		return false;
	}
	return insert(&user);
	//return false;
}

bool RegistDatabase::removeUser(QString uuid)
{
	return remove(uuid);
	//return false;
}

QVector<LoginUserInfo> RegistDatabase::searchUser(QString name)
{
	auto result = QVector<LoginUserInfo>();
	auto rt = search("name", name);
	for (int i = 0; i < rt.count(); i++) {
		LoginUserInfo user;
		user.fromJson(rt[i]);
		result.push_back(user);
	}
	return result;

}

bool RegistDatabase::createTable()
{
	query.prepare("CREATE TABLE `"+ dbTableName +"` ( `uuid` CHAR(40) NOT NULL, `name` CHAR(20) NOT NULL, `password` CHAR(20) NOT NULL, `photo` LONGBLOB, PRIMARY KEY (`uuid`) ) CHARSET=utf8;");
	
	//query.prepare("CREATE TABLE `:tableName` ( `uuid` CHAR(36) NOT NULL, `name` CHAR(20) NOT NULL, `password` CHAR(20) NOT NULL, `photo` LONGBLOB, PRIMARY KEY (`uuid`) ) CHARSET=utf8;");
	//query.bindValue(":tableName", dbTableName);
	auto rt = query.exec();
	qDebug() << "error:" << query.lastError();
	return rt;
	//return false;
}

bool RegistDatabase::insert(BagProtocol* bag)
{
	qDebug() << "database is open:" << databaseIsOpen();
	auto u = static_cast<LoginUserInfo*>(bag);
	query.prepare("insert into `" + dbTableName + "` (`uuid`,`name`,`password`,`photo`) "
					"values(:uuid,:name,:password,:photo)");
	//query.bindValue(":table", dbTableName);
	query.bindValue(":uuid", u->uuid);
	query.bindValue(":name", u->name);
	query.bindValue(":password", u->password);
	query.bindValue(":photo", QVariant( u->photo));
	emit signalDatabaseChanged();
	auto rt = query.exec();
	qDebug() << "sql:" << query.executedQuery() << ",the affect number:" << query.numRowsAffected();
	qDebug() << "error:" << query.lastError();
	if (query.lastError().isValid()) {
		emit signalDatabaseHasError(query.lastError());
	}
	
	return rt;
}

bool RegistDatabase::remove(QString keyString)
{
	//auto u = static_cast<LoginUserInfo*>(bag);
	query.prepare("DELETE FROM :table WHERE `uuid` = ':uuid' ");
	query.bindValue(":table", dbTableName);
	query.bindValue(":uuid", keyString);
	emit signalDatabaseChanged();
	return query.exec();
}

bool RegistDatabase::update(BagProtocol* bag)
{
	emit signalDatabaseChanged();
	return false;
}
/*
QVector<QJsonObject> RegistDatabase::search(const QString& keyString)
{
	auto result = QVector<QJsonObject>();
	query.prepare("select * FROM :table WHERE `uuid` = ':uuid' ");
	query.bindValue(":table", dbTableName);
	query.bindValue(":uuid", keyString);
	while (query.next()) {
		auto uuid = query.value("uuid").toString();
		auto name = query.value("name").toString();
		auto pass = query.value("password").toString();
		auto photo = query.value("photo").toByteArray();
		auto lu = LoginUserIsnfo(uuid, name, pass, photo);
		result.push_back(lu.toObject());
	}
	return result;
}*/
