#include "materielManager.h"
#include <QPdfWriter>
#include <QPainter>
#include <QDate>
#include <QDateTime>

bool MaterielManager::addMateriel(const Materiel& materiel)
{
    QSqlQuery query;
    query.prepare("INSERT INTO materiels (type, etat, localisation, disponibilite) "
                  "VALUES (:type, :etat, :localisation, :disponibilite)");

    query.bindValue(":type", materiel.getType());
    query.bindValue(":etat", materiel.getEtat());
    query.bindValue(":localisation", materiel.getLocalisation());
    query.bindValue(":disponibilite", materiel.getDisponibilite());

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'ajout du materiel: " << query.lastError().text();
        return false;
    }
    return true;
}

bool MaterielManager::getMateriel(int id, Materiel& materiel)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM materiels WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec() || !query.next()) {
        qDebug() << "Erreur lors de la lecture du materiel: " << query.lastError().text();
        return false;
    }

    materiel = Materiel(
        query.value("type").toString(),
        query.value("etat").toString(),
        query.value("localisation").toString(),
        query.value("disponibilite").toString());

    materiel.setId(query.value("id").toInt());

    return true;
}

std::vector<Materiel> MaterielManager::getAllMateriels()
{
    std::vector<Materiel> materiels;
    QSqlQuery query("SELECT * FROM materiels");

    while (query.next()) {
        Materiel materiel(
            query.value("type").toString(),
            query.value("etat").toString(),
            query.value("localisation").toString(),
            query.value("disponibilite").toString());

        materiel.setId(query.value("id").toInt());

        materiels.push_back(materiel);
    }

    return materiels;
}

bool MaterielManager::updateMateriel(const Materiel& materiel)
{
    QSqlQuery query;
    query.prepare("UPDATE materiels SET type = :type, etat = :etat, localisation = :localisation, "
                  "disponibilite = :disponibilite WHERE id = :id");

    query.bindValue(":id", materiel.getId());
    query.bindValue(":type", materiel.getType());
    query.bindValue(":etat", materiel.getEtat());
    query.bindValue(":localisation", materiel.getLocalisation());
    query.bindValue(":disponibilite", materiel.getDisponibilite());

    if (!query.exec()) {
        qDebug() << "Erreur lors de la mise a jour du materiel: " << query.lastError().text();
        return false;
    }
    return true;
}

bool MaterielManager::deleteMateriel(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM materiels WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la suppresion du materiel: " << query.lastError().text();
        return false;
    }
    return true;
}





bool MaterielManager::generatePdf(const QString& filePath)
{
    // Set up the PDF writer with consistent margins
    QPdfWriter writer(filePath);
    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setResolution(300);
    // Set margins to 50 points on all sides
    const int pageMargin = 50;
    writer.setPageMargins(QMarginsF(pageMargin, pageMargin, pageMargin, pageMargin), QPageLayout::Point);

    QPainter painter(&writer);
    painter.setRenderHint(QPainter::Antialiasing);

    // Get page dimensions (drawing area within margins)
    QRect pageRect = painter.viewport();
    int pageWidth = pageRect.width();
    int pageHeight = pageRect.height();

    // Set up starting y position and title area
    int y = pageMargin;
    int titleHeight = 50;

    // Draw Title
    painter.setFont(QFont("Arial", 18, QFont::Bold));
    QRect titleRect(pageMargin, y, pageWidth - 2 * pageMargin, titleHeight);
    painter.drawText(titleRect, Qt::AlignCenter, "Liste des Materiels");
    y += titleHeight + 20;  // leave some space after the title

    // Define table header dimensions
    int rowHeight = 40;
    int tableWidth = pageWidth - 2 * pageMargin;
    int col1Width = tableWidth * 0.1;  // ID (10%)
    int col2Width = tableWidth * 0.2;  // Type (20%)
    int col3Width = tableWidth * 0.2;  // Etat (20%)
    int col4Width = tableWidth * 0.3;  // Localisation (30%)
    int col5Width = tableWidth * 0.2;  // Disponibilite (20%)

    // Draw Table Header
    painter.setFont(QFont("Arial", 12, QFont::Bold));
    QRect headerRect(pageMargin, y, tableWidth, rowHeight);
    painter.fillRect(headerRect, QColor(230, 230, 230));
    painter.drawRect(headerRect);
    int x = pageMargin;
    painter.drawText(QRect(x, y, col1Width, rowHeight), Qt::AlignCenter, "ID");
    painter.drawLine(x + col1Width, y, x + col1Width, y + rowHeight);
    x += col1Width;

    painter.drawText(QRect(x, y, col2Width, rowHeight), Qt::AlignCenter, "Type");
    painter.drawLine(x + col2Width, y, x + col2Width, y + rowHeight);
    x += col2Width;

    painter.drawText(QRect(x, y, col3Width, rowHeight), Qt::AlignCenter, "Etat");
    painter.drawLine(x + col3Width, y, x + col3Width, y + rowHeight);
    x += col3Width;

    painter.drawText(QRect(x, y, col4Width, rowHeight), Qt::AlignCenter, "Localisation");
    painter.drawLine(x + col4Width, y, x + col4Width, y + rowHeight);
    x += col4Width;

    painter.drawText(QRect(x, y, col5Width, rowHeight), Qt::AlignCenter, "Disponibilite");
    y += rowHeight;

    // Prepare for drawing data rows
    QSqlQuery query;
    if (!query.exec("SELECT * FROM materiels")) {
        qDebug() << "Error fetching data: " << query.lastError().text();
        return false;
    }

    painter.setFont(QFont("Arial", 11));
    int rowCount = 0;
    int pageCount = 1;
    int footerHeight = 30; // space reserved for the footer text
    // Calculate maximum rows per page (taking bottom margin into account)
    int maxRowsPerPage = (pageHeight - y - pageMargin) / rowHeight;

    // Loop through each row in the query
    while (query.next()) {
        // Check if we need a new page
        if (rowCount >= maxRowsPerPage) {
            // Draw Footer on current page
            painter.setFont(QFont("Arial", 10));
            QRect footerRect(pageMargin, pageHeight - pageMargin, tableWidth, footerHeight);
            painter.drawText(footerRect, Qt::AlignLeft, QDate::currentDate().toString("dd/MM/yyyy"));
            painter.drawText(footerRect, Qt::AlignRight, QString("Page %1").arg(pageCount));

            writer.newPage();
            pageCount++;
            y = pageMargin;  // reset y position on new page

            // Redraw Title on new page
            painter.setFont(QFont("Arial", 18, QFont::Bold));
            titleRect = QRect(pageMargin, y, tableWidth, titleHeight);
            painter.drawText(titleRect, Qt::AlignCenter, "Liste des Materiels");
            y += titleHeight + 20;

            // Redraw Table Header on new page
            painter.setFont(QFont("Arial", 12, QFont::Bold));
            headerRect = QRect(pageMargin, y, tableWidth, rowHeight);
            painter.fillRect(headerRect, QColor(230, 230, 230));
            painter.drawRect(headerRect);
            x = pageMargin;
            painter.drawText(QRect(x, y, col1Width, rowHeight), Qt::AlignCenter, "ID");
            painter.drawLine(x + col1Width, y, x + col1Width, y + rowHeight);
            x += col1Width;
            painter.drawText(QRect(x, y, col2Width, rowHeight), Qt::AlignCenter, "Type");
            painter.drawLine(x + col2Width, y, x + col2Width, y + rowHeight);
            x += col2Width;
            painter.drawText(QRect(x, y, col3Width, rowHeight), Qt::AlignCenter, "Etat");
            painter.drawLine(x + col3Width, y, x + col3Width, y + rowHeight);
            x += col3Width;
            painter.drawText(QRect(x, y, col4Width, rowHeight), Qt::AlignCenter, "Localisation");
            painter.drawLine(x + col4Width, y, x + col4Width, y + rowHeight);
            x += col4Width;
            painter.drawText(QRect(x, y, col5Width, rowHeight), Qt::AlignCenter, "Disponibilite");
            y += rowHeight;
            rowCount = 0;
        }

        // Draw Data Row Background (alternating colors)
        QRect rowRect(pageMargin, y, tableWidth, rowHeight);
        if (rowCount % 2 == 0) {
            painter.fillRect(rowRect, QColor(252, 252, 252));
        } else {
            painter.fillRect(rowRect, QColor(245, 245, 245));
        }
        painter.drawRect(rowRect);

        // Draw cell data
        x = pageMargin;
        painter.drawText(QRect(x, y, col1Width, rowHeight), Qt::AlignCenter, query.value("id").toString());
        painter.drawLine(x + col1Width, y, x + col1Width, y + rowHeight);
        x += col1Width;
        painter.drawText(QRect(x, y, col2Width, rowHeight), Qt::AlignCenter, query.value("type").toString());
        painter.drawLine(x + col2Width, y, x + col2Width, y + rowHeight);
        x += col2Width;
        painter.drawText(QRect(x, y, col3Width, rowHeight), Qt::AlignCenter, query.value("etat").toString());
        painter.drawLine(x + col3Width, y, x + col3Width, y + rowHeight);
        x += col3Width;
        painter.drawText(QRect(x, y, col4Width, rowHeight), Qt::AlignCenter, query.value("localisation").toString());
        painter.drawLine(x + col4Width, y, x + col4Width, y + rowHeight);
        x += col4Width;
        painter.drawText(QRect(x, y, col5Width, rowHeight), Qt::AlignCenter, query.value("disponibilite").toString());

        y += rowHeight;
        rowCount++;
    }

    // Draw Footer on the last page
    painter.setFont(QFont("Arial", 10));
    QRect footerRect(pageMargin, pageHeight - pageMargin, tableWidth, footerHeight);
    painter.drawText(footerRect, Qt::AlignLeft, QDate::currentDate().toString("dd/MM/yyyy"));
    painter.drawText(footerRect, Qt::AlignRight, QString("Page %1").arg(pageCount));

    painter.end();
    return true;
}


bool MaterielManager::clearDatabase()
{
    QSqlQuery query;
    if (!query.exec("DELETE FROM materiels")) {
        qDebug() << "Error clearing database: " << query.lastError().text();
        return false;  // Return false if the operation fails
    }
    return true;  // Return true if successful
}

