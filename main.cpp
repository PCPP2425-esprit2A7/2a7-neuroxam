#include "mainwindow.h"
#include "connection.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Initialiser la connexion à la base de données
    if (!Connection::createconnect()) {
        // Afficher un message d'erreur si la connexion échoue
        QMessageBox::critical(nullptr, "Erreur de connexion", "Échec de la connexion à la base de données.");
        return -1; // Quitter l'application si la connexion échoue
    }

    // Lancer la fenêtre principale de l'application
    MainWindow w;
    w.show();

    // Exécuter l'application
    return a.exec();
}
