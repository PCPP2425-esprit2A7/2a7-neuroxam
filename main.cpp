#include "mainwindow.h"
#include "connection.h"
#include <QApplication>
#include <QObject>
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

    bool restartLogin = true;
    int resultCode = 0;
    while (restartLogin) {
        restartLogin = false; // Reset flag

    // Show login dialog
    Dialog loginDialog;
        if (loginDialog.exec() == QDialog::Accepted) {
            // Login success → Show main window
            MainWindow* w = new MainWindow();

            QObject::connect(w, &MainWindow::disconnect, [&restartLogin, w]() {
                w->deleteLater();
                restartLogin = true;
            });

            w->show();
            resultCode = a.exec();

            if (!restartLogin) break;
        } else {
            // Login canceled → Exit app
            break;
        }

}
    return resultCode;
}

