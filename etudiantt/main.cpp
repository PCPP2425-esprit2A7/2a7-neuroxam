#include "mainwindow.h"
#include "connection.h"
#include "etudiantservice.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    if (!Connection::createconnect())  // Use the new method name
        return -1;

    // Create tables if they don't exist
    EtudiantService service;
    
    MainWindow w;
    w.show();
    return a.exec();
}
