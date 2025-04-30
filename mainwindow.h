#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "examen.h"
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
    void on_sup_clicked();
    void on_recuperer_clicked();
    void on_tri_clicked();
    void on_cherchebut_clicked();
    void on_pdf_clicked();
    void on_stat_clicked();
    void on_btn_ouvrirEmailDialog_clicked();
    void mettreAJourCalendrier();
     void on_calendar_examen_clicked(const QDate &date);
private:
    Ui::MainWindow *ui;
    examen e;

};

#endif // MAINWINDOW_H
