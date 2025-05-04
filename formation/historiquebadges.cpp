#include "historiquebadges.h"
#include "ui_historiquebadges.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>

HistoriqueBadges::HistoriqueBadges(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HistoriqueBadges)
{
    ui->setupUi(this);
    chargerHistorique();

    connect(ui->btnFermer, &QPushButton::clicked, this, &HistoriqueBadges::close);
    connect(ui->btnFiltrer, &QPushButton::clicked, this, &HistoriqueBadges::filtrerHistorique);
    connect(ui->btnSupprimer, &QPushButton::clicked, this, &HistoriqueBadges::supprimerBadge); // Connexion bouton supprimer
}

HistoriqueBadges::~HistoriqueBadges()
{
    delete ui;
}

void HistoriqueBadges::chargerHistorique(const QString &filtre)
{
    QSqlQueryModel *model = new QSqlQueryModel(this);

    QString queryStr = R"(
        SELECT
            UID_BADGE AS "Badge",
            NOM_FORMATEUR AS "Formateur",
            TO_CHAR(DATE_ENTREE, 'DD/MM/YYYY HH24:MI:SS') AS "Heure d'entrée",
            TO_CHAR(DATE_SORTIE, 'DD/MM/YYYY HH24:MI:SS') AS "Heure de sortie"
        FROM BADGE_ENTREES
    )";

    if (!filtre.isEmpty()) {
        queryStr += " WHERE LOWER(UID_BADGE) LIKE LOWER('%" + filtre + "%') OR LOWER(NOM_FORMATEUR) LIKE LOWER('%" + filtre + "%')";
    }

    queryStr += " ORDER BY DATE_ENTREE DESC";

    model->setQuery(queryStr);

    if (model->lastError().isValid()) {
        qDebug() << "❌ Erreur SQL :" << model->lastError().text();
    } else {
        ui->tableViewHistorique->setModel(model);
        ui->tableViewHistorique->setAlternatingRowColors(true);
        ui->tableViewHistorique->resizeColumnsToContents();

        // 🔢 Statistiques dynamiques
        int total = model->rowCount();
        ui->labelStats->setText(QString("🔐 Total entrées : %1").arg(total));
    }
}

void HistoriqueBadges::filtrerHistorique()
{
    QString texteFiltre = ui->lineEditFiltre->text().trimmed();
    chargerHistorique(texteFiltre);
}

void HistoriqueBadges::supprimerBadge()
{
    QModelIndexList selection = ui->tableViewHistorique->selectionModel()->selectedRows();

    if (selection.isEmpty()) {
        QMessageBox::warning(this, "Avertissement", "Veuillez sélectionner un badge à supprimer.");
        return;
    }

    QString badgeUID = selection.first().data().toString();
    QSqlQuery query;
    query.prepare("DELETE FROM BADGE_ENTREES WHERE UID_BADGE = :uid");
    query.bindValue(":uid", badgeUID);

    if (!query.exec()) {
        qDebug() << "❌ Erreur lors de la suppression du badge :" << query.lastError().text();
        QMessageBox::critical(this, "Erreur", "Impossible de supprimer le badge.");
    } else {
        QMessageBox::information(this, "Succès", "Le badge a été supprimé avec succès.");
        chargerHistorique(); // Recharger l'historique après suppression
    }
}
