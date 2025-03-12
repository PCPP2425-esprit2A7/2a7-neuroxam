#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QString>
#include <QDate>
#include <QRegularExpression>
#include "employe.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    employe e;
    QSqlQueryModel *model =e.afficher(); // Ensure to create a new instance of employe
    qDebug() << "Nombre d'employés :" << model->rowCount();
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



void MainWindow::verifierNumeroTelephone()
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

void MainWindow::on_ajoute_clicked()
{
    QString nom = ui->nom->text().trimmed();
    QString prenom = ui->prenom->text().trimmed();
    QString numero_telephone = ui->numero_telephone->text().trimmed();
    QString email = ui->email->text().trimmed();
    QString password = ui->password->text().trimmed();
    QDate date_dembauche = ui->date_dembauche->date();

    verifierNom();
    verifierNumeroTelephone();

    if (nom.isEmpty() || prenom.isEmpty() || numero_telephone.isEmpty() || email.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs obligatoires.");
        return;
    }

    employe newEmploye(nom, prenom, numero_telephone, email, password, date_dembauche);

    if (newEmploye.create()) {
        QMessageBox::information(this, "Succès", "L'employé a été ajouté avec succès !");
        ui->aff->setModel(newEmploye.afficher());
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout de l'employé.");
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

void MainWindow::on_modifier_clicked()
{
    QString idText = ui->idedit->text();
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
        ui->aff->setModel(e.afficher());
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible de modifier l'employé.");
    }
}

void MainWindow::on_supprimer_clicked()
{
    QString idText = ui->idedit->text();
    bool ok;
    int id = idText.toInt(&ok);

    if (!ok || id <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide.");
        return;
    }

    employe e;

    if (e.remove(id)) {
        QMessageBox::information(this, "Succès", "Employé supprimé avec succès.");
        ui->aff->setModel(e.afficher());
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de la suppression de l'employé.");
    }
}
