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
    if (!Connection::get_database().isValid()) {
        qDebug() << "Database connection not established in EtudiantService constructor";
    } else {
        // Create the table if it doesn't exist
        createTableIfNotExists();
    }
}

bool EtudiantService::createTableIfNotExists()
{
    QSqlQuery query(Connection::get_database());

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

    QSqlQuery query(Connection::get_database());
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

    QSqlQuery query(Connection::get_database());
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

    QSqlQuery query(Connection::get_database());
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

    QSqlQuery query(Connection::get_database());
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
    QSqlQuery query(Connection::get_database());
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
    QSqlQuery query(Connection::get_database());

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

    QSqlQuery query(Connection::get_database());

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

    QSqlQuery query(Connection::get_database());

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

    QSqlQuery query(Connection::get_database());
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

    QSqlQuery query(Connection::get_database());
    query.exec("SELECT SPECIALITY, COUNT(*) FROM ETUDIANT GROUP BY SPECIALITY");

    while (query.next()) {
        stats.insert(query.value(0).toString(), query.value(1).toInt());
    }

    return stats;
}

QMap<QString, double> EtudiantService::getAverageNoteBySpeciality() {
    QMap<QString, double> stats;

    QSqlQuery query(Connection::get_database());
    query.exec("SELECT SPECIALITY, AVG(NOTE) FROM ETUDIANT GROUP BY SPECIALITY");

    while (query.next()) {
        stats.insert(query.value(0).toString(), query.value(1).toDouble());
    }

    return stats;
}

int EtudiantService::getTotalCount()
{
    QSqlQuery query(Connection::get_database());
    query.exec("SELECT COUNT(*) FROM ETUDIANT");

    if (query.next()) {
        return query.value(0).toInt();
    }

    return 0;
}

int EtudiantService::getCountByGender(const QString &gender)
{
    QSqlQuery query(Connection::get_database());
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
    QSqlQuery query(Connection::get_database());
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
        // Set up the PDF document
        QPdfWriter pdfWriter(filename);
        pdfWriter.setPageSize(QPageSize(QPageSize::A4));
        pdfWriter.setPageMargins(QMarginsF(30, 30, 30, 30));
        pdfWriter.setResolution(300); // Higher resolution for better quality

        QPainter painter(&pdfWriter);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setRenderHint(QPainter::TextAntialiasing, true);
        painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

        // Define colors for styling
        QColor headerBgColor(52, 152, 219);  // Blue
        QColor headerTextColor(255, 255, 255);  // White
        QColor alternateBgColor(245, 245, 245); // Light gray for alternating rows
        QColor borderColor(52, 73, 94);  // Dark blue
        QColor titleColor(41, 128, 185); // Darker blue for title
        QColor textColor(0, 0, 0);       // Pure black for text

        // Page dimensions
        int pageWidth = pdfWriter.width();
        int pageHeight = pdfWriter.height();
        int margin = 5;
        int contentWidth = pageWidth - 2 * margin + 300;

        // Add a header with date
        QFont dateFont("Arial", 9);
        painter.setFont(dateFont);
        painter.setPen(textColor);
        painter.drawText(QRect(margin, margin, contentWidth, 20),
                         Qt::AlignRight,
                         "Généré le " + QDateTime::currentDateTime().toString("dd/MM/yyyy à hh:mm:ss"));

        // Create a solid background for the title
        painter.setBrush(Qt::white);
        painter.setPen(Qt::NoPen);
        painter.drawRect(margin, margin + 30, contentWidth, 60);

        // Draw title with better positioning and spacing
        QFont titleFont("Arial", 22, QFont::Bold);
        painter.setFont(titleFont);
        painter.setPen(titleColor);

        // Explicitly calculate text width to ensure proper centering
        QFontMetrics fm(titleFont);
        QString titleText = "Liste des Étudiants";
        int textWidth = fm.horizontalAdvance(titleText);
        int textX = margin + (contentWidth - textWidth) / 2;
        int textY = margin + 60;

        painter.drawText(textX, textY, titleText);

        // Draw decorative line under title with more space
        painter.setPen(QPen(titleColor, 2));
        painter.drawLine(margin + 100, textY + 15, pageWidth - margin - 100, textY + 15);

        // Reset pen
        painter.setPen(Qt::black);

        // Draw table with headers - increase starting position to add more space after title
        int yPos = margin + 120;
        int rowHeight = 50;

        // Column widths
        int idWidth = 250/3;
        int cinWidth = 600/3;
        int nameWidth = 700/3;
        int familyNameWidth = 700/3;
        int specialityWidth = 750/3;
        int noteWidth = 350/3;
        int genderWidth = 450/3;
        int totalWidth = idWidth + cinWidth + nameWidth + familyNameWidth + specialityWidth + noteWidth + genderWidth + 100;

        // Calculate left position to center the table
        int xPos = margin + (contentWidth - totalWidth) / 2 - 20;
        int initialXPos = xPos;


        // Draw table header background
        painter.setBrush(headerBgColor);
        painter.setPen(Qt::NoPen);
        painter.drawRect(xPos, yPos, totalWidth, rowHeight);

        // Draw header text
        painter.setPen(headerTextColor);
        QFont headerFont("Arial", 9, QFont::Bold);
        painter.setFont(headerFont);

        xPos = initialXPos;
        painter.drawText(QRect(xPos, yPos, idWidth, rowHeight), Qt::AlignCenter, "ID");
        xPos += idWidth;

        painter.drawText(QRect(xPos, yPos, cinWidth, rowHeight), Qt::AlignCenter, "CIN");
        xPos += cinWidth;

        painter.drawText(QRect(xPos, yPos, nameWidth, rowHeight), Qt::AlignCenter, "Nom");
        xPos += nameWidth;

        painter.drawText(QRect(xPos, yPos, familyNameWidth, rowHeight), Qt::AlignCenter, "Prénom");
        xPos += familyNameWidth;

        painter.drawText(QRect(xPos, yPos, specialityWidth, rowHeight), Qt::AlignCenter, "Spécialité");
        xPos += specialityWidth;

        painter.drawText(QRect(xPos, yPos, noteWidth, rowHeight), Qt::AlignCenter, "Note");
        xPos += noteWidth;

        painter.drawText(QRect(xPos, yPos, genderWidth, rowHeight), Qt::AlignCenter, "Genre");

        // Move to next row
        yPos += rowHeight;

        // Draw student rows
        QFont contentFont("Arial", 8);
        painter.setFont(contentFont);
        painter.setPen(textColor);

        bool alternateRow = false;
        int studentCount = 0;

        // Custom page number that starts at 101
        int customPageNumber = 1;

        for (const Etudiant &student : students) {
            // If we're about to go off the page, start a new page
            if (yPos + rowHeight > pageHeight - margin) {
                painter.drawText(QRect(margin, pageHeight - margin - 20, contentWidth, 20),
                                 Qt::AlignCenter,
                                 QString("Page %1").arg(customPageNumber));

                pdfWriter.newPage();
                customPageNumber++;

                // Reset position
                yPos = margin + 50;

                // Add page header
                painter.setFont(dateFont);
                painter.setPen(textColor);
                painter.drawText(QRect(margin, margin, contentWidth, 20),
                                 Qt::AlignRight,
                                 "Généré le " + QDateTime::currentDateTime().toString("dd/MM/yyyy à hh:mm:ss"));

                // Draw table header again on new page
                painter.setBrush(headerBgColor);
                painter.setPen(Qt::NoPen);
                painter.drawRect(initialXPos, yPos, totalWidth, rowHeight);

                // Draw header text
                painter.setPen(headerTextColor);
                painter.setFont(headerFont);

                xPos = initialXPos;
                painter.drawText(QRect(xPos, yPos, idWidth, rowHeight), Qt::AlignCenter, "ID");
                xPos += idWidth;

                painter.drawText(QRect(xPos, yPos, cinWidth, rowHeight), Qt::AlignCenter, "CIN");
                xPos += cinWidth;

                painter.drawText(QRect(xPos, yPos, nameWidth, rowHeight), Qt::AlignCenter, "Nom");
                xPos += nameWidth;

                painter.drawText(QRect(xPos, yPos, familyNameWidth, rowHeight), Qt::AlignCenter, "Prénom");
                xPos += familyNameWidth;

                painter.drawText(QRect(xPos, yPos, specialityWidth, rowHeight), Qt::AlignCenter, "Spécialité");
                xPos += specialityWidth;

                painter.drawText(QRect(xPos, yPos, noteWidth, rowHeight), Qt::AlignCenter, "Note");
                xPos += noteWidth;

                painter.drawText(QRect(xPos, yPos, genderWidth, rowHeight), Qt::AlignCenter, "Genre");

                // Move to next row
                yPos += rowHeight;

                // Reset content settings
                painter.setFont(contentFont);
                painter.setPen(textColor);

                // Reset alternate row flag
                alternateRow = false;
            }

            // Draw row background (alternating colors)
            if (alternateRow) {
                painter.setBrush(alternateBgColor);
                painter.setPen(Qt::NoPen);
                painter.drawRect(initialXPos, yPos, totalWidth, rowHeight);
            }

            // Draw cell content
            painter.setPen(textColor);

            xPos = initialXPos;
            painter.drawText(QRect(xPos, yPos, idWidth, rowHeight),
                             Qt::AlignCenter,
                             QString::number(student.getId()));
            xPos += idWidth;

            painter.drawText(QRect(xPos, yPos, cinWidth, rowHeight),
                             Qt::AlignCenter,
                             student.getCin());
            xPos += cinWidth;

            painter.drawText(QRect(xPos, yPos, nameWidth, rowHeight),
                             Qt::AlignCenter,
                             student.getName());
            xPos += nameWidth;

            painter.drawText(QRect(xPos, yPos, familyNameWidth, rowHeight),
                             Qt::AlignCenter,
                             student.getFamilyName());
            xPos += familyNameWidth;

            painter.drawText(QRect(xPos, yPos, specialityWidth, rowHeight),
                             Qt::AlignCenter,
                             student.getSpeciality());
            xPos += specialityWidth;

            painter.drawText(QRect(xPos, yPos, noteWidth, rowHeight),
                             Qt::AlignCenter,
                             QString::number(student.getNote(), 'f', 2));
            xPos += noteWidth;

            painter.drawText(QRect(xPos, yPos, genderWidth, rowHeight),
                             Qt::AlignCenter,
                             student.getGender());

            // Move to next row
            yPos += rowHeight;
            alternateRow = !alternateRow;
            studentCount++;
        }

        // Adjust the table border to the new y-position of table beginning (120 instead of 100)
        // Draw table border
        painter.setPen(QPen(borderColor, 1));
        painter.setBrush(Qt::NoBrush);
        painter.drawRect(initialXPos, margin + 120, totalWidth, studentCount * rowHeight);

        // Draw grid lines - make them lighter
        painter.setPen(QPen(borderColor, 0.3, Qt::SolidLine));

        // Vertical lines
        xPos = initialXPos;
        for (int i = 1; i < 7; i++) {
            if (i == 1) xPos += idWidth;
            else if (i == 2) xPos += cinWidth;
            else if (i == 3) xPos += nameWidth;
            else if (i == 4) xPos += familyNameWidth;
            else if (i == 5) xPos += specialityWidth;
            else if (i == 6) xPos += noteWidth;

            painter.drawLine(xPos, margin + 120, xPos, margin + 120 + (studentCount + 1) * rowHeight - 10);
        }

        // Horizontal lines
        for (int i = 1; i <= studentCount + 1; i++) {
            painter.drawLine(initialXPos, margin + 120 + i * rowHeight,
                             initialXPos + totalWidth, margin + 120 + i * rowHeight);
        }

        // Draw summary
        yPos += 20;
        painter.setPen(textColor);
        QFont summaryFont("Arial", 11, QFont::Bold);
        painter.setFont(summaryFont);
        painter.drawText(QRect(initialXPos, yPos, totalWidth, 60),
                         Qt::AlignLeft,
                         QString("Total des étudiants: %1").arg(studentCount));

        // Draw page number
        painter.drawText(QRect(margin, pageHeight - margin - 60, contentWidth, 20),
                         Qt::AlignCenter,
                         QString("Page %1").arg(customPageNumber));

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
        // Set up the PDF document
        QPdfWriter pdfWriter(filename);
        pdfWriter.setPageSize(QPageSize(QPageSize::A4));
        pdfWriter.setPageMargins(QMarginsF(30, 30, 30, 30));
        pdfWriter.setResolution(300); // Higher resolution for better quality

        QPainter painter(&pdfWriter);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setRenderHint(QPainter::TextAntialiasing, true);
        painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

        // Define colors for styling
        QColor headerColor(52, 152, 219);  // Blue
        QColor textColor(0, 0, 0);         // Pure black for all text
        QColor accentColor(46, 204, 113);  // Green
        QColor lightBgColor(236, 240, 241); // Light gray for background

        // Page dimensions
        int pageWidth = pdfWriter.width();
        int pageHeight = pdfWriter.height();
        int margin = 50;
        int contentWidth = pageWidth - 2 * margin;

        // Draw background pattern for header
        painter.setBrush(headerColor);
        painter.setPen(Qt::NoPen);
        painter.drawRect(0, 0, pageWidth, 150);

        // Draw document title
        QFont titleFont("Arial", 24, QFont::Bold);
        painter.setFont(titleFont);
        painter.setPen(Qt::white);  // White text for header
        painter.drawText(QRect(margin, 50, contentWidth, 50), Qt::AlignCenter, "Fiche Étudiant");

        // Draw decorative line
        painter.setPen(QPen(Qt::white, 2));
        painter.drawLine(margin + 150, 100, pageWidth - margin - 150, 100);

        // Draw a round background for student details
        int detailsTop = 180;
        int detailsWidth = contentWidth;
        int detailsHeight = 500;

        painter.setBrush(lightBgColor);
        painter.setPen(Qt::NoPen);
        painter.drawRoundedRect(margin, detailsTop, detailsWidth, detailsHeight, 15, 15);

        // Draw student photo if available - ENLARGED SIZE
        int photoSize = 200;  // Increased from 150 to 200
        int photoX = pageWidth - margin - photoSize - 30;
        int photoY = detailsTop + 30;

        if (!student.getPhotoPath().isEmpty()) {
            QImage photo(student.getPhotoPath());
            if (!photo.isNull()) {
                // Draw decorative frame around photo
                painter.setBrush(accentColor);
                painter.setPen(QPen(Qt::white, 2));
                painter.drawRoundedRect(photoX - 5, photoY - 5, photoSize + 10, photoSize + 10, 10, 10);

                // Draw the photo
                painter.drawImage(QRect(photoX, photoY, photoSize, photoSize), photo);
            } else {
                qDebug() << "Could not load student photo from:" << student.getPhotoPath();
                // Draw placeholder
                painter.setBrush(Qt::lightGray);
                painter.setPen(Qt::NoPen);
                painter.drawRoundedRect(photoX, photoY, photoSize, photoSize, 10, 10);

                QFont placeholderFont("Arial", 14);  // Increased size
                painter.setFont(placeholderFont);
                painter.setPen(textColor);  // Use black text
                painter.drawText(QRect(photoX, photoY, photoSize, photoSize),
                                 Qt::AlignCenter, "No Photo\nAvailable");
            }
        } else {
            // Draw placeholder
            painter.setBrush(Qt::lightGray);
            painter.setPen(Qt::NoPen);
            painter.drawRoundedRect(photoX, photoY, photoSize, photoSize, 10, 10);

            QFont placeholderFont("Arial", 14);  // Increased size
            painter.setFont(placeholderFont);
            painter.setPen(textColor);  // Use black text
            painter.drawText(QRect(photoX, photoY, photoSize, photoSize),
                             Qt::AlignCenter, "No Photo\nAvailable");
        }

        // Draw student details with styled labels
        QFont labelFont("Arial", 12, QFont::Bold);  // Increased size
        QFont valueFont("Arial", 12);  // Increased size
        int yPos = detailsTop + 40;
        int xPos = margin + 30;
        int labelWidth = 150;
        int valueWidth = contentWidth - photoSize - 60 - labelWidth;
        int rowHeight = 40;

        // Helper function to draw field
        auto drawField = [&](const QString &label, const QString &value) {
            // Label
            painter.setFont(labelFont);
            painter.setPen(headerColor);  // Keep blue for labels
            painter.drawText(QRect(xPos, yPos, labelWidth, rowHeight), Qt::AlignRight | Qt::AlignVCenter, label);

            // Value with a light background
            painter.setBrush(Qt::white);
            painter.setPen(Qt::NoPen);
            painter.drawRoundedRect(xPos + labelWidth, yPos + 5, valueWidth, rowHeight - 10, 5, 5);

            painter.setFont(valueFont);
            painter.setPen(textColor);  // Black text for values
            painter.drawText(QRect(xPos + labelWidth + 10, yPos, valueWidth - 20, rowHeight),
                             Qt::AlignVCenter, value);

            yPos += rowHeight;
        };

        drawField("ID:", QString::number(student.getId()));
        drawField("CIN:", student.getCin());
        drawField("Nom:", student.getName());
        drawField("Prénom:", student.getFamilyName());
        drawField("Spécialité:", student.getSpeciality());
        drawField("Note:", QString::number(student.getNote(), 'f', 2));
        drawField("Téléphone:", student.getPhoneNumber());
        drawField("Email:", student.getEmail());
        drawField("Date de naissance:", student.getBirthDate().toString("dd/MM/yyyy"));
        drawField("Genre:", student.getGender());

        // Draw a decorative footer
        painter.setBrush(accentColor);
        painter.setPen(Qt::NoPen);
        painter.drawRect(0, pageHeight - 50, pageWidth, 50);

        // Add footer text with page number starting at 101
        QFont footerFont("Arial", 9);
        painter.setFont(footerFont);
        painter.setPen(Qt::white);  // White text on green background
        painter.drawText(QRect(margin, pageHeight - 45, contentWidth, 40),
                         Qt::AlignRight | Qt::AlignVCenter,
                         "Fiche générée le " + QDateTime::currentDateTime().toString("dd/MM/yyyy à hh:mm:ss") +
                             " | Page 1 - " + student.getName() + " " + student.getFamilyName());

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
    QSqlQuery query(Connection::get_database());
    query.exec("SELECT COALESCE(MAX(ID), 0) FROM ETUDIANT");

    if (query.next()) {
        maxId = query.value(0).toInt();
    }

    return maxId + 1;
}
