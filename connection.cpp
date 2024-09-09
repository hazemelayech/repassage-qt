#include "Connection.h"

Connection::Connection() {}

bool Connection::createConnection()
{
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("gestiondespace"); // Insert the name of the ODBC data source
    db.setUserName("hazem");              // Insert the user name
    db.setPassword("12");              // Insert the password

    if (!db.open()) {
        qDebug() << "Database connection failed: " << db.lastError().text();
        return false;
    }

    qDebug() << "Database connection successful.";
    return true;
}

void Connection::closeConnection() {
    if (db.isOpen()) {
        db.close();
        qDebug() << "Database connection closed.";
    }
}
