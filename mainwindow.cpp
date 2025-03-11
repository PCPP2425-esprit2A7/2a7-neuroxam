#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QString>
#include <QFileDialog>
#include "centre.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSqlQueryModel *model = c.afficher();
    qDebug() << "Nombre de centre :" << model->rowCount();
    ui->aff->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::verifierNom()
{
    QString nom = ui->nom->text();
    QRegularExpression regex("^[A-Za-zÀ-ÖØ-öø-ÿ]+$");
    if (nom.isEmpty()) {
        ui->nomeror->clear();
    } else if (!regex.match(nom).hasMatch()) {
        ui->nomeror->setText("Le nom doit contenir uniquement des lettres.");
    } else {
        ui->nomeror->clear();
    }
}
void MainWindow::verifierads()
{
    QString adresse = ui->adresse->text().trimmed();
    if (adresse.isEmpty()) {
        ui->adseror->clear();
    } else if (adresse[0] < 'A' || adresse[0] > 'Z') {
        ui->adseror->setText("Le nom doit contenir uniquement des lettres.");
    } else {
        ui->adseror->clear();
    }
}
void MainWindow::verifierdtc()
{
     QString directeur = ui->directeur->text().trimmed();
    QRegularExpression regex("^[A-Za-zÀ-ÖØ-öø-ÿ]+$");
    if (directeur.isEmpty()) {
        ui->drteror->clear();
    } else if (directeur[0] < 'A' || directeur[0] > 'Z') {
        ui->drteror->setText("Le nom doit contenir uniquement des lettres.");
    } else {
        ui->drteror->clear();
    }
}


void MainWindow::on_ajoute_clicked()
{
    QString nom = ui->nom->text().trimmed();
    QString adresse = ui->adresse->text().trimmed();
    QString directeur = ui->directeur->text().trimmed();
    QString facilities = ui->facilities->text().trimmed();
    int status = ui->status->currentIndex();
    int capacite = ui->capacite->text().toInt();
    MainWindow::verifierNom();
    MainWindow::verifierdtc();
    MainWindow::verifierads();
    if (nom.isEmpty() || adresse.isEmpty() || directeur.isEmpty() || facilities.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs obligatoires.");
        return;
    }

    int s =0;
    QRegularExpression regex("^[A-Za-zÀ-ÖØ-öø-ÿ]+$");
    if (!regex.match(nom).hasMatch()) {
        s=1;
    }

    if (directeur[0] < 'A' || directeur[0] > 'Z') {
        s=1;
    }
    if (adresse[0] < 'A' || adresse[0] > 'Z') {
        s=1;
    }

    if (capacite <= 0) {
        ui->cpteror->setText("La capacité doit être positive.");
        s=1;
    }
    if (s==1){
        return;
    }
    centre newCentre(nom, adresse, directeur, facilities, status, capacite);

    if (newCentre.create()) {
        QMessageBox::information(this, "Succès", "Le centre a été ajouté avec succès !");
        ui->aff->setModel(newCentre.afficher());
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout du centre.");
    }
}


void MainWindow::on_recuperer_clicked()
{
    QString idText = ui->idedit->text();

    bool ok;
    int id = idText.toInt(&ok);


    if (!ok || id <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide.");
        return;
    }

    if (!centre::exists(id)) {
        QMessageBox::warning(this, "Erreur", "Centre non trouvé.");
        return;
    }
    centre c = centre::read(id);
    ui->nom->setText(c.getNom());
    ui->adresse->setText(c.getAdresse());
    ui->directeur->setText(c.getDirecteur());
    ui->facilities->setText(c.getFacilities());
    ui->status->setCurrentIndex(c.getStatus());
    ui->capacite->setText(QString::number(c.getCapacite()));
}



void MainWindow::on_modifier_clicked()
{
    QString idText = ui->idedit->text();
    bool ok;
    int id = idText.toInt(&ok);
    if (!ok || id <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide.");
        return;
    }
    if (!centre::exists(id)) {
        QMessageBox::warning(this, "Erreur", "Centre non trouvé.");
        return;
    }
    QString nom = ui->nom->text().trimmed();
    QString adresse = ui->adresse->text().trimmed();
    QString directeur = ui->directeur->text().trimmed();
    QString facilities = ui->facilities->text().trimmed();
    int status = ui->status->currentIndex();
    int capacite = ui->capacite->text().toInt();

    centre c;
    if (c.update(id, nom, adresse, directeur, facilities, status, capacite)) {
        QMessageBox::information(this, "Succès", "Le centre a été modifié avec succès.");
        ui->aff->setModel(c.afficher());
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible de modifier le centre.");
    }
}


void MainWindow::on_sup_clicked()
{
    QString idText = ui->idedit->text();

    bool ok;
    int id = idText.toInt(&ok);

    if (!ok || id <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide.");
        return;
    }

    centre c;
    if (c.remove(id)) {
        QMessageBox::information(this, "Succès", "centre supprimé avec succès.");
        ui->aff->setModel(c.afficher());


    } else {
        QMessageBox::warning(this, "Erreur", "Échec de la suppression de le centre.");
    }
}





void MainWindow::on_tri_clicked()
{
    centre c;
    QString critere = ui->trie->currentText().toLower();


    if (critere == "id") {
        critere = "id";
    } else if (critere == "status") {
        critere = "status";
    } else if (critere == "capacite") {
        critere = "capacite";
    }

    bool ascendant = true;
    QSqlQueryModel* model = c.trier(critere, ascendant);
    ui->aff->setModel(model);
}


void MainWindow::on_cherchebut_clicked()
{
    centre c;
    QString valeur = ui->cherche->text();

    QSqlQueryModel* model = c.rechercher(valeur);
    ui->aff->setModel(model);
}


void MainWindow::on_pdf_clicked()
{
    QString fichierPDF = QFileDialog::getSaveFileName(this, "Enregistrer le PDF", "", "*.pdf");

    if (!fichierPDF.isEmpty()) {
        if (!fichierPDF.endsWith(".pdf", Qt::CaseInsensitive)) {
            fichierPDF += ".pdf";
        }

        centre c;
        c.genererPDF(fichierPDF);
        QMessageBox::information(this, "Succès", "Le PDF a été généré avec succès.");
    } else {
        QMessageBox::warning(this, "Annulé", "La génération du PDF a été annulée.");
    }
}

