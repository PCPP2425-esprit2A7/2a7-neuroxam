#ifndef DEPLOME_H
#define DEPLOME_H

#include <QDialog>
#include <QDate>
#include <QTime>

namespace Ui {
class Deplome;
}

class Deplome : public QDialog
{
    Q_OBJECT

public:
    explicit Deplome(QWidget *parent = nullptr);
    ~Deplome();

private slots:
    void on_btnRechercherFormation_clicked();
    void on_btnChoisirImage_clicked();
    void on_btnValider_clicked();
    void on_btnOuvrirHistorique_clicked(); // ✅ Nouveau slot

private:
    Ui::Deplome *ui;

    QString sujet;
    QDate date;
    QTime heure;
    int duree = 0;
    QString imagePath;
};

#endif // DEPLOME_H
