#include "mysql.h"
#include <QImage>
#include <QPixmap>

MySql::MySql():
    hostName("192.168.31.101"),
    dbName("test"),
    userName("root"),
    password("lode801103?"),
    port(23306),
    model(new QSqlQueryModel())
{
    qDebug()<<QSqlDatabase::drivers();
    dbConn = QSqlDatabase::addDatabase(("QMYSQL"));
    dbConn.setHostName(hostName);
    dbConn.setDatabaseName(dbName);
    dbConn.setUserName(userName);
    dbConn.setPassword(password);
    dbConn.setPort(port);
    qDebug()<<"database open status:"<<dbConn.open();
    QSqlError error = dbConn.lastError();
    qDebug()<<error.text();
    //dbConn.close();
   // model->setTable("test");


}

MySql::~MySql()
{
    dbConn.close();
    if (model!=nullptr) {
        delete model;
    }
}

void MySql::viewTable()
{
    QSqlQuery sq(dbConn);
    auto rt = sq.exec("show fields from t2;");
    //auto result = sq.result();
    auto filedsNumber = sq.size();
    for (int i = 0; i < sq.size(); i++) {
        sq.seek(i);
        auto v = sq.value(0).toString();
        cout<<sq.value(0).toString().toStdString()<<"\t";

    }
    cout << endl;
    sq.prepare("select * from t2");
    qDebug()<<"exec result:"<<sq.exec();
    //dbConn.
    while (sq.next()) {
        for (int i = 0; i < filedsNumber; i++)
        {
            if (i == 3) {
                auto v = sq.value(i).toByteArray();
                QBuffer buf(&v);
                buf.open(QIODevice::ReadOnly);
                QImage img;
                img.load(&buf, "PNG");
                img.save("d:\\test.jpg");
                /*if (show != nullptr) {
                    delete show;
                }
                show = new ShowImage(img);
                show->show();*/
               /* QString vb = QString::fromUtf8(v);
                qDebug() << vb;
                cout << v.toStdString() << "\t";
                continue;*/
            }
            auto va = sq.value(i);
            if (va.isNull()) {
                qDebug() << "NULL";
            }
            else {
                qDebug() << va.toString();
            }
           // auto v = sq.value(i).toString();
            //qDebug() << v;
           // cout << v.toStdString() << "\t";
        }
        cout << endl;
    }

}

void MySql::insert()
{
    auto imag = QImage();// QImage("d:\\1.jpg");
    QByteArray ba;
    QBuffer buf(&ba);
    buf.open(QIODevice::WriteOnly);
    imag.save(&buf,"PNG");
   
    QSqlQuery sq(dbConn);
    sq.exec("select * from t2");
    auto nr = sq.numRowsAffected();
    sq.prepare("insert into t2 (`name`,`id`,`login`,`bytes`) "
        "values( :name ,:id,:login,:bytes)");
    QString n = QString::number(nr + 1);
    n += QString::fromLocal8Bit("nameÁãÆßµçÄÔ");
    sq.bindValue(":name", n);
    sq.bindValue(":id", nr);
    sq.bindValue(":login", true);
    qDebug() << ba.size();
    sq.bindValue(":bytes", QVariant(ba));
    sq.exec();
    qDebug() << "effict rows:" << sq.numRowsAffected();
    qDebug() << "last error:" << sq.lastError();
    viewTable();
}

QSqlQueryModel* MySql::getModel()
{
    if (model) {
        delete model;
    }
    auto model = new QSqlTableModel();
    model->setTable("test");
    model->select();
    //model->setQuery(QString("select name,id from test;"));
    auto str = QString::fromLocal8Bit("ÐÕÃû");
    model->setHeaderData(0, Qt::Horizontal, str);
    return model;
}

