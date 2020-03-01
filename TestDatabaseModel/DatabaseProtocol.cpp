#include "DatabaseProtocol.h"

DatabaseProtocol::DatabaseProtocol(QString tableName, QObject *parent)
	: QObject(parent),
	dbHost("192.168.31.101"),
	dbUser("root"),
	dbPassword("lode801103?"),
	dbPort(23306),
	dbName("chatSql"),
	db(QSqlDatabase::addDatabase("QMYSQL")),
	dbTableName(tableName),
	model(nullptr)
{
	db.setHostName(dbHost);
	db.setPassword(dbPassword);
	db.setPort(dbPort);
	db.setUserName(dbUser);
	db.setDatabaseName(dbName);
	db.open();
	
	query = QSqlQuery(db);
}

DatabaseProtocol::~DatabaseProtocol()
{
	db.close();
	if (model != nullptr) {
		model->deleteLater();
		model = nullptr;
	}
}

bool DatabaseProtocol::databaseIsOpen()
{
	return db.isOpen();
}

int DatabaseProtocol::getRecordsNumber()
{

	
	query.exec("select * from " + dbTableName);

	return query.numRowsAffected();
}

QSqlQueryModel* DatabaseProtocol::getModel()
{
	if (model == nullptr) {
		model = new QSqlQueryModel(this);
	}
	model->setQuery("select * from " + dbTableName);


	return model;
}


QVector<QJsonObject> DatabaseProtocol::search(const QString& key, const QVariant& value)
{
	auto result = QVector<QJsonObject>();
	query.exec("desc `" + dbTableName + "`;");
	QVector<QString> keys;
	while (query.next()) {
		keys.push_back(query.value("Field").toString());
	}

	query.prepare("select * FROM `" + dbTableName +"` WHERE `" +key +"` = :value ");
	//query.bindValue(":table", dbTableName);
	//query.bindValue(":key", key);
	query.bindValue(":value", value);
	query.exec();
	while (query.next()) {
		QJsonObject obj;
		for (int i = 0; i < keys.count(); i++) {
			obj.insert(keys[i], query.value(i).toString());
		}
		result.push_back(obj);
		
	}
	return result;
}
