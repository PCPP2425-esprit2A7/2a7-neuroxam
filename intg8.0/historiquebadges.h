#ifndef HISTORIQUEBADGES_H
#define HISTORIQUEBADGES_H

#include <QDialog>

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
    void filtrerHistorique();
    void supprimerBadge();

private:
    Ui::HistoriqueBadges *ui;
};

#endif // HISTORIQUEBADGES_H
