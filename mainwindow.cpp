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
    ui->stackedWidget->setCurrentIndex(0);
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
    QString filePath = QFileDialog::getSaveFileName(this, "Save PDF", "", "PDF Files (*.pdf)");

    if (filePath.isEmpty()) {
        qDebug() << "No file selected.";
        return;
    }

    if (!filePath.endsWith(".pdf", Qt::CaseInsensitive)) {
        filePath.append(".pdf");
    }

    if (manager.generatePdf(filePath)) {
        qDebug() << "PDF generated successfully!";
    } else {
        qDebug() << "Failed to generate PDF.";
    }
}



void MainWindow::on_tab1_p1_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_tab2_p1_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    drawStatistics();
}


void MainWindow::on_tab1_p2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_tab2_p2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    drawStatistics();
}



int MainWindow::countEtat(const QString& etat)
{
    QSqlQuery query;

    query.prepare("SELECT COUNT(*) FROM materiels WHERE etat = :etat");
    query.bindValue(":etat", etat);

    if (!query.exec()) {
        qDebug() << "Error counting Materiel by Etat:" << query.lastError().text();
        return 0;
    }

    if (query.next()) {
        return query.value(0).toInt();
    }

    return 0;
}

int MainWindow::countDisponibilite(const QString& disponibilite)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM materiels WHERE disponibilite = :disponibilite");
    query.bindValue(":disponibilite", disponibilite);

    if (!query.exec()) {
        qDebug() << "Error counting Materiel by Disponibilite:" << query.lastError().text();
        return 0;
    }

    if (query.next()) {
        return query.value(0).toInt();
    }

    return 0;
}


void MainWindow::drawStatistics()
{
    QPixmap pixmap(600, 400);
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);

    QRect rect(130, 50, 150, 150);

    int nbExcellent = countEtat("Excellent");
    int nbBon = countEtat("Bon");
    int nbMauvais = countEtat("Mauvais");
    int nbHorsService = countEtat("Hors Service");

    int totalEtat = nbExcellent + nbBon + nbMauvais + nbHorsService;
    if (totalEtat == 0) return;

    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 12, QFont::Bold));
    painter.drawText(130, 60, "Etat");

    int angleExcellent = static_cast<int>(360.0 * nbExcellent / totalEtat);
    int angleBon = static_cast<int>(360.0 * nbBon / totalEtat);
    int angleMauvais = static_cast<int>(360.0 * nbMauvais / totalEtat);
    int angleHorsService = 360 - angleExcellent - angleBon - angleMauvais;

    int startAngle = 0;

    painter.setBrush(Qt::blue);
    painter.drawPie(rect, startAngle * 16, angleExcellent * 16);
    startAngle += angleExcellent;

    painter.setBrush(Qt::green);
    painter.drawPie(rect, startAngle * 16, angleBon * 16);
    startAngle += angleBon;

    painter.setBrush(Qt::red);
    painter.drawPie(rect, startAngle * 16, angleMauvais * 16);
    startAngle += angleMauvais;

    painter.setBrush(Qt::gray);
    painter.drawPie(rect, startAngle * 16, angleHorsService * 16);

    painter.setPen(Qt::black);
    painter.setPen(Qt::blue);
    painter.drawText(420, 80, QString("🔵 Excellent: %1").arg(nbExcellent));

    painter.setPen(Qt::green);
    painter.drawText(420, 110, QString("🟢 Bon: %1").arg(nbBon));

    painter.setPen(Qt::red);
    painter.drawText(420, 140, QString("🔴 Mauvais: %1").arg(nbMauvais));

    painter.setPen(Qt::gray);
    painter.drawText(420, 170, QString("⚫ Hors Service: %1").arg(nbHorsService));

    QRect rectDisponibilite(130, 240, 150, 150);

    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 12, QFont::Bold));
    painter.drawText(130, 230, "Disponibilité");

    int nbDisponible = countDisponibilite("Disponible");
    int nbEnUtilisation = countDisponibilite("En Utilisation");
    int nbEnReparation = countDisponibilite("En Réparation");
    int nbIndisponible = countDisponibilite("Indisponible");

    int totalDisponibilite = nbDisponible + nbEnUtilisation + nbEnReparation + nbIndisponible;
    if (totalDisponibilite == 0) return;

    int angleDisponible = static_cast<int>(360.0 * nbDisponible / totalDisponibilite);
    int angleEnUtilisation = static_cast<int>(360.0 * nbEnUtilisation / totalDisponibilite);
    int angleEnReparation = static_cast<int>(360.0 * nbEnReparation / totalDisponibilite);
    int angleIndisponible = 360 - angleDisponible - angleEnUtilisation - angleEnReparation;

    startAngle = 0;

    painter.setBrush(Qt::cyan);
    painter.drawPie(rectDisponibilite, startAngle * 16, angleDisponible * 16);
    startAngle += angleDisponible;

    painter.setBrush(Qt::yellow);
    painter.drawPie(rectDisponibilite, startAngle * 16, angleEnUtilisation * 16);
    startAngle += angleEnUtilisation;

    painter.setBrush(Qt::magenta);
    painter.drawPie(rectDisponibilite, startAngle * 16, angleEnReparation * 16);
    startAngle += angleEnReparation;

    painter.setBrush(Qt::darkGray);
    painter.drawPie(rectDisponibilite, startAngle * 16, angleIndisponible * 16);

    painter.setPen(Qt::black);
    painter.setPen(Qt::cyan);
    painter.drawText(420, 280, QString("🟦 Disponible: %1").arg(nbDisponible));

    painter.setPen(Qt::yellow);
    painter.drawText(420, 310, QString("🟡 En Utilisation: %1").arg(nbEnUtilisation));

    painter.setPen(Qt::magenta);
    painter.drawText(420, 340, QString("🟣 En Réparation: %1").arg(nbEnReparation));

    painter.setPen(Qt::darkGray);
    painter.drawText(420, 370, QString("⚫ Indisponible: %1").arg(nbIndisponible));

    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addPixmap(pixmap);


    ui->graphics->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    ui->graphics->setScene(scene);
}

