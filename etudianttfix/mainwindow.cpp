#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chatdialog.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QPixmap>
#include <QRegularExpressionValidator>
#include <QDate>
#include <QBarSet>
#include <QBarSeries>
#include <QChart>
#include <QChartView>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QtCharts>
#include <QPushButton>
#include <QMenu>
#include <QAction>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), model(new QStandardItemModel(this)),
      currentStudentId(-1)
{
    ui->setupUi(this);
    setupTable();
    setupValidators();
    setupConnections();
    
    // Add the AI Assistant menu item
    QMenu *toolsMenu = menuBar()->addMenu("Outils");
    QAction *aiAction = new QAction("Assistant IA", this);
    aiAction->setStatusTip("Ouvrir l'assistant IA pour analyser les données étudiants");
    connect(aiAction, &QAction::triggered, this, &MainWindow::onOpenChatDialog);
    toolsMenu->addAction(aiAction);
    
    loadStudents();
}

MainWindow::~MainWindow() { 
    delete ui; 
}

void MainWindow::setupTable() {
    ui->tableView->setModel(model);
    model->setHorizontalHeaderLabels({"ID", "CIN", "Nom", "Prénom", "Spécialité", "Note"});
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::setupValidators() {
    // Set validator for numeric fields
    QRegularExpressionValidator *numValidator = new QRegularExpressionValidator(QRegularExpression("[0-9]*"), this);
    ui->cinEdit->setValidator(numValidator);
    ui->phoneEdit->setValidator(numValidator);
    
    // Set validator for email
    QRegularExpressionValidator *emailValidator = new QRegularExpressionValidator(
        QRegularExpression("[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}"), this);
    ui->emailEdit->setValidator(emailValidator);
    
    // Set up date picker
    ui->birthDateEdit->setDisplayFormat("dd/MM/yyyy");
    ui->birthDateEdit->setCalendarPopup(true);
    ui->birthDateEdit->setMaximumDate(QDate::currentDate());
    
    // Set up gender combo box
    ui->genderCombo->addItems({"Homme", "Femme"});
    
    // Set up sorting combo box
    ui->sortCombo->addItems({"id", "name", "family_name", "cin", "speciality", "note"});
}

void MainWindow::setupConnections() {
    // Connect button signals
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::onAddStudent);
    connect(ui->updateButton, &QPushButton::clicked, this, &MainWindow::onUpdateStudent);
    connect(ui->deleteButton, &QPushButton::clicked, this, &MainWindow::onDeleteStudent);
    connect(ui->sortCombo, &QComboBox::currentTextChanged, this, &MainWindow::onSortStudents);
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::onSearch);
    connect(ui->statsButton, &QPushButton::clicked, this, &MainWindow::onShowStats);
    connect(ui->pdfButton, &QPushButton::clicked, this, &MainWindow::onSavePDF);
    connect(ui->studentPdfButton, &QPushButton::clicked, this, &MainWindow::onSaveStudentPDF);
    connect(ui->browseButton, &QPushButton::clicked, this, &MainWindow::onBrowseImage);
    connect(ui->clearButton, &QPushButton::clicked, this, &MainWindow::clearFields);
    
    // Connect table selection
    connect(ui->tableView->selectionModel(), &QItemSelectionModel::selectionChanged, 
            [this](const QItemSelection &selected, const QItemSelection &) {
                if (!selected.indexes().isEmpty()) {
                    int row = selected.indexes().first().row();
                    int id = model->data(model->index(row, 0)).toInt();
                    onLoadStudentDetails(id);
                }
            });
}

void MainWindow::loadStudents(const QString &sortBy) {
    model->removeRows(0, model->rowCount());
    QList<Etudiant> students = sortBy.isEmpty() ? service.getAll() : service.getSortedBy(sortBy);
    
    for (const Etudiant &e : students) {
        QList<QStandardItem *> row;
        row << new QStandardItem(QString::number(e.getId()))
            << new QStandardItem(e.getCin())
            << new QStandardItem(e.getName())
            << new QStandardItem(e.getFamilyName())
            << new QStandardItem(e.getSpeciality())
            << new QStandardItem(QString::number(e.getNote(), 'f', 2));
        model->appendRow(row);
    }
    
    ui->tableView->resizeColumnsToContents();
}

void MainWindow::onAddStudent() {
    QString name = ui->nameEdit->text();
    QString familyName = ui->familyNameEdit->text();
    QString cin = ui->cinEdit->text();
    QString speciality = ui->specialityEdit->text();
    float note = ui->noteEdit->text().toFloat();
    QString phoneNumber = ui->phoneEdit->text();
    QString email = ui->emailEdit->text();
    QDate birthDate = ui->birthDateEdit->date();
    QString gender = ui->genderCombo->currentText();
    
    if (name.isEmpty() || familyName.isEmpty() || cin.isEmpty() || speciality.isEmpty() || 
        phoneNumber.isEmpty() || email.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Veuillez remplir tous les champs obligatoires.");
        return;
    }
    
    // Save the image if selected
    QString savedPhotoPath;
    if (!currentPhotoPath.isEmpty()) {
        if (!service.saveImage(currentPhotoPath, savedPhotoPath)) {
            QMessageBox::warning(this, "Erreur Image", "Impossible de sauvegarder l'image.");
            return;
        }
    }
    
    Etudiant etudiant(name, familyName, cin, speciality, note, savedPhotoPath, 
                      phoneNumber, email, birthDate, gender);
    
    if (service.add(etudiant)) {
        QMessageBox::information(this, "Succès", "Étudiant ajouté avec succès.");
        loadStudents();
        clearFields();
    } else {
        QMessageBox::critical(this, "Erreur", "Impossible d'ajouter l'étudiant.");
    }
}

void MainWindow::onUpdateStudent() {
    if (currentStudentId < 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un étudiant à modifier.");
        return;
    }
    
    QString name = ui->nameEdit->text();
    QString familyName = ui->familyNameEdit->text();
    QString cin = ui->cinEdit->text();
    QString speciality = ui->specialityEdit->text();
    float note = ui->noteEdit->text().toFloat();
    QString phoneNumber = ui->phoneEdit->text();
    QString email = ui->emailEdit->text();
    QDate birthDate = ui->birthDateEdit->date();
    QString gender = ui->genderCombo->currentText();
    
    if (name.isEmpty() || familyName.isEmpty() || cin.isEmpty() || speciality.isEmpty() || 
        phoneNumber.isEmpty() || email.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Veuillez remplir tous les champs obligatoires.");
        return;
    }

    // Get the current student to preserve the photo path if not changed
    Etudiant currentStudent = service.getById(currentStudentId);
    QString photoPath = currentStudent.getPhotoPath();
    
    // Update the photo if a new one was selected
    if (!currentPhotoPath.isEmpty() && currentPhotoPath != photoPath) {
        QString savedPhotoPath;
        if (!service.saveImage(currentPhotoPath, savedPhotoPath)) {
            QMessageBox::warning(this, "Erreur Image", "Impossible de sauvegarder l'image.");
            return;
        }
        photoPath = savedPhotoPath;
    }
    
    Etudiant updatedStudent(currentStudentId, name, familyName, cin, speciality, note, 
                           photoPath, phoneNumber, email, birthDate, gender);
    
    if (service.update(updatedStudent)) {
        QMessageBox::information(this, "Succès", "Étudiant modifié avec succès.");
        loadStudents();
        clearFields();
        currentStudentId = -1;
    } else {
        QMessageBox::critical(this, "Erreur", "Impossible de modifier l'étudiant.");
    }
}

void MainWindow::onDeleteStudent() {
    if (currentStudentId < 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un étudiant à supprimer.");
        return;
    }
    
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmation",
        "Êtes-vous sûr de vouloir supprimer cet étudiant ?", 
        QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        if (service.remove(currentStudentId)) {
            QMessageBox::information(this, "Succès", "Étudiant supprimé avec succès.");
            loadStudents();
            clearFields();
            currentStudentId = -1;
        } else {
            QMessageBox::critical(this, "Erreur", "Impossible de supprimer l'étudiant.");
        }
    }
}

void MainWindow::onSortStudents(const QString &criteria) {
    loadStudents(criteria);
}

void MainWindow::onSearch() {
    QString criteria = ui->searchFieldCombo->currentText();
    QString value = ui->searchValueEdit->text();
    
    if (value.isEmpty()) {
        loadStudents();
        return;
    }
    
    model->removeRows(0, model->rowCount());
    QList<Etudiant> students = service.searchByCriteria(criteria, value);
    
    for (const Etudiant &e : students) {
        QList<QStandardItem *> row;
        row << new QStandardItem(QString::number(e.getId()))
            << new QStandardItem(e.getCin())
            << new QStandardItem(e.getName())
            << new QStandardItem(e.getFamilyName())
            << new QStandardItem(e.getSpeciality())
            << new QStandardItem(QString::number(e.getNote(), 'f', 2));
        model->appendRow(row);
    }
}

void MainWindow::onShowStats() {
    // Get statistics
    QMap<QString, int> studentsBySpeciality = service.getStatsBySpeciality();
    QMap<QString, double> avgNoteBySpeciality = service.getAverageNoteBySpeciality();
    
    if (studentsBySpeciality.isEmpty()) {
        QMessageBox::information(this, "Statistiques", "Aucune donnée à afficher.");
        return;
    }
    
    // Create chart for students by speciality
    QBarSet *set = new QBarSet("Nombre d'étudiants");
    QStringList categories;
    
    for (auto it = studentsBySpeciality.constBegin(); it != studentsBySpeciality.constEnd(); ++it) {
        *set << it.value();
        categories << it.key();
    }
    
    QBarSeries *series = new QBarSeries();
    series->append(set);
    
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des étudiants par spécialité");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, set->at(set->count() - 1) + 5);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    
    // Create a dialog to display the chart
    QDialog dialog(this);
    dialog.setWindowTitle("Statistiques");
    dialog.resize(800, 600);
    
    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    layout->addWidget(chartView);
    
    dialog.exec();
}

void MainWindow::onSavePDF() {
    QString filename = QFileDialog::getSaveFileName(this, "Enregistrer en PDF", 
                                                   QDir::homePath(), "PDF (*.pdf)");
    if (filename.isEmpty()) return;
    
    if (!filename.endsWith(".pdf")) filename += ".pdf";
    
    if (service.generatePDF(filename, service.getAll())) {
        QMessageBox::information(this, "Succès", "Le PDF a été généré avec succès.");
    } else {
        QMessageBox::critical(this, "Erreur", "Impossible de générer le PDF.");
    }
}

void MainWindow::onSaveStudentPDF() {
    if (currentStudentId < 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un étudiant.");
        return;
    }
    
    QString filename = QFileDialog::getSaveFileName(this, "Enregistrer en PDF", 
                                                   QDir::homePath(), "PDF (*.pdf)");
    if (filename.isEmpty()) return;
    
    if (!filename.endsWith(".pdf")) filename += ".pdf";
    
    Etudiant student = service.getById(currentStudentId);
    if (service.generateStudentPDF(filename, student)) {
        QMessageBox::information(this, "Succès", "Le PDF a été généré avec succès.");
    } else {
        QMessageBox::critical(this, "Erreur", "Impossible de générer le PDF.");
    }
}

void MainWindow::onBrowseImage() {
    QString filePath = QFileDialog::getOpenFileName(this, "Sélectionner une image", 
                                                  QDir::homePath(), 
                                                  "Images (*.png *.jpg *.jpeg)");
    if (filePath.isEmpty()) return;
    
    currentPhotoPath = filePath;
    
    // Display the selected image
    QPixmap pixmap(filePath);
    ui->photoLabel->setPixmap(pixmap.scaled(ui->photoLabel->size(), Qt::KeepAspectRatio));
}

void MainWindow::onLoadStudentDetails(int studentId) {
    Etudiant student = service.getById(studentId);
    if (student.getId() <= 0) return;
    
    currentStudentId = student.getId();
    
    ui->nameEdit->setText(student.getName());
    ui->familyNameEdit->setText(student.getFamilyName());
    ui->cinEdit->setText(student.getCin());
    ui->specialityEdit->setText(student.getSpeciality());
    ui->noteEdit->setText(QString::number(student.getNote(), 'f', 2));
    ui->phoneEdit->setText(student.getPhoneNumber());
    ui->emailEdit->setText(student.getEmail());
    ui->birthDateEdit->setDate(student.getBirthDate());
    
    int genderIndex = ui->genderCombo->findText(student.getGender());
    if (genderIndex >= 0) {
        ui->genderCombo->setCurrentIndex(genderIndex);
    }
    
    // Display student photo if available
    if (!student.getPhotoPath().isEmpty()) {
        QPixmap pixmap(student.getPhotoPath());
        if (!pixmap.isNull()) {
            ui->photoLabel->setPixmap(pixmap.scaled(ui->photoLabel->size(), Qt::KeepAspectRatio));
            currentPhotoPath = student.getPhotoPath();
        } else {
            ui->photoLabel->clear();
            currentPhotoPath.clear();
        }
    } else {
        ui->photoLabel->clear();
        currentPhotoPath.clear();
    }
}

void MainWindow::clearFields() {
    ui->nameEdit->clear();
    ui->familyNameEdit->clear();
    ui->cinEdit->clear();
    ui->specialityEdit->clear();
    ui->noteEdit->clear();
    ui->phoneEdit->clear();
    ui->emailEdit->clear();
    ui->birthDateEdit->setDate(QDate::currentDate());
    ui->genderCombo->setCurrentIndex(0);
    ui->photoLabel->clear();
    
    currentPhotoPath.clear();
    currentStudentId = -1;
}

void MainWindow::onOpenChatDialog()
{
    ChatDialog* chatDialog = new ChatDialog(this);
    chatDialog->setModal(true);
    chatDialog->setAttribute(Qt::WA_DeleteOnClose);
    chatDialog->show();
}
