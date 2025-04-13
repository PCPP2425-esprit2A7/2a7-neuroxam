#include "etudiantdialog.h"
#include "ui_etudiantdialog.h"
#include "connection.h"
#include "etudiantservice.h"
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QDateTime>
#include <QtCharts>
#include <QBarSet>
#include <QBarSeries>
#include <QRegExp>
#include <QPalette>

EtudiantDialog::EtudiantDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EtudiantDialog)
{
    ui->setupUi(this);
    
    // Setup table model
    model = new QSqlTableModel(this, Connection::get_database());
    model->setTable("ETUDIANT");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    
    // Set headers
    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("Name"));
    model->setHeaderData(2, Qt::Horizontal, tr("Family Name"));
    model->setHeaderData(3, Qt::Horizontal, tr("CIN"));
    model->setHeaderData(4, Qt::Horizontal, tr("Speciality"));
    model->setHeaderData(5, Qt::Horizontal, tr("Note"));
    model->setHeaderData(6, Qt::Horizontal, tr("Gender"));
    model->setHeaderData(7, Qt::Horizontal, tr("Phone"));
    model->setHeaderData(8, Qt::Horizontal, tr("Email"));
    model->setHeaderData(9, Qt::Horizontal, tr("Birth Date"));
    model->setHeaderData(10, Qt::Horizontal, tr("Photo Path"));
    
    // Set table view
    ui->studentTableView->setModel(model);
    ui->studentTableView->setSortingEnabled(true);
    ui->studentTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->studentTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->studentTableView->resizeColumnsToContents();
    
    // Setup chart
    setupChart();
    
    // Set default birth date to current date
    ui->birthDateEdit->setDate(QDate::currentDate());
    
    // Connect real-time validation signals
    connect(ui->nameEdit, &QLineEdit::textChanged, this, &EtudiantDialog::validateName);
    connect(ui->familyNameEdit, &QLineEdit::textChanged, this, &EtudiantDialog::validateFamilyName);
    connect(ui->cinEdit, &QLineEdit::textChanged, this, &EtudiantDialog::validateCIN);
    connect(ui->noteEdit, &QLineEdit::textChanged, this, &EtudiantDialog::validateNote);
    connect(ui->emailEdit, &QLineEdit::textChanged, this, &EtudiantDialog::validateEmail);
    connect(ui->phoneEdit, &QLineEdit::textChanged, this, &EtudiantDialog::validatePhone);
    
    // Clear form
    clearInputs();
}

EtudiantDialog::~EtudiantDialog()
{
    delete ui;
}

void EtudiantDialog::on_addButton_clicked()
{
    if (!validateInputs()) {
        return;
    }
    
    QString name = ui->nameEdit->text();
    QString familyName = ui->familyNameEdit->text();
    QString cin = ui->cinEdit->text();
    QString speciality = ui->specialityCombo->currentText();
    double note = ui->noteEdit->text().toDouble();
    QString gender = ui->genderCombo->currentText();
    QString phone = ui->phoneEdit->text();
    QString email = ui->emailEdit->text();
    QDate birthDate = ui->birthDateEdit->date();
    QString photoPath = ui->photoPathEdit->text();
    
    EtudiantService service;
    bool success = service.add(name, familyName, cin, speciality, note, gender, phone, email, birthDate.toString("yyyy-MM-dd"), photoPath);
    
    if (success) {
        QMessageBox::information(this, "Success", "Student added successfully");
        model->select();
        clearInputs();
        updateGenderStats();
    } else {
        QMessageBox::critical(this, "Error", "Failed to add student");
    }
}

void EtudiantDialog::on_updateButton_clicked()
{
    if (!validateInputs()) {
        return;
    }
    
    // Get the selected row
    QModelIndex currentIndex = ui->studentTableView->currentIndex();
    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, "Warning", "Please select a student to update");
        return;
    }
    
    int id = model->data(model->index(currentIndex.row(), 0)).toInt();
    QString name = ui->nameEdit->text();
    QString familyName = ui->familyNameEdit->text();
    QString cin = ui->cinEdit->text();
    QString speciality = ui->specialityCombo->currentText();
    double note = ui->noteEdit->text().toDouble();
    QString gender = ui->genderCombo->currentText();
    QString phone = ui->phoneEdit->text();
    QString email = ui->emailEdit->text();
    QDate birthDate = ui->birthDateEdit->date();
    QString photoPath = ui->photoPathEdit->text();
    
    EtudiantService service;
    bool success = service.update(id, name, familyName, cin, speciality, note, gender, phone, email, birthDate.toString("yyyy-MM-dd"), photoPath);
    
    if (success) {
        QMessageBox::information(this, "Success", "Student updated successfully");
        model->select();
        clearInputs();
        updateGenderStats();
    } else {
        QMessageBox::critical(this, "Error", "Failed to update student");
    }
}

void EtudiantDialog::on_deleteButton_clicked()
{
    // Get the selected row
    QModelIndex currentIndex = ui->studentTableView->currentIndex();
    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, "Warning", "Please select a student to delete");
        return;
    }
    
    // Show confirmation dialog
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmation", 
                                                               "Are you sure you want to delete this student?",
                                                               QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::No) {
        return;
    }
    
    // Get student ID
    int id = model->data(model->index(currentIndex.row(), 0)).toInt();
    
    EtudiantService service;
    bool success = service.remove(id);
    
    if (success) {
        QMessageBox::information(this, "Success", "Student deleted successfully");
        model->select();
        clearInputs();
        updateGenderStats();
    } else {
        QMessageBox::critical(this, "Error", "Failed to delete student");
    }
}

void EtudiantDialog::on_clearButton_clicked()
{
    clearInputs();
}

void EtudiantDialog::on_searchButton_clicked()
{
    QString searchText = ui->searchEdit->text().trimmed();
    if (searchText.isEmpty()) {
        model->setFilter("");
    } else {
        // Search in multiple columns using uppercase column names for Oracle
        model->setFilter(QString("UPPER(NAME) LIKE UPPER('%%1%') OR UPPER(FAMILY_NAME) LIKE UPPER('%%1%') OR UPPER(CIN) LIKE UPPER('%%1%')").arg(searchText));
    }
}

void EtudiantDialog::on_sortButton_clicked()
{
    model->sort(1, Qt::AscendingOrder); // Sort by NAME (column 1)
}

void EtudiantDialog::on_browseButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Select Photo", "", "Images (*.png *.jpg *.jpeg)");
    if (!filename.isEmpty()) {
        ui->photoPathEdit->setText(filename);
        
        // Display the image
        QPixmap pixmap(filename);
        ui->photoLabel->setPixmap(pixmap.scaled(120, 120, Qt::KeepAspectRatio));
    }
}

void EtudiantDialog::on_studentTableView_clicked(const QModelIndex &index)
{
    if (!index.isValid()) {
        return;
    }
    
    int studentId = model->data(model->index(index.row(), 0)).toInt();
    loadStudentToForm(studentId);
}

void EtudiantDialog::on_refreshStatsButton_clicked()
{
    updateGenderStats();
}

void EtudiantDialog::on_exportPdfButton_clicked()
{
    // Get printer
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("students_report.pdf");
    printer.setPageMargins(QMarginsF(15, 15, 15, 15));
    
    QPainter painter;
    if (!painter.begin(&printer)) {
        QMessageBox::critical(this, "Error", "Could not open PDF file for writing");
        return;
    }
    
    // Set the font
    QFont font = painter.font();
    font.setPointSize(12);
    painter.setFont(font);
    
    // Draw title
    font.setPointSize(18);
    font.setBold(true);
    painter.setFont(font);
    painter.drawText(QRect(0, 0, printer.width(), 50), Qt::AlignHCenter | Qt::AlignTop, "Student Management Report");
    
    // Reset font
    font.setPointSize(12);
    font.setBold(false);
    painter.setFont(font);
    
    // Draw timestamp
    QString timestamp = "Generated on: " + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    painter.drawText(QRect(0, 50, printer.width(), 20), Qt::AlignRight, timestamp);
    
    // Draw table headers
    font.setBold(true);
    painter.setFont(font);
    int yPos = 100;
    painter.drawText(QRect(0, yPos, 50, 30), Qt::AlignLeft, "ID");
    painter.drawText(QRect(50, yPos, 100, 30), Qt::AlignLeft, "Name");
    painter.drawText(QRect(150, yPos, 100, 30), Qt::AlignLeft, "Family Name");
    painter.drawText(QRect(250, yPos, 80, 30), Qt::AlignLeft, "CIN");
    painter.drawText(QRect(330, yPos, 100, 30), Qt::AlignLeft, "Speciality");
    painter.drawText(QRect(430, yPos, 50, 30), Qt::AlignLeft, "Note");
    painter.drawText(QRect(480, yPos, 70, 30), Qt::AlignLeft, "Gender");
    
    // Reset font
    font.setBold(false);
    painter.setFont(font);
    
    // Draw table rows
    yPos += 30;
    for (int row = 0; row < model->rowCount(); ++row) {
        painter.drawText(QRect(0, yPos, 50, 20), Qt::AlignLeft, model->data(model->index(row, 0)).toString());
        painter.drawText(QRect(50, yPos, 100, 20), Qt::AlignLeft, model->data(model->index(row, 1)).toString());
        painter.drawText(QRect(150, yPos, 100, 20), Qt::AlignLeft, model->data(model->index(row, 2)).toString());
        painter.drawText(QRect(250, yPos, 80, 20), Qt::AlignLeft, model->data(model->index(row, 3)).toString());
        painter.drawText(QRect(330, yPos, 100, 20), Qt::AlignLeft, model->data(model->index(row, 4)).toString());
        painter.drawText(QRect(430, yPos, 50, 20), Qt::AlignLeft, model->data(model->index(row, 5)).toString());
        painter.drawText(QRect(480, yPos, 70, 20), Qt::AlignLeft, model->data(model->index(row, 6)).toString());
        
        yPos += 20;
        
        // Check if we need to start a new page
        if (yPos > printer.height() - 40) {
            printer.newPage();
            yPos = 40;
        }
    }
    
    // End painting
    painter.end();
    
    QMessageBox::information(this, "Success", "PDF report generated successfully: students_report.pdf");
}

void EtudiantDialog::loadStudents()
{
    model->select();
}

void EtudiantDialog::clearInputs()
{
    ui->nameEdit->clear();
    ui->familyNameEdit->clear();
    ui->cinEdit->clear();
    ui->specialityCombo->setCurrentIndex(0);
    ui->noteEdit->clear();
    ui->genderCombo->setCurrentIndex(0);
    ui->phoneEdit->clear();
    ui->emailEdit->clear();
    ui->birthDateEdit->setDate(QDate::currentDate());
    ui->photoPathEdit->clear();
    ui->photoLabel->clear();
    ui->searchEdit->clear();
    
    // Reset styling for all input fields
    ui->nameEdit->setStyleSheet("");
    ui->familyNameEdit->setStyleSheet("");
    ui->cinEdit->setStyleSheet("");
    ui->specialityCombo->setStyleSheet("");
    ui->noteEdit->setStyleSheet("");
    ui->genderCombo->setStyleSheet("");
    ui->phoneEdit->setStyleSheet("");
    ui->emailEdit->setStyleSheet("");
    
    // Reset tooltips
    ui->nameEdit->setToolTip("");
    ui->familyNameEdit->setToolTip("");
    ui->cinEdit->setToolTip("");
    ui->specialityCombo->setToolTip("");
    ui->noteEdit->setToolTip("");
    ui->genderCombo->setToolTip("");
    ui->phoneEdit->setToolTip("");
    ui->emailEdit->setToolTip("");
    
    // Reset table filter
    model->setFilter("");
    
    // Remove selection
    ui->studentTableView->clearSelection();
}

void EtudiantDialog::loadStudentToForm(int studentId)
{
    EtudiantService service;
    Etudiant etudiant = service.getById(studentId);
    
    if (etudiant.getId() > 0) {
        ui->nameEdit->setText(etudiant.getName());
        ui->familyNameEdit->setText(etudiant.getFamilyName());
        ui->cinEdit->setText(etudiant.getCin());
        ui->specialityCombo->setCurrentText(etudiant.getSpeciality());
        ui->noteEdit->setText(QString::number(etudiant.getNote(), 'f', 2));
        ui->genderCombo->setCurrentText(etudiant.getGender());
        ui->phoneEdit->setText(etudiant.getPhoneNumber());
        ui->emailEdit->setText(etudiant.getEmail());
        ui->birthDateEdit->setDate(etudiant.getBirthDate());
        
        QString photoPath = etudiant.getPhotoPath();
        ui->photoPathEdit->setText(photoPath);
        
        // Display image if exists
        if (!photoPath.isEmpty()) {
            QPixmap pixmap(photoPath);
            if (!pixmap.isNull()) {
                ui->photoLabel->setPixmap(pixmap.scaled(120, 120, Qt::KeepAspectRatio));
            }
        } else {
            ui->photoLabel->clear();
        }
        
        // Trigger validation on loaded data
        validateName();
        validateFamilyName();
        validateCIN();
        validateNote();
        validateEmail();
        validatePhone();
    }
}

void EtudiantDialog::setupChart()
{
    // Create chart
    genderChart = new QChart();
    genderChart->setTitle("Students by Gender");
    genderChart->setAnimationOptions(QChart::SeriesAnimations);
    
    // Create chart view
    chartView = new QChartView(genderChart);
    chartView->setRenderHint(QPainter::Antialiasing);
    
    // Add chart to layout
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(chartView);
    ui->chartWidget->setLayout(layout);
    
    // Update chart data
    updateGenderStats();
}

void EtudiantDialog::updateGenderStats()
{
    // Clear old series
    genderChart->removeAllSeries();
    
    // Get gender counts from database
    QSqlQuery query(Connection::get_database());
    query.prepare("SELECT gender, COUNT(*) as count FROM ETUDIANT GROUP BY gender");
    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to fetch gender statistics");
        return;
    }
    
    // Create pie series
    QPieSeries *series = new QPieSeries();
    
    // Fill series with data
    int maleCount = 0;
    int femaleCount = 0;
    
    while (query.next()) {
        QString gender = query.value("gender").toString();
        int count = query.value("count").toInt();
        
        if (gender.toLower() == "male") {
            maleCount = count;
        } else if (gender.toLower() == "female") {
            femaleCount = count;
        }
        
        series->append(gender, count);
    }
    
    // Update statistics labels
    ui->maleCountLabel->setText(QString::number(maleCount));
    ui->femaleCountLabel->setText(QString::number(femaleCount));
    ui->totalCountLabel->setText(QString::number(maleCount + femaleCount));
    
    // Configure series
    series->setLabelsVisible(true);
    series->setLabelsPosition(QPieSlice::LabelOutside);
    
    for (auto slice : series->slices()) {
        slice->setLabel(QString("%1: %2 (%3%)").arg(slice->label())
                        .arg(slice->value())
                        .arg(100 * slice->percentage(), 0, 'f', 1));
    }
    
    // Add series to chart
    genderChart->addSeries(series);
    genderChart->legend()->setAlignment(Qt::AlignBottom);
    
    // Refresh chart
    chartView->repaint();
}

bool EtudiantDialog::validateInputs()
{
    bool isValid = true;
    
    // Name validation
    QString name = ui->nameEdit->text().trimmed();
    bool nameValid = !name.isEmpty() && name.length() >= 2;
    setValidationStatus(ui->nameEdit, nameValid, nameValid ? "" : "Name must be at least 2 characters");
    isValid = isValid && nameValid;
    
    // Family name validation
    QString familyName = ui->familyNameEdit->text().trimmed();
    bool familyNameValid = !familyName.isEmpty() && familyName.length() >= 2;
    setValidationStatus(ui->familyNameEdit, familyNameValid, familyNameValid ? "" : "Family name must be at least 2 characters");
    isValid = isValid && familyNameValid;
    
    // CIN validation
    QString cin = ui->cinEdit->text().trimmed();
    bool cinValid = isValidCIN(cin);
    setValidationStatus(ui->cinEdit, cinValid, cinValid ? "" : "CIN must be in the format: 1-2 letters followed by 6-8 digits");
    isValid = isValid && cinValid;
    
    // Speciality validation
    QString speciality = ui->specialityCombo->currentText().trimmed();
    bool specialityValid = !speciality.isEmpty();
    setValidationStatus(ui->specialityCombo, specialityValid, specialityValid ? "" : "Speciality is required");
    isValid = isValid && specialityValid;
    
    // Note validation
    QString noteText = ui->noteEdit->text().trimmed();
    bool convertOk;
    double note = noteText.toDouble(&convertOk);
    bool noteValid = convertOk && note >= 0 && note <= 20;
    setValidationStatus(ui->noteEdit, noteValid, noteValid ? "" : "Note must be a number between 0 and 20");
    isValid = isValid && noteValid;
    
    // Phone validation
    QString phone = ui->phoneEdit->text().trimmed();
    bool phoneValid = phone.isEmpty() || isValidPhone(phone);
    setValidationStatus(ui->phoneEdit, phoneValid, phoneValid ? "" : "Phone must have 8-15 digits (optionally with + prefix)");
    isValid = isValid && phoneValid;
    
    // Email validation
    QString email = ui->emailEdit->text().trimmed();
    bool emailValid = email.isEmpty() || isValidEmail(email);
    setValidationStatus(ui->emailEdit, emailValid, emailValid ? "" : "Invalid email format");
    isValid = isValid && emailValid;
    
    // Birth date validation
    QDate birthDate = ui->birthDateEdit->date();
    bool dateNotFuture = birthDate <= QDate::currentDate();
    bool dateNotTooOld = birthDate.addYears(100) >= QDate::currentDate();
    bool birthDateValid = dateNotFuture && dateNotTooOld;
    
    QString dateTooltip = "";
    if (!dateNotFuture) {
        dateTooltip = "Birth date cannot be in the future";
    } else if (!dateNotTooOld) {
        dateTooltip = "Birth date is too far in the past";
    }
    
    // Special case for date widgets which don't have the same styling
    ui->birthDateEdit->setToolTip(dateTooltip);
    isValid = isValid && birthDateValid;
    
    // If any validation fails, show a message for the first error
    if (!isValid) {
        if (!nameValid) {
            QMessageBox::warning(this, "Validation Error", "Name must be at least 2 characters");
            ui->nameEdit->setFocus();
        } else if (!familyNameValid) {
            QMessageBox::warning(this, "Validation Error", "Family name must be at least 2 characters");
            ui->familyNameEdit->setFocus();
        } else if (!cinValid) {
            QMessageBox::warning(this, "Validation Error", "CIN must be in the format: 1-2 letters followed by 6-8 digits");
            ui->cinEdit->setFocus();
        } else if (!specialityValid) {
            QMessageBox::warning(this, "Validation Error", "Speciality is required");
            ui->specialityCombo->setFocus();
        } else if (!noteValid) {
            QMessageBox::warning(this, "Validation Error", "Note must be a number between 0 and 20");
            ui->noteEdit->setFocus();
        } else if (!phoneValid) {
            QMessageBox::warning(this, "Validation Error", "Phone must have 8-15 digits (optionally with + prefix)");
            ui->phoneEdit->setFocus();
        } else if (!emailValid) {
            QMessageBox::warning(this, "Validation Error", "Invalid email format");
            ui->emailEdit->setFocus();
        } else if (!birthDateValid) {
            QMessageBox::warning(this, "Validation Error", dateTooltip);
            ui->birthDateEdit->setFocus();
        }
    }
    
    return isValid;
}

// Validation handlers
void EtudiantDialog::validateName()
{
    QString name = ui->nameEdit->text().trimmed();
    bool isValid = !name.isEmpty() && name.length() >= 2;
    QString toolTip = isValid ? "" : "Name must be at least 2 characters";
    setValidationStatus(ui->nameEdit, isValid, toolTip);
}

void EtudiantDialog::validateFamilyName()
{
    QString familyName = ui->familyNameEdit->text().trimmed();
    bool isValid = !familyName.isEmpty() && familyName.length() >= 2;
    QString toolTip = isValid ? "" : "Family name must be at least 2 characters";
    setValidationStatus(ui->familyNameEdit, isValid, toolTip);
}

void EtudiantDialog::validateCIN()
{
    QString cin = ui->cinEdit->text().trimmed();
    bool isValid = isValidCIN(cin);
    QString toolTip = isValid ? "" : "CIN must be 1-2 letters followed by 6-8 digits";
    setValidationStatus(ui->cinEdit, isValid, toolTip);
}

void EtudiantDialog::validateNote()
{
    QString noteText = ui->noteEdit->text().trimmed();
    bool convertOk;
    double note = noteText.toDouble(&convertOk);
    bool isValid = convertOk && note >= 0 && note <= 20;
    QString toolTip = isValid ? "" : "Note must be a number between 0 and 20";
    setValidationStatus(ui->noteEdit, isValid, toolTip);
}

void EtudiantDialog::validateEmail()
{
    QString email = ui->emailEdit->text().trimmed();
    bool isValid = email.isEmpty() || isValidEmail(email);
    QString toolTip = isValid ? "" : "Invalid email format";
    setValidationStatus(ui->emailEdit, isValid, toolTip);
}

void EtudiantDialog::validatePhone()
{
    QString phone = ui->phoneEdit->text().trimmed();
    bool isValid = phone.isEmpty() || isValidPhone(phone);
    QString toolTip = isValid ? "" : "Phone must have 8-15 digits (optionally with + prefix)";
    setValidationStatus(ui->phoneEdit, isValid, toolTip);
}

void EtudiantDialog::setValidationStatus(QWidget *widget, bool isValid, const QString &toolTip)
{
    QPalette palette = widget->palette();
    if (QLineEdit *lineEdit = qobject_cast<QLineEdit*>(widget)) {
        if (isValid) {
            lineEdit->setStyleSheet("QLineEdit { background-color: white; }");
        } else {
            lineEdit->setStyleSheet("QLineEdit { background-color: #FFEEEE; }");
        }
        lineEdit->setToolTip(toolTip);
    } else if (QComboBox *comboBox = qobject_cast<QComboBox*>(widget)) {
        if (isValid) {
            comboBox->setStyleSheet("QComboBox { background-color: white; }");
        } else {
            comboBox->setStyleSheet("QComboBox { background-color: #FFEEEE; }");
        }
        comboBox->setToolTip(toolTip);
    }
}

bool EtudiantDialog::isValidCIN(const QString &cin)
{
    if (cin.isEmpty()) {
        return false;
    }
    QRegExp cinRegex("^[A-Za-z]{1,2}\\d{6,8}$");
    return cinRegex.exactMatch(cin);
}

bool EtudiantDialog::isValidEmail(const QString &email)
{
    QRegExp emailRegex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    return emailRegex.exactMatch(email);
}

bool EtudiantDialog::isValidPhone(const QString &phone)
{
    QRegExp phoneRegex("^\\+?[0-9]{8,15}$");
    return phoneRegex.exactMatch(phone);
} 