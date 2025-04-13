#include <QApplication>
#include "mainwindow.h"
#include "database.h"
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Database db;
    if (!db.connectToDatabase()) {
        QMessageBox::critical(nullptr, "Database Connection Failed", "Could not connect to the database.");
        return 1;
    }

    MainWindow w;
    w.show();

    int result = app.exec();

    db.closeConnection();
    return result;
}
