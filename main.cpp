#include "mainwindow.h"
#include "connection.h"
#include <QApplication>
#include <QMessageBox>
#include "logdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Initialize the database connection
    if (!Connection::createconnect()) {
        qDebug() << "Failed to connect to the database!";
        return -1;
    }

    // Show login dialog
    Dialog loginDialog;
    if (loginDialog.exec() != QDialog::Accepted) {
        return 0; // Exit if login fails
    }

    // MainWindow must persist (declare it before exec())
    MainWindow *w = new MainWindow(); // Allocate on heap to prevent destruction
    w->show();

    // Debug output to verify window creation
    qDebug() << "MainWindow created and shown";

    return a.exec(); // Start the event loop (keeps app alive)
}
