#include "fenetresignatures.h"
#include "ui_fenetresignatures.h"
#include <QStandardItemModel>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDateTime>

FenetreSignatures::FenetreSignatures(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FenetreSignatures)
{
    ui->setupUi(this);
    actualiserTable();
}

FenetreSignatures::~FenetreSignatures()
{
    delete ui;
}

void FenetreSignatures::actualiserTable()
{
    QStandardItemModel *model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels(QStringList() << "Date" << "Nom Employé" << "Sujet" << "Hash SHA256");

    QFile fichier("signatures_certificats.txt");
    if (!fichier.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "❌ Erreur ouverture fichier signatures_certificats.txt";
        return;
    }

    QTextStream in(&fichier);
    while (!in.atEnd()) {
        QString ligne = in.readLine().trimmed();
        if (ligne.isEmpty()) continue;

        QStringList parties = ligne.split(" | ");
        if (parties.size() < 4) continue;

        QList<QStandardItem*> ligneItems;
        for (const QString &part : parties) {
            ligneItems << new QStandardItem(part.trimmed());
        }
        model->appendRow(ligneItems);
    }

    ui->tableViewSignatures->setModel(model);
    ui->tableViewSignatures->resizeColumnsToContents();
    ui->tableViewSignatures->setAlternatingRowColors(true);
    ui->tableViewSignatures->horizontalHeader()->setStretchLastSection(true);

    qDebug() << "✅ Signatures chargées depuis fichier texte.";
}
