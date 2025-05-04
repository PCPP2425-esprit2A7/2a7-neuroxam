#include "fenetresignatures.h"
#include "ui_fenetresignatures.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

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
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery("SELECT NOM_FICHIER, HASH_SHA256, TO_CHAR(DATE_SIGNATURE, 'DD/MM/YYYY HH24:MI') AS DATE_SIGNATURE FROM PDF_SIGNATURES");

    model->setHeaderData(0, Qt::Horizontal, "Nom Fichier");
    model->setHeaderData(1, Qt::Horizontal, "Hash SHA256");
    model->setHeaderData(2, Qt::Horizontal, "Date");

    ui->tableViewSignatures->setModel(model);
    ui->tableViewSignatures->setWordWrap(false);

    qDebug() << "✅ Table des signatures chargée.";
}
