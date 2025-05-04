#ifndef HISTORIQUEBADGES_H
#define HISTORIQUEBADGES_H

#include <QDialog>
#include <QSqlQueryModel>

namespace Ui {
class HistoriqueBadges;
}

class HistoriqueBadges : public QDialog
{
    Q_OBJECT

public:
    explicit HistoriqueBadges(QWidget *parent = nullptr);
    ~HistoriqueBadges();

private slots:
    void chargerHistorique(const QString &filtre = "");
    void filtrerHistorique();    // Slot pour filtrer l'historique
    void supprimerBadge();       // Slot pour supprimer un badge

private:
    Ui::HistoriqueBadges *ui;
};

#endif // HISTORIQUEBADGES_H
