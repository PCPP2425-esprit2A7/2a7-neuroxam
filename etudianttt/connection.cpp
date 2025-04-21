#include "connection.h"
#include <QDebug>
#include <QSqlError>

Connection::Connection()
{
}

bool Connection::createconnect()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("student"); // Ensure this matches your DSN (Data Source Name)
    db.setUserName("mahdi");       // Ensure this is the correct username
    db.setPassword("mahdi");       // Ensure this is the correct password

    if (db.open()) {
        qDebug() << "Database connected successfully!";
        return true;
    } else {
        qDebug() << "Database connection error: " << db.lastError().text();
        return false;
    }
}

QSqlDatabase Connection::getDatabase()
{
    return QSqlDatabase::database(); // Return the default database connection
}
