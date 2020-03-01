#include "TestDatabaseModel.h"

TestDatabaseModel::TestDatabaseModel(QWidget *parent)
	: QMainWindow(parent),
	regist(new RegistDatabase(this))
{
	ui.setupUi(this);
	auto model = regist->getModel();
	ui.tableView->setModel(model);
	//model->select();
	connect(ui.cBtnInsert, &QPushButton::clicked, this, &TestDatabaseModel::slotClickedInsert);
	connect(regist, &RegistDatabase::signalRegistHasError, this, &TestDatabaseModel::slotRegistHasError);
}

TestDatabaseModel::~TestDatabaseModel()
{
	if (regist != nullptr) {
		regist->deleteLater();
		regist = nullptr;
	}
}

void TestDatabaseModel::slotRegistHasError(QString error)
{
	QMessageBox::warning(this, "´íÎó", error);
}

void TestDatabaseModel::slotClickedInsert()
{
	auto user = LoginUserInfo("ro", "lodestar");
	auto users = regist->searchUser("ro");
	if (!users.isEmpty()) {
		
	}
	regist->appendUser(user);

	auto rt = regist->searchUser("ro");
	for (auto i = 0; i < rt.count(); i++) {
		qDebug() << rt[i].toObject() << endl;
	}
	//qDebug() << rt;
}
