#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class Connection
{
public:
    Connection();
    static bool createconnect();
    static QSqlDatabase getDatabase();
};

#endif // CONNECTION_H
