#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Connection ct;
    if (!ct.createconnect()) {
        QMessageBox::critical(nullptr, QObject::tr("Database Error"),
                              QObject::tr("Connection failed.\nClick Cancel to exit."),
                              QMessageBox::Cancel);
        return 0;
    }


    MainWindow w;
    w.show();
    return a.exec();
}
