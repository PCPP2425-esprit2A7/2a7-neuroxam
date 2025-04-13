#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>

class Connection {
public:
    Connection();
    static bool createconnect();
    static QSqlDatabase get_database();
private:
    static QSqlDatabase db;
};

#endif // CONNECTION_H
