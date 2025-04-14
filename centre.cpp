#include "centre.h"
#include "connection.h"
#include"recommendation.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QDebug>
#include <QPdfWriter>
#include <QPainter>
#include <QPrinter>
#include <QFile>
#include <QTextDocument>
#include <QDate>
#include <QGeoCoordinate>
centre::centre() : id(-1), status(0), capacite(0) {}

centre::centre(const QString &nom, const QString &adresse, const QString &directeur,
               const QString &facilities, int status, int capacite)
    : id(-1), nom(nom), adresse(adresse), directeur(directeur),
    facilities(facilities), status(status), capacite(capacite) {}


int centre::getId() const { return id; }
QString centre::getNom() const { return nom; }
QString centre::getAdresse() const { return adresse; }
QString centre::getDirecteur() const { return directeur; }
QString centre::getFacilities() const { return facilities; }
int centre::getStatus() const { return status; }
int centre::getCapacite() const { return capacite; }


void centre::setNom(const QString &nom) { this->nom = nom; }
void centre::setAdresse(const QString &adresse) { this->adresse = adresse; }
void centre::setDirecteur(const QString &directeur) { this->directeur = directeur; }
void centre::setFacilities(const QString &facilities) { this->facilities = facilities; }
void centre::setStatus(int status) { this->status = status; }
void centre::setCapacite(int capacite) { this->capacite = capacite; }


bool centre::exists(int id) {
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM CENTRE WHERE id = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        if (query.next()) {
            return query.value(0).toInt() > 0;
        }
    }
    return false;
}


bool centre::create() {
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("INSERT INTO CENTRE (nom, adresse, directeur, facilities, status, capacite) "
                  "VALUES (:nom, :adresse, :directeur, :facilities, :status, :capacite)");

    query.bindValue(":nom", nom);
    query.bindValue(":adresse", adresse);
    query.bindValue(":directeur", directeur);
    query.bindValue(":facilities", facilities);
    query.bindValue(":status", status);
    query.bindValue(":capacite", capacite);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'insertion :" << query.lastError();
        return false;
    }

    id = query.lastInsertId().toInt();
    return true;
}

QSqlQueryModel* centre::afficher() {
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return nullptr;
    }

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM CENTRE", db);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Directeur"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Facilities"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Status"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Capacite"));

    return model;
}

bool centre::remove(int id) {
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("DELETE FROM CENTRE WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la suppression :" << query.lastError();
        return false;
    }

    return true;
}


centre centre::read(int id) {
    centre c;  // Créer un objet centre vide
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return c;
    }

    QSqlQuery query(db);
    query.prepare("SELECT * FROM CENTRE WHERE id = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        if (query.next()) {  // Si un résultat est trouvé
            c.setId(query.value("id").toInt());
            c.setNom(query.value("nom").toString());
            c.setAdresse(query.value("adresse").toString());
            c.setDirecteur(query.value("directeur").toString());
            c.setFacilities(query.value("facilities").toString());
            c.setStatus(query.value("status").toInt());
            c.setCapacite(query.value("capacite").toInt());
        } else {
            qDebug() << "Aucun centre trouvé avec l'ID:" << id;
        }
    } else {
        qDebug() << "Erreur lors de la récupération du centre :" << query.lastError().text();
    }

    return c;
}


bool centre::update(int id, const QString &nom, const QString &adresse, const QString &directeur,
                    const QString &facilities, int status, int capacite) {
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);

    query.prepare("SELECT COUNT(*) FROM CENTRE WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();
    query.next();

    if (query.value(0).toInt() == 0) {
        qDebug() << "Le centre avec l'ID " << id << " n'existe pas.";
        return false;  // Le centre n'existe pas
    }

    query.prepare("UPDATE CENTRE SET nom = :nom, adresse = :adresse, directeur = :directeur, "
                  "facilities = :facilities, status = :status, capacite = :capacite "
                  "WHERE id = :id");

    query.bindValue(":nom", nom);
    query.bindValue(":adresse", adresse);
    query.bindValue(":directeur", directeur);
    query.bindValue(":facilities", facilities);
    query.bindValue(":status", status);
    query.bindValue(":capacite", capacite);
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la mise à jour du centre : " << query.lastError().text();
        return false;
    }

    qDebug() << "Centre avec ID " << id << " modifié avec succès.";
    return true;
}

QSqlQueryModel* centre::trier(const QString& critere, bool ascendant) {
    QSqlQuery query;
    QString queryString = "SELECT * FROM CENTRE";

    if (!critere.isEmpty()) {
        queryString += " ORDER BY " + critere;
        if (!ascendant) {
            queryString += " DESC";
        }
    }

    query.prepare(queryString);
    query.exec();

    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(std::move(query));

    return model;
}


QSqlQueryModel* centre::rechercher(const QString& valeur) {
    QSqlQuery query;
    QString queryString;

    if (valeur.toInt() > 0) {
        queryString = "SELECT * FROM CENTRE WHERE id = :valeur";
    } else {
        queryString = "SELECT * FROM CENTRE "
                      "WHERE nom LIKE :valeurLike "
                      "OR adresse LIKE :valeurLike "
                      "OR directeur LIKE :valeurLike "
                      "OR facilities LIKE :valeurLike";
    }

    query.prepare(queryString);

    if (valeur.toInt() > 0) {
        query.bindValue(":valeur", valeur);
    } else {
        query.bindValue(":valeurLike", "%" + valeur + "%");
    }

    qDebug() << "Executing query:" << queryString;
    qDebug() << "Binding values - " << (valeur.toInt() > 0 ? "exact:" : "LIKE pattern:") << valeur;

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
    }

    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(std::move(query));

    return model;
}

// Méthode pour générer le contenu HTML du PDF
QString centre::genererContenuPDF() {
    QString html = R"(
    <html>
    <head>
        <style>
            body {
                font-family: Arial, sans-serif;
                margin: 0;
                padding: 0;
            }
            h1 {
                text-align: center;
                color: #333;
                margin-bottom: 10px;
                font-size: 18px;
            }
            table {
                width: 100%;
                border-collapse: collapse;
            }
            th, td {
                border: 1px solid #dddddd;
                padding: 8px;
                text-align: left;
                font-size: 9px;
                white-space: nowrap;
            }
            th {
                background-color: #f2f2f2;
                font-weight: bold;
            }
            .footer {
                text-align: center;
                font-size: 10px;
                color: #666;
                margin-top: 15px;
            }
        </style>
    </head>
    <body>
        <h1>Rapport des Centres</h1>
        <table>
            <tr>
                <th>ID</th>
                <th>Nom</th>
                <th>Adresse</th>
                <th>Directeur</th>
                <th>Facilities</th>
                <th>Status</th>
                <th>Capacite</th>
            </tr>
    )";

    // Ajouter les centres à la table dans la boucle
    QSqlQuery query("SELECT * FROM CENTRE");
    while (query.next()) {
        int id = query.value(0).toInt();
        QString nom = query.value(1).toString();
        QString adresse = query.value(2).toString();
        QString directeur = query.value(3).toString();
        QString facilities = query.value(4).toString();
        int status = query.value(5).toInt();
        int capacite = query.value(6).toInt();

        html += QString(
                    "<tr>"
                    "<td>%1</td>"
                    "<td>%2</td>"
                    "<td>%3</td>"
                    "<td>%4</td>"
                    "<td>%5</td>"
                    "<td>%6</td>"
                    "<td>%7</td>"
                    "</tr>"
                    ).arg(id)
                    .arg(nom)
                    .arg(adresse)
                    .arg(directeur)
                    .arg(facilities)
                    .arg(status)
                    .arg(capacite);
    }

    html += QString(R"(
        </table>
        <div class='footer'>
            <p>Ce rapport a été généré automatiquement le %1.</p>
        </div>
    </body>
    </html>
    )").arg(QDate::currentDate().toString("dd/MM/yyyy"));

    return html;
}

// Méthode pour générer le PDF
void centre::genererPDF(const QString& fichierPDF) {
    QString contenuHTML = genererContenuPDF();  // Récupérer le contenu HTML généré

    QTextDocument document;
    document.setHtml(contenuHTML);

    // Configurer le QPrinter pour créer un PDF
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageOrientation(QPageLayout::Landscape); // Utilisez setPageOrientation
    printer.setOutputFileName(fichierPDF);

    // Réduire les marges de la page pour maximiser l'espace
    printer.setPageMargins(QMarginsF(5, 5, 5, 5));

    // Imprimer le document dans le fichier PDF
    document.print(&printer);
}
QMap<QString, int> centre::obtenirStatistiques() {
    QMap<QString, int> stats;
    QSqlQuery query;
    query.prepare("SELECT status, COUNT(*) FROM CENTRE GROUP BY status");
    if (!query.exec()) {
        return stats;  // Retourner un map vide en cas d'erreur
    }

    while (query.next()) {
        QString status = query.value(0).toString();
        int count = query.value(1).toInt();
        stats.insert(status, count);
    }

    return stats;
}
QPieSeries* centre::statistiquesParstatus() {
    QPieSeries* series = new QPieSeries();

    QSqlDatabase db = Connection::get_database();
    QSqlQuery query(db);
    query.prepare("SELECT status, COUNT(*) FROM CENTRE GROUP BY status");

    if (query.exec()) {
        while (query.next()) {
            QString status = query.value(0).toString();
            int count = query.value(1).toInt();
            series->append(status, count);
        }
    } else {
        qDebug() << "Erreur lors de la récupération des statistiques par sexe : " << query.lastError().text();
    }

    return series;
}


QGeoCoordinate centre::getCoordinate() const {
    return coordinate;
}

void centre::setCoordinate(const QGeoCoordinate &coord) {
    coordinate = coord;
}

void centre::setCoordinate(double latitude, double longitude) {
    coordinate = QGeoCoordinate(latitude, longitude);
}

QList<QPair<QString, QGeoCoordinate>> centre::getAllCoordinates() {
    QList<QPair<QString, QGeoCoordinate>> coordinates;
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return coordinates;
    }

    QSqlQuery query(db);
    query.prepare("SELECT nom, adresse FROM CENTRE");

    if (query.exec()) {
        while (query.next()) {
            QString name = query.value(0).toString();
            QString address = query.value(1).toString();

            // Parse coordinates from address (assuming format "lat,lon")
            QStringList parts = address.split(",");
            if (parts.size() == 2) {
                bool ok1, ok2;
                double lat = parts[0].trimmed().toDouble(&ok1);
                double lon = parts[1].trimmed().toDouble(&ok2);
                if (ok1 && ok2) {
                    coordinates.append(qMakePair(name, QGeoCoordinate(lat, lon)));
                }
            }
        }
    } else {
        qDebug() << "Error fetching coordinates:" << query.lastError().text();
    }

    return coordinates;
}

