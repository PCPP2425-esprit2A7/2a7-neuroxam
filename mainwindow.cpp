#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "materiel.h"
#include <QMessageBox>
#include <QStandardItemModel>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadMaterielsIntoTable();


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::loadMaterielsIntoTable()
{
    MaterielManager manager;
    std::vector<Materiel> materiels = manager.getAllMateriels();

    QStandardItemModel *model = new QStandardItemModel(this);
    model->setColumnCount(5);
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "Type");
    model->setHeaderData(2, Qt::Horizontal, "État");
    model->setHeaderData(3, Qt::Horizontal, "Localisation");
    model->setHeaderData(4, Qt::Horizontal, "Disponibilité");

    for (int row = 0; row < static_cast<int>(materiels.size()); ++row) {
        const Materiel& m = materiels[row];

        model->setItem(row, 0, new QStandardItem(QString::number(m.getId())));
        model->setItem(row, 1, new QStandardItem(m.getType()));
        model->setItem(row, 2, new QStandardItem(m.getEtat()));
        model->setItem(row, 3, new QStandardItem(m.getLocalisation()));
        model->setItem(row, 4, new QStandardItem(m.getDisponibilite()));
    }

    ui->materielTableWidget->setModel(model);
    ui->materielTableWidget->resizeColumnsToContents();
    ui->materielTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->materielTableWidget->setColumnHidden(0, true);
    ui->materielTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->materielTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->materielTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}




void MainWindow::on_addButton_clicked()
{
    QString type = ui->type->currentText();
    QString etat = ui->etat->currentText();
    QString localisation = ui->localisation->currentText();
    QString disponibilite = ui->disponibilite->currentText();

    if (type.isEmpty() || etat.isEmpty() || localisation.isEmpty() || disponibilite.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all fields.");
        return;
    }

    Materiel newMateriel(type, etat, localisation, disponibilite);

    MaterielManager manager;
    if (manager.addMateriel(newMateriel)) {
        qDebug() << "Materiel added successfully!";
        loadMaterielsIntoTable();

        ui->type->setCurrentIndex(0);
        ui->etat->setCurrentIndex(0);
        ui->localisation->setCurrentIndex(0);
        ui->disponibilite->setCurrentIndex(0);
        loadedMaterielId = -1;
    } else {
        QMessageBox::critical(this, "Error", "Failed to add materiel.");
    }
}

void MainWindow::on_loadButton_clicked()
{
    QModelIndexList selectedRows = ui->materielTableWidget->selectionModel()->selectedRows();

    if (selectedRows.isEmpty()) {
        QMessageBox::warning(this, "Selection Error", "Please select a row to load.");
        return;
    }

    QModelIndex index = selectedRows.first();
    QAbstractItemModel *model = ui->materielTableWidget->model();

    // Store ID (column 0)
    loadedMaterielId = model->index(index.row(), 0).data().toInt();

    // Get other values
    QString type = model->index(index.row(), 1).data().toString();
    QString etat = model->index(index.row(), 2).data().toString();
    QString localisation = model->index(index.row(), 3).data().toString();
    QString disponibilite = model->index(index.row(), 4).data().toString();

    auto findIndex = [](QComboBox* box, const QString& value) {
        for (int i = 1; i < box->count(); ++i) {
            if (box->itemText(i) == value)
                return i;
        }
        return 0;
    };

    ui->type->setCurrentIndex(findIndex(ui->type, type));
    ui->etat->setCurrentIndex(findIndex(ui->etat, etat));
    ui->localisation->setCurrentIndex(findIndex(ui->localisation, localisation));
    ui->disponibilite->setCurrentIndex(findIndex(ui->disponibilite, disponibilite));
}


void MainWindow::on_editButton_clicked()
{
    if (loadedMaterielId == -1) {
        QMessageBox::warning(this, "Edit Error", "No materiel loaded to edit.");
        return;
    }

    QString type = ui->type->currentText();
    QString etat = ui->etat->currentText();
    QString localisation = ui->localisation->currentText();
    QString disponibilite = ui->disponibilite->currentText();

    if (type.isEmpty() || etat.isEmpty() || localisation.isEmpty() || disponibilite.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all fields.");
        return;
    }

    Materiel updatedMateriel(type, etat, localisation, disponibilite);
    updatedMateriel.setId(loadedMaterielId);

    MaterielManager manager;
    if (manager.updateMateriel(updatedMateriel)) {
        qDebug() << "Materiel updated successfully!";
        loadMaterielsIntoTable();

        // Reset fields
        ui->type->setCurrentIndex(0);
        ui->etat->setCurrentIndex(0);
        ui->localisation->setCurrentIndex(0);
        ui->disponibilite->setCurrentIndex(0);

        // Clear loaded ID
        loadedMaterielId = -1;
    } else {
        QMessageBox::critical(this, "Error", "Failed to update materiel.");
    }
}



void MainWindow::on_deleteButton_clicked()
{
    QModelIndexList selectedRows = ui->materielTableWidget->selectionModel()->selectedRows();

    if (selectedRows.isEmpty()) {
        QMessageBox::warning(this, "Selection Error", "Please select a row to delete.");
        return;
    }

    QModelIndex index = selectedRows.first();
    int id = ui->materielTableWidget->model()->index(index.row(), 0).data().toInt();

    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Confirm Delete", "Are you sure you want to delete this materiel?",
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        MaterielManager manager;
        if (manager.deleteMateriel(id)) {
            qDebug() << "Materiel deleted successfully!";
            loadMaterielsIntoTable();

            // Reset form if this was the loaded materiel
            if (loadedMaterielId == id) {
                loadedMaterielId = -1;
                ui->type->setCurrentIndex(0);
                ui->etat->setCurrentIndex(0);
                ui->localisation->setCurrentIndex(0);
                ui->disponibilite->setCurrentIndex(0);
            }
        } else {
            QMessageBox::critical(this, "Error", "Failed to delete materiel.");
        }
    }
}


void MainWindow::on_searchButton_clicked()
{
    QString searchText = ui->search->text().trimmed();

    QSqlQuery query;
    query.prepare("SELECT * FROM materiels WHERE "
                  "LOWER(type) LIKE LOWER(:text) OR "
                  "LOWER(etat) LIKE LOWER(:text) OR "
                  "LOWER(localisation) LIKE LOWER(:text) OR "
                  "LOWER(disponibilite) LIKE LOWER(:text)");
    query.bindValue(":text", "%" + searchText + "%");

    if (!query.exec()) {
        qDebug() << "Erreur lors de la recherche: " << query.lastError().text();
        return;
    }

    // Create a new model
    QStandardItemModel *model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels(QStringList() << "ID" << "Type" << "État" << "Localisation" << "Disponibilité");

    while (query.next()) {
        QList<QStandardItem *> rowItems;

        rowItems << new QStandardItem(query.value("id").toString());
        rowItems << new QStandardItem(query.value("type").toString());
        rowItems << new QStandardItem(query.value("etat").toString());
        rowItems << new QStandardItem(query.value("localisation").toString());
        rowItems << new QStandardItem(query.value("disponibilite").toString());

        model->appendRow(rowItems);
    }

    ui->materielTableWidget->setModel(model);
    ui->materielTableWidget->setColumnHidden(0, true);  // Hide ID
}




void MainWindow::on_resetButton_clicked()
{
    loadMaterielsIntoTable();
}


void MainWindow::on_sortButton_clicked()
{
    QString selectedProperty = ui->sortBox->currentText().trimmed();

    QString orderByColumn;
    if (selectedProperty == "Type") {
        orderByColumn = "type";
    } else if (selectedProperty == "Etat") {
        orderByColumn = "etat";
    } else if (selectedProperty == "Localisation") {
        orderByColumn = "localisation";
    } else if (selectedProperty == "Disponibilité") {
        orderByColumn = "disponibilite";
    } else {
        orderByColumn = "type";
    }

    QSqlQuery query;
    query.prepare(QString("SELECT * FROM materiels ORDER BY %1 ASC").arg(orderByColumn));

    if (!query.exec()) {
        qDebug() << "Erreur lors du tri des materiels: " << query.lastError().text();
        return;
    }

    // Create a new model
    QStandardItemModel *model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels(QStringList() << "ID" << "Type" << "État" << "Localisation" << "Disponibilité");

    while (query.next()) {
        QList<QStandardItem *> rowItems;

        rowItems << new QStandardItem(query.value("id").toString());
        rowItems << new QStandardItem(query.value("type").toString());
        rowItems << new QStandardItem(query.value("etat").toString());
        rowItems << new QStandardItem(query.value("localisation").toString());
        rowItems << new QStandardItem(query.value("disponibilite").toString());

        model->appendRow(rowItems);
    }

    ui->materielTableWidget->setModel(model);
    ui->materielTableWidget->setColumnHidden(0, true);  // Hide ID
}



void MainWindow::on_pdfButton_clicked()
{
    // Open a file dialog to choose the save location
    QString filePath = QFileDialog::getSaveFileName(this, "Save PDF", "", "PDF Files (*.pdf)");

    // Check if the user selected a file path
    if (filePath.isEmpty()) {
        qDebug() << "No file selected.";
        return;  // If no file is selected, exit
    }

    // Ensure the file ends with .pdf extension
    if (!filePath.endsWith(".pdf", Qt::CaseInsensitive)) {
        filePath.append(".pdf");
    }

    // Call the function to generate PDF with the chosen file path
    if (manager.generatePdf(filePath)) {
        qDebug() << "PDF generated successfully!";
    } else {
        qDebug() << "Failed to generate PDF.";
    }
}

