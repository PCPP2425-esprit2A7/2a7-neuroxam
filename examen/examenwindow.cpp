#include "examenwindow.h"
#include "ui_examenwindow.h"
#include "centre/piechartwidget.h"
#include <QMessageBox>
#include <QString>
#include <QFileDialog>
#include "examen.h"
#include "EmailDialog.h"
#include <QTextCharFormat>
#include <QBrush>
#include <QColor>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDialog>


examenwindow::examenwindow(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::examenwindow)
{
    ui->setupUi(this);
    mettreAJourCalendrier();
    QSqlQueryModel *model = e.afficher();
    qDebug() << "Nombre d'examens :" << model->rowCount();
    ui->aff->setModel(model);
    connect(ui->btn_ouvrirEmailDialog_, &QPushButton::clicked, this, &examenwindow::on_btn_ouvrirEmailDialog_clicked);
}

examenwindow::~examenwindow()
{
    delete ui;
}

void examenwindow::on_ajoute_clicked() {
    // Récupération des valeurs saisies
    QDate date_examen = ui->date_examen->date();
    QString heure_examen = ui->heure_examen->text().trimmed();
    QString matiere = ui->matiere->text().trimmed();
    QString type_examen = ui->type_examen->text().trimmed();
    QString centre_examen = ui->centre_examen->text().trimmed();
    QString email = ui->email->text().trimmed();

    // Vérification des champs obligatoires
    if (matiere.isEmpty() || type_examen.isEmpty() || centre_examen.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs obligatoires.");
        return;
    }

    // Vérification si un examen est déjà prévu pour cette date
    if (examen::existeExamenLeMemeJour(date_examen)) {
        QMessageBox::warning(this, "Date déjà réservée", "Un examen est déjà prévu à cette date. Veuillez choisir une autre date.");
        return;
    }

    // Création de l'objet examen
    examen newExamen(date_examen, heure_examen, matiere, type_examen, centre_examen, email);

    // Tentative d'ajout à la base de données
    if (newExamen.create()) {
        QMessageBox::information(this, "Succès", "L'examen a été ajouté avec succès !");
        ui->aff->setModel(newExamen.afficher());

        // Mise à jour du calendrier après ajout
        mettreAJourCalendrier();  // Appeler la fonction pour mettre à jour l'affichage
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout de l'examen.");
    }
}



void examenwindow::on_recuperer_clicked()
{
    QString idText = ui->idedit->text();

    bool ok;
    int id_examen = idText.toInt(&ok);

    if (!ok || id_examen <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide.");
        return;
    }

    if (!examen::exists(id_examen)) {
        QMessageBox::warning(this, "Erreur", "Examen non trouvé.");
        return;
    }

    examen e = examen::read(id_examen);
    ui->date_examen->setDate(e.getDateExamen());
    ui->heure_examen->setText(e.getHeureExamen());
    ui->matiere->setText(e.getMatiere());
    ui->type_examen->setText(e.getTypeExamen());
    ui->centre_examen->setText(e.getCentreExamen());
    ui->email->setText(e.getEmail());
}

void examenwindow::on_modifier_clicked()
{
    QString idText = ui->idedit->text();
    bool ok;
    int id_examen = idText.toInt(&ok);

    if (!ok || id_examen <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide.");
        return;
    }

    if (!examen::exists(id_examen)) {
        QMessageBox::warning(this, "Erreur", "Examen non trouvé.");
        return;
    }

    QDate date_examen = ui->date_examen->date();
    QString heure_examen = ui->heure_examen->text().trimmed();
    QString matiere = ui->matiere->text().trimmed();
    QString type_examen = ui->type_examen->text().trimmed();
    QString centre_examen = ui->centre_examen->text().trimmed();
    QString email = ui->email->text().trimmed();

    examen e;
    if (e.update(id_examen, date_examen, heure_examen, matiere, type_examen, centre_examen, email)) {
        QMessageBox::information(this, "Succès", "L'examen a été modifié avec succès.");
        ui->aff->setModel(e.afficher());
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible de modifier l'examen.");
    }
}

void examenwindow::on_sup_clicked()
{
    QString idText = ui->idedit->text();
    bool ok;
    int id_examen = idText.toInt(&ok);

    if (!ok || id_examen <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide.");
        return;
    }

    examen e;
    if (e.remove(id_examen)) {
        QMessageBox::information(this, "Succès", "Examen supprimé avec succès.");
        ui->aff->setModel(e.afficher());
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de la suppression de l'examen.");
    }
}

void examenwindow::on_tri_clicked()
{
    examen e;
    QString critere = ui->trie->currentText().toLower();

    if (critere == "id_examen") {
        critere = "id_examen";
    } else if (critere == "date_examen") {
        critere = "date_examen";
    }

    bool ascendant = true;
    QSqlQueryModel* model = e.trier(critere, ascendant);
    ui->aff->setModel(model);
}

void examenwindow::on_cherchebut_clicked()
{
    examen e;
    QString valeur = ui->cherche->text();

    QSqlQueryModel* model = e.rechercher(valeur);
    ui->aff->setModel(model);
}

void examenwindow::on_pdf_clicked()
{
    QString fichierPDF = QFileDialog::getSaveFileName(this, "Enregistrer le PDF", "", "*.pdf");

    if (!fichierPDF.isEmpty()) {
        if (!fichierPDF.endsWith(".pdf", Qt::CaseInsensitive)) {
            fichierPDF += ".pdf";
        }

        examen e;
        e.genererPDF(fichierPDF);
        QMessageBox::information(this, "Succès", "Le PDF a été généré avec succès.");
    } else {
        QMessageBox::warning(this, "Annulé", "La génération du PDF a été annulée.");
    }
}

#include <QVBoxLayout>  // Include if not already

void examenwindow::on_stat_clicked()
{
    examen e;
    QMap<QString, int> stats = e.obtenirStatistiques();

    if (stats.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Impossible de récupérer les statistiques.");
        return;
    }

    // Create a dialog window
    QDialog* statWindow = new QDialog(this);
    statWindow->setWindowTitle("Statistiques par poste");

    // Create chart widget
    PieChartWidget* chartWidget = new PieChartWidget(stats, statWindow);

    // Set layout
    QVBoxLayout* layout = new QVBoxLayout(statWindow);
    layout->addWidget(chartWidget);
    statWindow->setLayout(layout);

    statWindow->resize(600, 600);
    statWindow->exec(); // modal, use .show() if you want non-modal
}


void examenwindow::on_btn_ouvrirEmailDialog_clicked()
{
    EmailDialog dialog(this);
    dialog.exec(); // Affiche la fenêtre modale
}

void examenwindow::mettreAJourCalendrier() {


    QSqlQuery query;
    if (!query.exec("SELECT date_examen FROM examen")) {
        qDebug() << "❌ Erreur dans la requête :" << query.lastError();
        return;
    }

    QTextCharFormat formatVert;
    formatVert.setBackground(QBrush(Qt::green));  // Fond vert pour la date
    formatVert.setForeground(QBrush(Qt::white));  // Texte blanc pour contraste

    bool hasDate = false;

    while (query.next()) {
        QDate date = query.value(0).toDate();  // Récupérer la date d'examen
        qDebug() << "✅ Date trouvée dans la base :" << date;
        ui->calendar_examen->setDateTextFormat(date, formatVert);  // Colorier la date en vert
        hasDate = true;
    }

    if (!hasDate) {
        qDebug() << "⚠️ Aucun examen trouvé dans la base.";
    }
}


