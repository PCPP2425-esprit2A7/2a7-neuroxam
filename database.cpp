#include "database.h"

bool Database::connectToDatabase()
{
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("test-db");
    db.setUserName("loay");
    db.setPassword("loay");
    if (db.open()) {
        qDebug() << "Connected to Oracle successfully!";
        return true;
    } else {
        qDebug() << "Connection failed: " << db.lastError().text();
        return false;
    }
}

void Database::closeConnection()
{
    if (db.isOpen()) {
        db.close();
        qDebug() << "Database connection closed.";
    }
}

QSqlDatabase Database::getDatabase() const
{
    return db;
}
