#ifndef EXAMENWINDOW_H
#define EXAMENWINDOW_H

#include "examen.h"
#include <QWidget>


namespace Ui {
class examenwindow;
}

class examenwindow : public QWidget
{
    Q_OBJECT

public:
    examenwindow(QWidget *parent = nullptr);
    ~examenwindow();

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

private:
    Ui::examenwindow *ui;
    examen e;

};

#endif // EXAMENWINDOW_H
