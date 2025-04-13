#include "etudiantservice.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSqlDatabase>
#include <QVariant>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QDateTime>
#include <QPdfWriter>
#include <QPainter>
#include <QTextDocument>

EtudiantService::EtudiantService()
{
    // Ensure the database connection is established when service is created
    if (!QSqlDatabase::database().isValid()) {
        qDebug() << "Database connection not established in EtudiantService constructor";
    } else {
        // Create the table if it doesn't exist
        createTableIfNotExists();
    }
}

bool EtudiantService::createTableIfNotExists()
{
    QSqlQuery query;
    
    // Create the ETUDIANT table if it doesn't exist
    QString createTableQuery = 
        "CREATE TABLE IF NOT EXISTS ETUDIANT ("
        "ID INTEGER PRIMARY KEY, "
        "NAME TEXT, "
        "FAMILY_NAME TEXT, "
        "CIN TEXT, "
        "SPECIALITY TEXT, "
        "NOTE REAL, "
        "GENDER TEXT, "
        "PHONE TEXT, "
        "EMAIL TEXT, "
        "BIRTH_DATE TEXT, "
        "PHOTO_PATH TEXT)";
    
    if (!query.exec(createTableQuery)) {
        qDebug() << "Failed to create ETUDIANT table:" << query.lastError().text();
        return false;
    }
    
    qDebug() << "ETUDIANT table verified or created";
    return true;
}

bool EtudiantService::add(const Etudiant &etudiant) {
    QSqlQuery query;
    
    // Get the next available ID
    int newId = getNextId();
    
    // Print debug information
    qDebug() << "Adding student with ID:" << newId;
    
    // Use simpler query with consistent column names
    query.prepare("INSERT INTO ETUDIANT (ID, NAME, FAMILY_NAME, CIN, SPECIALITY, NOTE, GENDER, PHONE, EMAIL, BIRTH_DATE, PHOTO_PATH) "
                 "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
    
    query.addBindValue(newId);
    query.addBindValue(etudiant.getName());
    query.addBindValue(etudiant.getFamilyName());
    query.addBindValue(etudiant.getCin());
    query.addBindValue(etudiant.getSpeciality());
    query.addBindValue(etudiant.getNote());
    query.addBindValue(etudiant.getGender());
    query.addBindValue(etudiant.getPhoneNumber());
    query.addBindValue(etudiant.getEmail());
    query.addBindValue(etudiant.getBirthDate().toString("yyyy-MM-dd"));
    query.addBindValue(etudiant.getPhotoPath());

    if (!query.exec()) {
        qDebug() << "Add failed:" << query.lastError().text();
        return false;
    }
    return true;
}

bool EtudiantService::add(const QString &name, const QString &familyName, const QString &cin, 
                        const QString &speciality, double note, const QString &gender,
                        const QString &phone, const QString &email, const QString &birthDate,
                        const QString &photoPath)
{
    QSqlQuery query;
    
    // Get the next available ID
    int newId = getNextId();
    
    // Print debug information
    qDebug() << "Adding student with ID:" << newId;
    
    // Use simpler query with consistent column names and positional parameters
    query.prepare("INSERT INTO ETUDIANT (ID, NAME, FAMILY_NAME, CIN, SPECIALITY, NOTE, GENDER, PHONE, EMAIL, BIRTH_DATE, PHOTO_PATH) "
                 "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
    
    query.addBindValue(newId);
    query.addBindValue(name);
    query.addBindValue(familyName);
    query.addBindValue(cin);
    query.addBindValue(speciality);
    query.addBindValue(note);
    query.addBindValue(gender);
    query.addBindValue(phone);
    query.addBindValue(email);
    query.addBindValue(birthDate);
    query.addBindValue(photoPath);
    
    if (!query.exec()) {
        qDebug() << "Error adding student: " << query.lastError().text();
        qDebug() << "SQL query: " << query.lastQuery();
        return false;
    }
    
    return true;
}

bool EtudiantService::update(const Etudiant &etudiant) {
    QSqlQuery query;
    query.prepare("UPDATE ETUDIANT SET NAME = ?, FAMILY_NAME = ?, "
                  "CIN = ?, SPECIALITY = ?, NOTE = ?, "
                  "GENDER = ?, PHONE = ?, EMAIL = ?, BIRTH_DATE = ?, PHOTO_PATH = ? "
                  "WHERE ID = ?");
                   
    query.addBindValue(etudiant.getName());
    query.addBindValue(etudiant.getFamilyName());
    query.addBindValue(etudiant.getCin());
    query.addBindValue(etudiant.getSpeciality());
    query.addBindValue(etudiant.getNote());
    query.addBindValue(etudiant.getGender());
    query.addBindValue(etudiant.getPhoneNumber());
    query.addBindValue(etudiant.getEmail());
    query.addBindValue(etudiant.getBirthDate().toString("yyyy-MM-dd"));
    query.addBindValue(etudiant.getPhotoPath());
    query.addBindValue(etudiant.getId());

    if (!query.exec()) {
        qDebug() << "Update failed:" << query.lastError().text();
        qDebug() << "SQL query: " << query.lastQuery();
        return false;
    }
    return query.numRowsAffected() > 0;
}

bool EtudiantService::update(int id, const QString &name, const QString &familyName, const QString &cin, 
                           const QString &speciality, double note, const QString &gender,
                           const QString &phone, const QString &email, const QString &birthDate,
                           const QString &photoPath)
{
    QSqlQuery query;
    query.prepare("UPDATE ETUDIANT SET NAME = ?, FAMILY_NAME = ?, CIN = ?, "
                 "SPECIALITY = ?, NOTE = ?, GENDER = ?, PHONE = ?, "
                 "EMAIL = ?, BIRTH_DATE = ?, PHOTO_PATH = ? "
                 "WHERE ID = ?");
    
    query.addBindValue(name);
    query.addBindValue(familyName);
    query.addBindValue(cin);
    query.addBindValue(speciality);
    query.addBindValue(note);
    query.addBindValue(gender);
    query.addBindValue(phone);
    query.addBindValue(email);
    query.addBindValue(birthDate);
    query.addBindValue(photoPath);
    query.addBindValue(id);
    
    if (!query.exec()) {
        qDebug() << "Error updating student: " << query.lastError().text();
        qDebug() << "SQL query: " << query.lastQuery();
        return false;
    }
    
    return true;
}

bool EtudiantService::remove(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM ETUDIANT WHERE ID = ?");
    query.addBindValue(id);

    if (!query.exec()) {
        qDebug() << "Delete failed:" << query.lastError().text();
        qDebug() << "SQL query: " << query.lastQuery();
        return false;
    }
    return query.numRowsAffected() > 0;
}

Etudiant EtudiantService::getById(int id) {
    QSqlQuery query;
    query.prepare("SELECT ID, NAME, FAMILY_NAME, CIN, SPECIALITY, NOTE, PHOTO_PATH, "
                  "PHONE, EMAIL, BIRTH_DATE, GENDER "
                  "FROM ETUDIANT WHERE ID = ?");
    query.addBindValue(id);
    
    if (!query.exec()) {
        qDebug() << "Get by ID failed:" << query.lastError().text();
        qDebug() << "SQL query: " << query.lastQuery();
        return Etudiant();
    }
    
    if (!query.next()) {
        qDebug() << "No student found with ID:" << id;
        return Etudiant();
    }
    
    try {
        return Etudiant(
            query.value(0).toInt(),
            query.value(1).toString(),
            query.value(2).toString(),
            query.value(3).toString(),
            query.value(4).toString(),
            query.value(5).toFloat(),
            query.value(6).toString(),
            query.value(7).toString(),
            query.value(8).toString(),
            QDate::fromString(query.value(9).toString(), "yyyy-MM-dd"),
            query.value(10).toString()
        );
    } catch (const std::exception &e) {
        qDebug() << "Exception creating Etudiant object:" << e.what();
        return Etudiant();
    }
}

QList<Etudiant> EtudiantService::getAll() {
    QList<Etudiant> list;
    QSqlQuery query("SELECT ID, NAME, FAMILY_NAME, CIN, SPECIALITY, NOTE, PHOTO_PATH, "
                    "PHONE, EMAIL, BIRTH_DATE, GENDER "
                    "FROM ETUDIANT");

    while (query.next()) {
        list.append(Etudiant(
            query.value(0).toInt(),
            query.value(1).toString(),
            query.value(2).toString(),
            query.value(3).toString(),
            query.value(4).toString(),
            query.value(5).toFloat(),
            query.value(6).toString(),
            query.value(7).toString(),
            query.value(8).toString(),
            QDate::fromString(query.value(9).toString(), "yyyy-MM-dd"),
            query.value(10).toString()
        ));
    }
    return list;
}

QList<Etudiant> EtudiantService::getSortedBy(const QString &column) {
    QList<Etudiant> list;

    if (column.isEmpty()) return getAll();

    // Use proper column names for the SQL query
    QString columnName = column.toUpper();
    
    QString queryStr = QString("SELECT ID, NAME, FAMILY_NAME, CIN, SPECIALITY, NOTE, PHOTO_PATH, "
                              "PHONE, EMAIL, BIRTH_DATE, GENDER "
                              "FROM ETUDIANT ORDER BY %1").arg(columnName);

    QSqlQuery query;
    if (!query.exec(queryStr)) {
        qDebug() << "Sort failed:" << query.lastError().text();
        return list;
    }

    while (query.next()) {
        list.append(Etudiant(
            query.value(0).toInt(),
            query.value(1).toString(),
            query.value(2).toString(),
            query.value(3).toString(),
            query.value(4).toString(),
            query.value(5).toFloat(),
            query.value(6).toString(),
            query.value(7).toString(),
            query.value(8).toString(),
            QDate::fromString(query.value(9).toString(), "yyyy-MM-dd"),
            query.value(10).toString()
        ));
    }

    return list;
}

QList<Etudiant> EtudiantService::searchByCriteria(const QString &criteria, const QString &value) {
    QList<Etudiant> list;
    
    if (criteria.isEmpty() || value.isEmpty()) return getAll();
    
    // Use proper column names for the SQL query
    QString columnName = criteria.toUpper();
    
    QString queryStr = QString("SELECT ID, NAME, FAMILY_NAME, CIN, SPECIALITY, NOTE, PHOTO_PATH, "
                              "PHONE, EMAIL, BIRTH_DATE, GENDER "
                              "FROM ETUDIANT WHERE UPPER(%1) LIKE UPPER(?)").arg(columnName);
    
    QSqlQuery query;
    query.prepare(queryStr);
    query.addBindValue("%" + value + "%");
    
    if (!query.exec()) {
        qDebug() << "Search failed:" << query.lastError().text();
        qDebug() << "SQL query: " << query.lastQuery();
        return list;
    }
    
    while (query.next()) {
        try {
            list.append(Etudiant(
                query.value(0).toInt(),
                query.value(1).toString(),
                query.value(2).toString(),
                query.value(3).toString(),
                query.value(4).toString(),
                query.value(5).toFloat(),
                query.value(6).toString(),
                query.value(7).toString(),
                query.value(8).toString(),
                QDate::fromString(query.value(9).toString(), "yyyy-MM-dd"),
                query.value(10).toString()
            ));
        } catch (const std::exception &e) {
            qDebug() << "Exception creating Etudiant object:" << e.what();
        }
    }
    
    return list;
}

QMap<QString, int> EtudiantService::getStatsBySpeciality() {
    QMap<QString, int> stats;
    
    QSqlQuery query("SELECT SPECIALITY, COUNT(*) FROM ETUDIANT GROUP BY SPECIALITY");
    
    while (query.next()) {
        stats.insert(query.value(0).toString(), query.value(1).toInt());
    }
    
    return stats;
}

QMap<QString, double> EtudiantService::getAverageNoteBySpeciality() {
    QMap<QString, double> stats;
    
    QSqlQuery query("SELECT SPECIALITY, AVG(NOTE) FROM ETUDIANT GROUP BY SPECIALITY");
    
    while (query.next()) {
        stats.insert(query.value(0).toString(), query.value(1).toDouble());
    }
    
    return stats;
}

int EtudiantService::getTotalCount()
{
    QSqlQuery query("SELECT COUNT(*) FROM ETUDIANT");
    
    if (query.next()) {
        return query.value(0).toInt();
    }
    
    return 0;
}

int EtudiantService::getCountByGender(const QString &gender)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM ETUDIANT WHERE GENDER = ?");
    query.addBindValue(gender);
    
    if (!query.exec()) {
        qDebug() << "Count by gender failed:" << query.lastError().text();
        qDebug() << "SQL query: " << query.lastQuery();
        return 0;
    }
    
    if (query.next()) {
        return query.value(0).toInt();
    }
    
    return 0;
}

double EtudiantService::getAverageNote()
{
    QSqlQuery query("SELECT AVG(NOTE) FROM ETUDIANT");
    
    if (query.next()) {
        return query.value(0).toDouble();
    }
    
    return 0.0;
}

bool EtudiantService::saveImage(const QString &sourcePath, QString &destinationPath) {
    // Generate a unique filename based on timestamp
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");
    QString filename = timestamp + "_" + QFileInfo(sourcePath).fileName();
    
    // Create images directory if it doesn't exist
    QDir dir("./images");
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    
    // Copy the image file
    destinationPath = "./images/" + filename;
    
    if (QFile::copy(sourcePath, destinationPath)) {
        return true;
    }
    
    qDebug() << "Failed to copy image from" << sourcePath << "to" << destinationPath;
    destinationPath.clear();
    return false;
}

bool EtudiantService::generatePDF(const QString &filename, const QList<Etudiant> &students) {
    if (students.isEmpty()) {
        qDebug() << "Cannot generate PDF: No students to export";
        return false;
    }

    if (filename.isEmpty()) {
        qDebug() << "Cannot generate PDF: No filename provided";
        return false;
    }

    try {
        QPdfWriter pdfWriter(filename);
        pdfWriter.setPageSize(QPageSize(QPageSize::A4));
        pdfWriter.setPageMargins(QMarginsF(30, 30, 30, 30));
        
        QPainter painter(&pdfWriter);
        painter.setPen(Qt::black);
        
        // Draw title
        QFont titleFont("Arial", 18, QFont::Bold);
        painter.setFont(titleFont);
        painter.drawText(QRect(0, 100, pdfWriter.width(), 50), 
                         Qt::AlignHCenter, "Liste des Étudiants");
        
        // Draw header
        QFont headerFont("Arial", 12, QFont::Bold);
        painter.setFont(headerFont);
        int yPos = 200;
        painter.drawText(QRect(100, yPos, 100, 30), Qt::AlignLeft, "CIN");
        painter.drawText(QRect(200, yPos, 100, 30), Qt::AlignLeft, "Nom");
        painter.drawText(QRect(300, yPos, 100, 30), Qt::AlignLeft, "Prénom");
        painter.drawText(QRect(400, yPos, 150, 30), Qt::AlignLeft, "Spécialité");
        painter.drawText(QRect(550, yPos, 100, 30), Qt::AlignLeft, "Note");
        
        // Draw students
        QFont contentFont("Arial", 10);
        painter.setFont(contentFont);
        yPos += 40;
        
        for (const Etudiant &student : students) {
            painter.drawText(QRect(100, yPos, 100, 30), Qt::AlignLeft, student.getCin());
            painter.drawText(QRect(200, yPos, 100, 30), Qt::AlignLeft, student.getName());
            painter.drawText(QRect(300, yPos, 100, 30), Qt::AlignLeft, student.getFamilyName());
            painter.drawText(QRect(400, yPos, 150, 30), Qt::AlignLeft, student.getSpeciality());
            painter.drawText(QRect(550, yPos, 100, 30), Qt::AlignLeft, 
                             QString::number(student.getNote(), 'f', 2));
            
            yPos += 40;
            
            // If we reach the bottom of the page, create a new page
            if (yPos > pdfWriter.height() - 100) {
                painter.end();
                painter.begin(&pdfWriter);
                painter.setPen(Qt::black);
                painter.setFont(contentFont);
                yPos = 100;
            }
        }
        
        painter.end();
        qDebug() << "PDF successfully generated at:" << filename;
        return true;
    } catch (const std::exception &e) {
        qDebug() << "Error generating PDF:" << e.what();
        return false;
    }
}

bool EtudiantService::generateStudentPDF(const QString &filename, const Etudiant &student) {
    if (filename.isEmpty()) {
        qDebug() << "Cannot generate student PDF: No filename provided";
        return false;
    }

    if (student.getId() <= 0) {
        qDebug() << "Cannot generate student PDF: Invalid student data";
        return false;
    }

    try {
        QPdfWriter pdfWriter(filename);
        pdfWriter.setPageSize(QPageSize(QPageSize::A4));
        pdfWriter.setPageMargins(QMarginsF(30, 30, 30, 30));
        
        QPainter painter(&pdfWriter);
        painter.setPen(Qt::black);
        
        // Draw title
        QFont titleFont("Arial", 18, QFont::Bold);
        painter.setFont(titleFont);
        painter.drawText(QRect(0, 100, pdfWriter.width(), 50), 
                         Qt::AlignHCenter, "Fiche Étudiant");
        
        // Draw student details
        QFont contentFont("Arial", 12);
        painter.setFont(contentFont);
        int yPos = 200;
        
        // Draw student photo if available
        if (!student.getPhotoPath().isEmpty()) {
            QImage photo(student.getPhotoPath());
            if (!photo.isNull()) {
                painter.drawImage(QRect(pdfWriter.width() - 230, yPos, 150, 150), photo);
            } else {
                qDebug() << "Could not load student photo from:" << student.getPhotoPath();
            }
        }
        
        painter.drawText(QRect(100, yPos, 200, 30), "CIN: " + student.getCin());
        yPos += 40;
        painter.drawText(QRect(100, yPos, 200, 30), "Nom: " + student.getName());
        yPos += 40;
        painter.drawText(QRect(100, yPos, 200, 30), "Prénom: " + student.getFamilyName());
        yPos += 40;
        painter.drawText(QRect(100, yPos, 200, 30), "Spécialité: " + student.getSpeciality());
        yPos += 40;
        painter.drawText(QRect(100, yPos, 200, 30), 
                         "Note: " + QString::number(student.getNote(), 'f', 2));
        yPos += 40;
        painter.drawText(QRect(100, yPos, 300, 30), "Téléphone: " + student.getPhoneNumber());
        yPos += 40;
        painter.drawText(QRect(100, yPos, 300, 30), "Email: " + student.getEmail());
        yPos += 40;
        painter.drawText(QRect(100, yPos, 300, 30), 
                         "Date de naissance: " + student.getBirthDate().toString("dd/MM/yyyy"));
        yPos += 40;
        painter.drawText(QRect(100, yPos, 200, 30), "Genre: " + student.getGender());
        
        painter.end();
        qDebug() << "Student PDF successfully generated at:" << filename;
        return true;
    } catch (const std::exception &e) {
        qDebug() << "Error generating student PDF:" << e.what();
        return false;
    }
}

// Helper method to get the next ID for a new student
int EtudiantService::getNextId() {
    int maxId = 0;
    QSqlQuery query("SELECT COALESCE(MAX(ID), 0) FROM ETUDIANT");
    
    if (query.next()) {
        maxId = query.value(0).toInt();
    }
    
    return maxId + 1;
}
