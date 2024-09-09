#include "Connection.h"
#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Connection conn;
    if (!conn.createConnection()) {
        qDebug() << "Failed to connect to the database.";
        return -1; // Exit the application if the database connection fails
    }

    MainWindow w;
    w.show();

    return a.exec();
}
