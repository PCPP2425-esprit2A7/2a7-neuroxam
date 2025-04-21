#include "etudiantservice.h"
#include "connection.h"
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
    if (!Connection::getDatabase().isValid()) {
        qDebug() << "Database connection not established in EtudiantService constructor";
    } else {
        // Create the table if it doesn't exist
        createTableIfNotExists();
    }
}

bool EtudiantService::createTableIfNotExists()
{
    QSqlQuery query(Connection::getDatabase());

    // Check if table exists (using Oracle-specific query)
    if (!query.exec("SELECT table_name FROM user_tables WHERE table_name = 'ETUDIANT'")) {
        qDebug() << "Failed to check if table exists:" << query.lastError().text();
        return false;
    }

    // If table doesn't exist, create it
    if (!query.next()) {
        // Create table with very basic Oracle syntax
        if (!query.exec("CREATE TABLE ETUDIANT (ID NUMBER, NAME VARCHAR2(100), FAMILY_NAME VARCHAR2(100), "
                        "CIN VARCHAR2(20), SPECIALITY VARCHAR2(100), NOTE NUMBER(5,2), GENDER VARCHAR2(20), "
                        "PHONE VARCHAR2(20), EMAIL VARCHAR2(100), BIRTH_DATE DATE, PHOTO_PATH VARCHAR2(255), "
                        "CONSTRAINT PK_ETUDIANT PRIMARY KEY (ID))")) {
            qDebug() << "Failed to create table:" << query.lastError().text();
            return false;
        }

        // Create sequence for auto-increment ID with minimal options
        if (!query.exec("CREATE SEQUENCE ETUDIANT_SEQ")) {
            qDebug() << "Failed to create sequence:" << query.lastError().text();
            return false;
        }

        // Create simplified trigger for auto-increment ID
        if (!query.exec("CREATE TRIGGER ETUDIANT_TRG BEFORE INSERT ON ETUDIANT FOR EACH ROW "
                        "BEGIN SELECT ETUDIANT_SEQ.NEXTVAL INTO :NEW.ID FROM DUAL; END;")) {
            qDebug() << "Failed to create trigger:" << query.lastError().text();
            return false;
        }

        qDebug() << "Database objects created successfully";
    }

    return true;
}

// Helper function to format dates for Oracle
QString formatDateForOracle(const QDate &date) {
    if (!date.isValid()) {
        return "NULL";
    }
    return date.toString("yyyy-MM-dd");
}

bool EtudiantService::add(const Etudiant &etudiant) {
    QString birthDateStr = formatDateForOracle(etudiant.getBirthDate());

    // Build a direct SQL query with TO_DATE for dates
    QString sql = QString(
                      "INSERT INTO ETUDIANT (NAME, FAMILY_NAME, CIN, SPECIALITY, NOTE, GENDER, PHONE, EMAIL, BIRTH_DATE, PHOTO_PATH) "
                      "VALUES (:name, :family, :cin, :spec, :note, :gender, :phone, :email, TO_DATE('%1', 'YYYY-MM-DD'), :photo)")
                      .arg(birthDateStr);

    QSqlQuery query(Connection::getDatabase());
    query.prepare(sql);

    query.bindValue(":name", etudiant.getName());
    query.bindValue(":family", etudiant.getFamilyName());
    query.bindValue(":cin", etudiant.getCin());
    query.bindValue(":spec", etudiant.getSpeciality());
    query.bindValue(":note", etudiant.getNote());
    query.bindValue(":gender", etudiant.getGender());
    query.bindValue(":phone", etudiant.getPhoneNumber());
    query.bindValue(":email", etudiant.getEmail());
    query.bindValue(":photo", etudiant.getPhotoPath());

    qDebug() << "Executing SQL: " << sql;

    if (!query.exec()) {
        qDebug() << "Add failed:" << query.lastError().text();
        return false;
    }

    qDebug() << "Student successfully added to database";
    return true;
}

bool EtudiantService::add(const QString &name, const QString &familyName, const QString &cin,
                          const QString &speciality, double note, const QString &gender,
                          const QString &phone, const QString &email, const QString &birthDate,
                          const QString &photoPath)
{
    // Build a direct SQL query with TO_DATE for dates
    QString sql = QString(
                      "INSERT INTO ETUDIANT (NAME, FAMILY_NAME, CIN, SPECIALITY, NOTE, GENDER, PHONE, EMAIL, BIRTH_DATE, PHOTO_PATH) "
                      "VALUES (:name, :family, :cin, :spec, :note, :gender, :phone, :email, TO_DATE('%1', 'YYYY-MM-DD'), :photo)")
                      .arg(birthDate);

    QSqlQuery query(Connection::getDatabase());
    query.prepare(sql);

    query.bindValue(":name", name);
    query.bindValue(":family", familyName);
    query.bindValue(":cin", cin);
    query.bindValue(":spec", speciality);
    query.bindValue(":note", note);
    query.bindValue(":gender", gender);
    query.bindValue(":phone", phone);
    query.bindValue(":email", email);
    query.bindValue(":photo", photoPath);

    qDebug() << "Executing SQL: " << sql;

    if (!query.exec()) {
        qDebug() << "Error adding student: " << query.lastError().text();
        qDebug() << "SQL query: " << query.lastQuery();
        return false;
    }

    qDebug() << "Student successfully added to database";
    return true;
}

bool EtudiantService::update(const Etudiant &etudiant) {
    QString birthDateStr = formatDateForOracle(etudiant.getBirthDate());

    // Build a direct SQL query with TO_DATE for dates
    QString sql = QString(
                      "UPDATE ETUDIANT SET "
                      "NAME = :name, "
                      "FAMILY_NAME = :family, "
                      "CIN = :cin, "
                      "SPECIALITY = :spec, "
                      "NOTE = :note, "
                      "GENDER = :gender, "
                      "PHONE = :phone, "
                      "EMAIL = :email, "
                      "BIRTH_DATE = TO_DATE('%1', 'YYYY-MM-DD'), "
                      "PHOTO_PATH = :photo "
                      "WHERE ID = :id")
                      .arg(birthDateStr);

    QSqlQuery query(Connection::getDatabase());
    query.prepare(sql);

    query.bindValue(":name", etudiant.getName());
    query.bindValue(":family", etudiant.getFamilyName());
    query.bindValue(":cin", etudiant.getCin());
    query.bindValue(":spec", etudiant.getSpeciality());
    query.bindValue(":note", etudiant.getNote());
    query.bindValue(":gender", etudiant.getGender());
    query.bindValue(":phone", etudiant.getPhoneNumber());
    query.bindValue(":email", etudiant.getEmail());
    query.bindValue(":photo", etudiant.getPhotoPath());
    query.bindValue(":id", etudiant.getId());

    qDebug() << "Executing SQL update: " << sql;

    if (!query.exec()) {
        qDebug() << "Update failed:" << query.lastError().text();
        qDebug() << "SQL query: " << query.lastQuery();
        return false;
    }

    qDebug() << "Student successfully updated in database";
    return query.numRowsAffected() > 0;
}

bool EtudiantService::update(int id, const QString &name, const QString &familyName, const QString &cin,
                             const QString &speciality, double note, const QString &gender,
                             const QString &phone, const QString &email, const QString &birthDate,
                             const QString &photoPath)
{
    // Build a direct SQL query with TO_DATE for dates
    QString sql = QString(
                      "UPDATE ETUDIANT SET "
                      "NAME = :name, "
                      "FAMILY_NAME = :family, "
                      "CIN = :cin, "
                      "SPECIALITY = :spec, "
                      "NOTE = :note, "
                      "GENDER = :gender, "
                      "PHONE = :phone, "
                      "EMAIL = :email, "
                      "BIRTH_DATE = TO_DATE('%1', 'YYYY-MM-DD'), "
                      "PHOTO_PATH = :photo "
                      "WHERE ID = :id")
                      .arg(birthDate);

    QSqlQuery query(Connection::getDatabase());
    query.prepare(sql);

    query.bindValue(":name", name);
    query.bindValue(":family", familyName);
    query.bindValue(":cin", cin);
    query.bindValue(":spec", speciality);
    query.bindValue(":note", note);
    query.bindValue(":gender", gender);
    query.bindValue(":phone", phone);
    query.bindValue(":email", email);
    query.bindValue(":photo", photoPath);
    query.bindValue(":id", id);

    qDebug() << "Executing SQL update: " << sql;

    if (!query.exec()) {
        qDebug() << "Error updating student: " << query.lastError().text();
        qDebug() << "SQL query: " << query.lastQuery();
        return false;
    }

    qDebug() << "Student successfully updated in database";
    return true;
}

bool EtudiantService::remove(int id) {
    QSqlQuery query(Connection::getDatabase());
    query.prepare("DELETE FROM ETUDIANT WHERE ID = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Delete failed:" << query.lastError().text();
        qDebug() << "SQL query: " << query.lastQuery();
        return false;
    }
    return query.numRowsAffected() > 0;
}

Etudiant EtudiantService::getById(int id) {
    QSqlQuery query(Connection::getDatabase());

    // Use proper Oracle date format
    query.prepare("SELECT ID, NAME, FAMILY_NAME, CIN, SPECIALITY, NOTE, PHOTO_PATH, "
                  "PHONE, EMAIL, TO_CHAR(BIRTH_DATE, 'YYYY-MM-DD') as BIRTH_DATE, GENDER "
                  "FROM ETUDIANT WHERE ID = :id");

    query.bindValue(":id", id);

    qDebug() << "Executing getById for ID: " << id;

    if (!query.exec()) {
        qDebug() << "Get by ID failed:" << query.lastError().text();
        qDebug() << "SQL query: " << query.lastQuery();
        return Etudiant();
    }

    if (query.next()) {
        Etudiant student(
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
        qDebug() << "Student found: " << student.getName() << " " << student.getFamilyName();
        return student;
    }

    qDebug() << "No student found with ID: " << id;
    return Etudiant();
}

QList<Etudiant> EtudiantService::getAll() {
    QList<Etudiant> list;

    QSqlQuery query(Connection::getDatabase());

    qDebug() << "Executing getAll";

    if (!query.exec("SELECT ID, NAME, FAMILY_NAME, CIN, SPECIALITY, NOTE, PHOTO_PATH, "
                    "PHONE, EMAIL, TO_CHAR(BIRTH_DATE, 'YYYY-MM-DD') as BIRTH_DATE, GENDER "
                    "FROM ETUDIANT")) {
        qDebug() << "Get all failed:" << query.lastError().text();
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

    qDebug() << "Found" << list.size() << "students";
    return list;
}

QList<Etudiant> EtudiantService::getSortedBy(const QString &column) {
    QList<Etudiant> list;

    if (column.isEmpty()) return getAll();

    // Use proper column names for the SQL query
    QString columnName = column.toUpper();

    QString queryStr = QString("SELECT ID, NAME, FAMILY_NAME, CIN, SPECIALITY, NOTE, PHOTO_PATH, "
                               "PHONE, EMAIL, TO_CHAR(BIRTH_DATE, 'YYYY-MM-DD') as BIRTH_DATE, GENDER "
                               "FROM ETUDIANT ORDER BY %1").arg(columnName);

    QSqlQuery query(Connection::getDatabase());

    qDebug() << "Executing sort by: " << columnName;
    qDebug() << "SQL: " << queryStr;

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

    qDebug() << "Found" << list.size() << "students after sorting";
    return list;
}

QList<Etudiant> EtudiantService::searchByCriteria(const QString &criteria, const QString &value) {
    QList<Etudiant> list;

    if (criteria.isEmpty() || value.isEmpty()) return getAll();

    // Use proper column names for the SQL query
    QString columnName = criteria.toUpper();

    QString queryStr = QString("SELECT ID, NAME, FAMILY_NAME, CIN, SPECIALITY, NOTE, PHOTO_PATH, "
                               "PHONE, EMAIL, TO_CHAR(BIRTH_DATE, 'YYYY-MM-DD') as BIRTH_DATE, GENDER "
                               "FROM ETUDIANT WHERE UPPER(%1) LIKE UPPER(:value)").arg(columnName);

    QSqlQuery query(Connection::getDatabase());
    query.prepare(queryStr);
    query.bindValue(":value", "%" + value + "%");

    qDebug() << "Executing search by criteria: " << columnName << " with value: " << value;
    qDebug() << "SQL: " << queryStr;

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

    qDebug() << "Found" << list.size() << "students matching criteria";
    return list;
}

QMap<QString, int> EtudiantService::getStatsBySpeciality() {
    QMap<QString, int> stats;

    QSqlQuery query(Connection::getDatabase());
    query.exec("SELECT SPECIALITY, COUNT(*) FROM ETUDIANT GROUP BY SPECIALITY");

    while (query.next()) {
        stats.insert(query.value(0).toString(), query.value(1).toInt());
    }

    return stats;
}

QMap<QString, double> EtudiantService::getAverageNoteBySpeciality() {
    QMap<QString, double> stats;

    QSqlQuery query(Connection::getDatabase());
    query.exec("SELECT SPECIALITY, AVG(NOTE) FROM ETUDIANT GROUP BY SPECIALITY");

    while (query.next()) {
        stats.insert(query.value(0).toString(), query.value(1).toDouble());
    }

    return stats;
}

int EtudiantService::getTotalCount()
{
    QSqlQuery query(Connection::getDatabase());
    query.exec("SELECT COUNT(*) FROM ETUDIANT");

    if (query.next()) {
        return query.value(0).toInt();
    }

    return 0;
}

int EtudiantService::getCountByGender(const QString &gender)
{
    QSqlQuery query(Connection::getDatabase());
    query.prepare("SELECT COUNT(*) FROM ETUDIANT WHERE GENDER = :gender");
    query.bindValue(":gender", gender);

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
    QSqlQuery query(Connection::getDatabase());
    query.exec("SELECT AVG(NOTE) FROM ETUDIANT");

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
// This method is no longer needed since we're using Oracle sequence via the trigger
// Keeping it for backward compatibility with other code that might call it
int EtudiantService::getNextId() {
    int maxId = 0;
    QSqlQuery query(Connection::getDatabase());
    query.exec("SELECT COALESCE(MAX(ID), 0) FROM ETUDIANT");

    if (query.next()) {
        maxId = query.value(0).toInt();
    }

    return maxId + 1;
}
