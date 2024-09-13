//#include "signup.h"
#include "login.h"
#include <QApplication>
#include<QDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug () << "start";

    QSqlDatabase db;
    db =QSqlDatabase :: addDatabase ("QSQLITE");
    db.setDatabaseName("C:/sqlite/db.sqlite");

    if(!db.open ()){

        qDebug() << "problem opening database";
    }
    qDebug() << "end";
    QString query="CREATE TABLE IF NOT EXISTS user("
                    " USERID INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "PHONENUMBER INTEGER NOT NULL,"
                    "PIN INTEGER NOT NULL,"
                    "location_from TEXT,"
                    "location_to TEXT,"
                    "status TEXT DEFAULT 'on hold');";

    QSqlQuery qry;
    if(!qry.exec (query))
    {
        qDebug () << "error creating table";
    }
    db.close();
    qDebug () << "end";
    qDebug () << "start";

    QSqlDatabase db1;
    db1 =QSqlDatabase :: addDatabase ("QSQLITE");
    db1.setDatabaseName("C:/sqlite/db.sqlite");

    if(!db1.open ()){

        qDebug() << "problem opening database";
    }
    qDebug() << "end";
    QString query1="CREATE TABLE IF NOT EXISTS rider("
                     " RIDERID INTEGER PRIMARY KEY AUTOINCREMENT,"
                     "PHONENUMBER INTEGER NOT NULL,"
                     "PIN INTEGER NOT NULL);";

    QSqlQuery qry1;
    if(!qry1.exec (query1))
    {
        qDebug () << "error creating table";
    }
    db1.close();
    QSqlQuery qry3;
    QSqlDatabase db3;

    db3 =QSqlDatabase :: addDatabase ("QSQLITE");
    db3.setDatabaseName("C:/sqlite/db.sqlite");

    if(!db3.open ()){

        qDebug() << "problem opening database";

        qDebug() << "end";
    }
    QString query3="CREATE TABLE IF NOT EXISTS message ("
                     "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                     "phonenumber TEXT, "
                     "message TEXT, "
                     "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP"
                     ");";

    if(!qry3.exec (query3))
    {

        qDebug () << "error creating table";
    }
    db3.close();
    QSqlQuery qry4;
    QSqlDatabase db4;
    db4 =QSqlDatabase :: addDatabase ("QSQLITE");
    db4.setDatabaseName("C:/sqlite/db.sqlite");
    if(!db4.open ()){

        qDebug() << "problem opening database";

        qDebug() << "end";
    }
    QString query4="CREATE TABLE IF NOT EXISTS messagesRider ("
                     "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                     "phonenumber TEXT, "
                     "message TEXT, "
                     "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP"
                     ");";

    if(!qry4.exec (query4))
    {

        //qDebug () << "error creating table";
    }
    qDebug () << "end";
    //signup w;
    login z;
   // w.show();
    z.show();
    return a.exec();

}
