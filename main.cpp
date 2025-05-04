#include <QApplication>
#include <QMessageBox>
#include "mainwindow.h"
#include "database.h"
#include "logdialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Database db;
    if (!db.connectToDatabase()) {
        QMessageBox::critical(nullptr, "Database Connection Failed", "Could not connect to the database.");
        return 1;
    }

    bool restartLogin = true;
    int resultCode = 0;

    while (restartLogin) {
        restartLogin = false; // Reset flag

        logdialog login;
        if (login.exec() == QDialog::Accepted) {
            MainWindow* w = new MainWindow();

            // When disconnect button is clicked, we'll set restartLogin to true
            QObject::connect(w, &MainWindow::disconnected, [&restartLogin, w]() {
                w->deleteLater();
                restartLogin = true; // Reopen login dialog
            });

            w->show();
            resultCode = app.exec();

            // If app.exec() returns and restartLogin is false, it means the X button was clicked
            // In this case, we should exit the application
            if (!restartLogin) {
                break;
            }
        } else {
            // User canceled login dialog, exit the application
            break;
        }
    }

    db.closeConnection();
    return resultCode;
}
