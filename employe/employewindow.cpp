#include "employewindow.h"
#include "ui_employewindow.h"
#include <QVBoxLayout>
#include "employe.h"

employewindow::employewindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::employewindow)
{
    ui->setupUi(this);
}

employewindow::~employewindow()
{
    delete ui;
}

void employewindow::verifierNomp()
{
    QString nom = ui->nom->text();
    QRegularExpression regex("^[A-Za-zÀ-ÖØ-öø-ÿ]+$");
    if (nom.isEmpty()) {
        ui->lineEdit->clear();
    } else if (!regex.match(nom).hasMatch()) {
        ui->lineEdit->setText("Le nom doit contenir uniquement des lettres.");
    } else {
        ui->lineEdit->clear();
    }
}

void employewindow::verifierNumeroTelephone()
{
    QString telephone = ui->numero_telephone1->text();
    if (telephone.isEmpty()) {
        ui->telephoneError->clear();
    } else if (!telephone.startsWith('+') && telephone.length() < 10) {
        ui->telephoneError->setText("Le numéro de téléphone est invalide.");
    } else {
        ui->telephoneError->clear();
    }
}

void employewindow::on_ajoute_clicked()
{
    QString nom = ui->nom->text().trimmed();
    QString prenom = ui->prenom->text().trimmed();
    QString numero_telephone = ui->numero_telephone->text().trimmed();
    QString email = ui->email->text().trimmed();
    QString password = ui->password->text().trimmed();
    QDate date_dembauche = ui->date_dembauche->date();

    verifierNomp();
    verifierNumeroTelephone();

    if (nom.isEmpty() || prenom.isEmpty() || numero_telephone.isEmpty() || email.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs obligatoires.");
        return;
    }

    employe newEmploye(nom, prenom, numero_telephone, email, password, date_dembauche);

    if (newEmploye.create()) {
        QMessageBox::information(this, "Succès", "L'employé a été ajouté avec succès !");
        ui->aff_5->setModel(newEmploye.afficher());
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout de l'employé.");
    }
}

void employewindow::on_recuperer_5_clicked()
{
    QString idText = ui->idedit_5->text();
    bool ok;
    int id = idText.toInt(&ok);

    if (!ok || id <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide.");
        return;
    }

    if (!employe::exists(id)) {
        QMessageBox::warning(this, "Erreur", "Employé non trouvé.");
        return;
    }

    employe e = employe::read(id);
    ui->nom->setText(e.getNom());
    ui->prenom->setText(e.getPrenom());
    ui->numero_telephone->setText(e.getNumeroTelephone());
    ui->email->setText(e.getEmail());
    ui->password->setText(e.getPassword());
    ui->date_dembauche->setDate(e.getDateDembauche());
}

void employewindow::on_modifier_clicked()
{
    QString idText = ui->idedit_5->text();
    bool ok;
    int id = idText.toInt(&ok);
    if (!ok || id <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide.");
        return;
    }
    if (!employe::exists(id)) {
        QMessageBox::warning(this, "Erreur", "Employé non trouvé.");
        return;
    }

    QString nom = ui->nom->text().trimmed();
    QString prenom = ui->prenom->text().trimmed();
    QString numero_telephone = ui->numero_telephone->text().trimmed();
    QString email = ui->email->text().trimmed();
    QString password = ui->password->text().trimmed();
    QDate date_dembauche = ui->date_dembauche->date();

    employe e;
    if (e.update(id, nom, prenom, numero_telephone, email, password, date_dembauche)) {
        QMessageBox::information(this, "Succès", "L'employé a été modifié avec succès.");
        ui->aff_5->setModel(e.afficher());
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible de modifier l'employé.");
    }
}

void employewindow::on_supprimer_clicked()
{
    QString idText = ui->idedit_5->text();
    bool ok;
    int id = idText.toInt(&ok);

    if (!ok || id <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide.");
        return;
    }

    employe e;

    if (employe::remove(id))
    {
        QMessageBox::information(this, "Succès", "Employé supprimé avec succès.");
        ui->aff_5->setModel(e.afficher());
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de la suppression de l'employé.");
    }
}
void employewindow::on_tri_clicked()
{
    employe e;
    QString critere = ui->trie->currentText().toLower();

    if (critere == "id") {
        critere = "id";
    } else if (critere == "date_deambauche") {
        critere = "date_deambauche";
    }

    bool ascendant = true;
    QSqlQueryModel* model = e.trier(critere, ascendant);
    ui->aff_5->setModel(model);
}

void employewindow::on_cherchebut_5_clicked()
{
    employe e;
    QString valeur = ui->cherche_5->text();

    QSqlQueryModel* model = e.rechercher(valeur);
    ui->aff_5->setModel(model);
}

void employewindow::on_pdf_5_clicked()
{
    QString fichierPDF = QFileDialog::getSaveFileName(this, "Enregistrer le PDF", "", "*.pdf");

    if (!fichierPDF.isEmpty()) {
        if (!fichierPDF.endsWith(".pdf", Qt::CaseInsensitive)) {
            fichierPDF += ".pdf";
        }

        employe e;
        e.genererPDF(fichierPDF);
        QMessageBox::information(this, "Succès", "Le PDF a été généré avec succès.");
    } else {
        QMessageBox::warning(this, "Annulé", "La génération du PDF a été annulée.");
    }
}
void employewindow::on_stat_5_clicked()
{
    employe e;
    QMap<QString, int> stats = e.obtenirStatistiques();

    if (stats.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Aucune donnée statistique disponible.");
        return;
    }

    QDialog statDialog(this);
    statDialog.setWindowTitle("Statistiques des ressources");
    statDialog.resize(600, 600);

    PieChartWidget* chartWidget = new PieChartWidget(stats, &statDialog);
    QVBoxLayout layout(&statDialog);
    layout.addWidget(chartWidget);

    statDialog.exec();
}




