#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "examen.h"
#include <QMessageBox>


Examen examen;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "Database not open in MainWindow constructor, attempting to connect...";
        QSqlDatabase::database().open();
    }


   ui->tableView_examen->setModel(examen.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_add_clicked()

{
    // Retrieve values from the UI
    QString matiere = ui->lineEdit_matiere->text();
    QString centre = ui->lineEdit_centre->text();
    QString type = ui->lineEdit_type->text();
    QDate dateExamen = ui->dateEdit_examen->date();
    QTime heureExamen = ui->timeEdit_examen->time();

    // Validate fields
    if (matiere.isEmpty() || centre.isEmpty() || type.isEmpty() || !dateExamen.isValid() || !heureExamen.isValid()) {
        QMessageBox::warning(this, "Champ(s) manquant(s)", "Veuillez remplir tous les champs.");
        return;
    }

    // Check if the date is valid (not in the past)
    QDate aujourdhui = QDate::currentDate();
    if (dateExamen < aujourdhui) {
        QMessageBox::warning(this, "Date invalide", "La date de l'examen ne peut pas être antérieure à aujourd'hui.");
        return;
    }

    // Debug output
    qDebug() << "Matière:" << matiere;
    qDebug() << "Centre:" << centre;
    qDebug() << "Type:" << type;
    qDebug() << "Date:" << dateExamen;
    qDebug() << "Heure:" << heureExamen;

    // Create an instance of the Examen class
    Examen examen(dateExamen, heureExamen, matiere, centre, type);

    // Add the exam to the database
    bool success = examen.ajouter();

    // Show a message based on the result
    if (success) {
        QMessageBox::information(this, "Succès", "L'examen a été ajouté avec succès.");
        // Clear the fields
        ui->lineEdit_matiere->clear();
        ui->lineEdit_centre->clear();
        ui->lineEdit_type->clear();
        ui->dateEdit_examen->setDate(QDate::currentDate());
        ui->timeEdit_examen->setTime(QTime::currentTime());
        // Refresh the table view
        ui->tableView_examen->setModel(examen.afficher());
    } else {
        QMessageBox::critical(this, "Erreur", "Une erreur est survenue lors de l'ajout de l'examen.");
    }
}


void MainWindow::on_pushButton_modif_clicked()
{
    bool ok;
    int id = ui->id_examen->text().toInt(&ok);
    if (!ok || id <= 0) {
        QMessageBox::critical(this, "Erreur", "ID de l'examen invalide.");
        return;
    }

    // Retrieve values from the UI
    QString matiere = ui->lineEdit_matiere->text();
    QString centre = ui->lineEdit_centre->text();
    QString type = ui->lineEdit_type->text();
    QDate dateExamen = ui->dateEdit_examen->date();
    QTime heureExamen = ui->timeEdit_examen->time();

    // Validate fields
    if (matiere.isEmpty() || centre.isEmpty() || type.isEmpty() || !dateExamen.isValid() || !heureExamen.isValid()) {
        QMessageBox::critical(this, "Erreur", "Veuillez remplir tous les champs.");
        return;
    }

    // Check if the date is valid (not in the past)
    QDate aujourdhui = QDate::currentDate();
    if (dateExamen < aujourdhui) {
        QMessageBox::warning(this, "Date invalide", "La date de l'examen ne peut pas être antérieure à aujourd'hui.");
        return;
    }

    // Create an instance of the Examen class
    Examen examen(id, dateExamen, heureExamen, matiere, centre, type);

    // Update the exam in the database
    bool success = examen.modifier(id);

    if (success) {
        // Refresh the table view
        ui->tableView_examen->setModel(examen.afficher());
        // Clear the fields
        ui->lineEdit_matiere->clear();
        ui->lineEdit_centre->clear();
        ui->lineEdit_type->clear();
        ui->dateEdit_examen->setDate(QDate::currentDate());
        ui->timeEdit_examen->setTime(QTime::currentTime());
        ui->id_examen->clear();

        QMessageBox::information(this, "Modification réussie", "Examen modifié avec succès.");
    } else {
        QMessageBox::critical(this, "Erreur", "Une erreur est survenue lors de la modification de l'examen.");
    }
}




void MainWindow::on_pushButton_delete_clicked()
{
    // Check if a row is selected
    QModelIndexList selectedIndexes = ui->tableView_examen->selectionModel()->selectedIndexes();

    if (!selectedIndexes.isEmpty()) {
        // Get the ID of the selected exam
        int id = selectedIndexes.at(0).sibling(selectedIndexes.at(0).row(), 0).data().toInt();

        // Call the delete function
        bool supprime = examen.supprimer(id);

        if (supprime) {
            // Refresh the table view
            ui->tableView_examen->setModel(examen.afficher());
            QMessageBox::information(this, "Suppression réussie", "Examen supprimé avec succès.");
        } else {
            QMessageBox::warning(this, "Échec de la suppression", "Échec de la suppression de l'examen.");
        }
    } else {
        QMessageBox::warning(this, "Aucun examen sélectionné", "Veuillez sélectionner un examen à supprimer.");
    }
}


void MainWindow::on_tableView_examen_doubleClicked(const QModelIndex &index)
{
    int row = index.row();
    // Retrieve data from the selected row
    int id = ui->tableView_examen->model()->data(ui->tableView_examen->model()->index(row, 0)).toInt();
    QString matiere = ui->tableView_examen->model()->data(ui->tableView_examen->model()->index(row, 1)).toString();
    QString centre = ui->tableView_examen->model()->data(ui->tableView_examen->model()->index(row, 2)).toString();
    QString type = ui->tableView_examen->model()->data(ui->tableView_examen->model()->index(row, 3)).toString();
    QDate dateExamen = ui->tableView_examen->model()->data(ui->tableView_examen->model()->index(row, 4)).toDate();

    // Get the time as string first (since it's now formatted as "HH:MI AM")
    QString timeString = ui->tableView_examen->model()->data(ui->tableView_examen->model()->index(row, 5)).toString();
    // Convert the formatted string to QTime
    QTime heureExamen = QTime::fromString(timeString, "h:mm AP");

    // Set the data in the UI fields
    ui->id_examen->setText(QString::number(id));
    ui->lineEdit_matiere->setText(matiere);
    ui->lineEdit_centre->setText(centre);
    ui->lineEdit_type->setText(type);
    ui->dateEdit_examen->setDate(dateExamen);
    ui->timeEdit_examen->setTime(heureExamen);
}

