#include "connection.h"

Connection::Connection()
{
}

bool Connection::createconnect()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("test-db"); // Ensure this matches your DSN (Data Source Name)
    db.setUserName("loay");       // Ensure this is the correct username
    db.setPassword("loay");       // Ensure this is the correct password

    if (db.open()) {
        qDebug() << "Database connected successfully!";
        return true;
    } else {
        qDebug() << "Error: " << db.lastError().text();
        return false;
    }
}

QSqlDatabase Connection::get_database()
{
    return QSqlDatabase::database(); // Return the default database connection
}
