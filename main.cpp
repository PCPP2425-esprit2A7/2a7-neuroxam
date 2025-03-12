#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include "connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;
    bool test = c.createconnect();

    if(test && QSqlDatabase::database().isOpen()) {
        MainWindow w;
        w.show();
        QMessageBox::information(nullptr, QObject::tr("Database Connection"),
                                 QObject::tr("Connection successful.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
        return a.exec();
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Database Connection"),
                              QObject::tr("Connection failed.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        return -1;
    }
}
