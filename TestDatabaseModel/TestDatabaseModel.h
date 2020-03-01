#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TestDatabaseModel.h"
#include "mysql.h"
#include "RegistDatabase.h"
#include "LoginUserInfo.h"
#include <QMessageBox>

class TestDatabaseModel : public QMainWindow
{
	Q_OBJECT

public:
	TestDatabaseModel(QWidget *parent = Q_NULLPTR);
	~TestDatabaseModel();

private:
	Ui::TestDatabaseModelClass ui;
	MySql sql;
	RegistDatabase* regist;
public slots:

	void slotClickedInsert();
	void slotRegistHasError(QString error);
};
