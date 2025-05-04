#ifndef EMPLOYEWINDOW_H
#define EMPLOYEWINDOW_H

#include <QWidget>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QFileDialog>
#include <QMap>
#include "employe.h"
#include "centre/piechartwidget.h"

namespace Ui {
class employewindow;
}

class employewindow : public QWidget
{
    Q_OBJECT

public:
    explicit employewindow(QWidget *parent = nullptr);
    ~employewindow();

private slots:
    void on_ajoute_clicked();
    void on_recuperer_5_clicked();
    void on_modifier_clicked();
    void on_supprimer_clicked();
    void on_tri_clicked();
    void on_cherchebut_5_clicked();
    void on_pdf_5_clicked();
    void on_stat_5_clicked();

    // Validation functions
    void verifierNomp();
    void verifierNumeroTelephone();

private:
    Ui::employewindow *ui;
};

#endif // EMPLOYEWINDOW_H
