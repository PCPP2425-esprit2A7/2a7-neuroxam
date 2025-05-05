#include "historiquebadges.h"
#include "ui_historiquebadges.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
#include <QStandardItemModel>

HistoriqueBadges::HistoriqueBadges(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::HistoriqueBadges)
{
    ui->setupUi(this);
    chargerHistorique();

    connect(ui->btnFermer, &QPushButton::clicked, this, &HistoriqueBadges::close);
    connect(ui->btnFiltrer, &QPushButton::clicked, this, &HistoriqueBadges::filtrerHistorique);
    connect(ui->btnSupprimer, &QPushButton::clicked, this, &HistoriqueBadges::supprimerBadge);
}

HistoriqueBadges::~HistoriqueBadges()
{
    delete ui;
}

void HistoriqueBadges::chargerHistorique(const QString &filtre)
{
    QFile fichier("historique_badges.txt");
    if (!fichier.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir historique_badges.txt");
        return;
    }

    QStandardItemModel *model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({ "Type", "UID", "Horodatage" });

    QTextStream in(&fichier);
    int totalLignes = 0;

    while (!in.atEnd()) {
        QString ligne = in.readLine().trimmed();
        if (ligne.isEmpty()) continue;

        if (!filtre.isEmpty() && !ligne.contains(filtre, Qt::CaseInsensitive)) {
            continue; // on filtre
        }

        QStringList morceaux = ligne.split(";", Qt::SkipEmptyParts);
        if (morceaux.size() >= 3) {
            QList<QStandardItem *> items;
            for (const QString &champ : morceaux) {
                items.append(new QStandardItem(champ.trimmed()));
            }
            model->appendRow(items);
            totalLignes++;
        }
    }

    fichier.close();

    ui->tableViewHistorique->setModel(model);
    ui->tableViewHistorique->resizeColumnsToContents();
    ui->tableViewHistorique->setAlternatingRowColors(true);

    ui->labelStats->setText(QString("📄 Total lignes : %1").arg(totalLignes));
}

void HistoriqueBadges::filtrerHistorique()
{
    QString filtre = ui->lineEditFiltre->text().trimmed();
    chargerHistorique(filtre);
}

void HistoriqueBadges::supprimerBadge()
{
    QModelIndex index = ui->tableViewHistorique->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, "Sélection requise", "Sélectionnez une ligne à supprimer.");
        return;
    }

    QString uid = ui->tableViewHistorique->model()->index(index.row(), 1).data().toString(); // colonne UID
    QString type = ui->tableViewHistorique->model()->index(index.row(), 0).data().toString(); // ENTREE/SORTIE
    QString horodatage = ui->tableViewHistorique->model()->index(index.row(), 2).data().toString(); // date

    QString ligneCible = QString("%1 ; %2 ; %3").arg(type, uid, horodatage).trimmed();

    QFile fichier("historique_badges.txt");
    if (!fichier.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QStringList lignes;
    QTextStream in(&fichier);
    while (!in.atEnd()) {
        QString ligne = in.readLine().trimmed();
        if (ligne != ligneCible) {
            lignes << ligne;
        }
    }
    fichier.close();

    if (!fichier.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) return;

    QTextStream out(&fichier);
    for (const QString &l : lignes) {
        out << l << "\n";
    }

    fichier.close();
    chargerHistorique(); // Recharge après suppression
}
