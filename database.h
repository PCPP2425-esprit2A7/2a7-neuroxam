#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>

class Database
{
public:
    bool connectToDatabase();
    void closeConnection();
    QSqlDatabase getDatabase() const;


private:
    QSqlDatabase db;
};

#endif // DATABASE_H
