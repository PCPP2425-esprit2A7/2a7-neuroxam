#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"employe.h"
#include <QMainWindow>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_ajoute_clicked();

    void on_modifier_clicked();

    void on_supprimer_clicked();

    void on_recuperer_clicked();

    void verifierNom();

    void verifierNumeroTelephone();


private:
    Ui::MainWindow *ui;
      employe e;
};
#endif // MAINWINDOW_H
