#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

class Connection
{
    QSqlDatabase db;
public:
    Connection();
    bool createConnection();
    void closeConnection();
};

#endif // CONNECTION_H
