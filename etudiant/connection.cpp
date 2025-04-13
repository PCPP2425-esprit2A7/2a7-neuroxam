#include "connection.h"
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>
#include <QApplication>

QSqlDatabase Connection::db;

Connection::Connection() {}
bool Connection::createconnect() {
    // Check if QODBC driver is available
    if (!QSqlDatabase::isDriverAvailable("QODBC")) {
        QMessageBox::critical(nullptr, "Driver Error",
                              "QODBC driver not available. Please ensure:\n"
                              "1. Qt is built with ODBC support\n"
                              "2. Oracle ODBC driver is installed");
        return false;
    }

    db = QSqlDatabase::addDatabase("QODBC");

    // Try both DSN and DSN-less connection approaches
    QString connectString =
        "Driver={Oracle ODBC Driver};"  // Use your actual driver name
        "DBQ=XE;"                      // Oracle SID
        "UID=system;"
        "PWD=123456789;";

    db.setDatabaseName(connectString);

    if (!db.open()) {
        QString errorMsg = db.lastError().text();
        qDebug() << "Database Error:" << errorMsg;

        QMessageBox::critical(nullptr, "Connection Failed",
                              QString("Failed to connect to Oracle:\n%1\n\n"
                                      "Troubleshooting:\n"
                                      "1. Verify Oracle service (XE) is running\n"
                                      "2. Check Oracle listener status\n"
                                      "3. Confirm ODBC driver is installed\n"
                                      "4. Test connection in ODBC Administrator").arg(errorMsg));
        return false;
    }

    qDebug() << "Connected to Oracle database successfully";
    return true;
}
