#pragma once

#include <QObject>
#include <QSql>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QSqlResult>
#include <iostream>
#include <QSqlTableModel>
#include <QBuffer>
#include <QWidget>
#include <QSqlQueryModel>
#include "BagProtocol.h"
#include <QVariant>

class DatabaseProtocol : public QObject
{
	Q_OBJECT

public:
	DatabaseProtocol(QString tableName,QObject *parent = nullptr);
	virtual ~DatabaseProtocol();


public:
	bool databaseIsOpen();
	int getRecordsNumber();

public:
	virtual QSqlQueryModel* getModel();

	

protected:
	QString dbHost;
	int dbPort;
	QString dbUser;
	QString dbPassword;
	QString dbName;
	QSqlDatabase db;
	QString dbTableName;

	QSqlQueryModel* model;

protected:

	

	virtual bool createTable() = 0;
	virtual bool insert(BagProtocol* bag) = 0;
	virtual bool remove(QString keyString) = 0;
	virtual bool update(BagProtocol* bag) = 0;
	//virtual QVector<QJsonObject> search(const QString& keyString) = 0;
	virtual QVector<QJsonObject> search(const QString& key, const QVariant& value);
	QSqlQuery query;

signals:
	void signalDatabaseChanged();
	void signalDatabaseHasError(QSqlError);



};
