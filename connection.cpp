#include "connection.h"
#include <QDebug>
#include <QSqlError>

Connection::Connection()
{
}

bool Connection::createconnect()
{
    bool test = false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("test-db"); // Nom de la source de données
    db.setUserName("loay"); // Nom d'utilisateur
    db.setPassword("loay"); // Mot de passe

    if (db.open()) {
        qDebug() << "Database opened successfully";
        test = true;
    } else {
        qDebug() << "Failed to open database:" << db.lastError().text();
    }

    return test;
}

bool Connection::checkConnection()
{
    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "Database connection lost, attempting to reconnect...";
        return QSqlDatabase::database().open();
    }
    return true;
}
