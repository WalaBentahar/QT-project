#include "connection.h"
#include <QDebug>

connection::connection()
{
}

bool connection::createconnect()
{
    bool test = false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("wala");
    db.setUserName("wala");
    db.setPassword("wala");

    if (db.open())
    {
        test = true;
    }
    else
    {
        qDebug() << "Error: " << db.lastError().text();
    }

    return test;
}
