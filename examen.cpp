#include "examen.h"
#include "connection.h"
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

// Constructeur par défaut
examen::examen() : id_examen(-1), date_examen(QDate::currentDate()), matiere(""), type_examen(""), centre_examen("") {}

// Constructeur paramétré
examen::examen(const QDate &date_examen, const QString &heure_examen, const QString &matiere,
               const QString &type_examen, const QString &centre_examen)
    : id_examen(-1), date_examen(date_examen), heure_examen(heure_examen), matiere(matiere),
    type_examen(type_examen), centre_examen(centre_examen) {}

// Getters
int examen::getIdExamen() const { return id_examen; }
QDate examen::getDateExamen() const { return date_examen; }
QString examen::getHeureExamen() const { return heure_examen; }
QString examen::getMatiere() const { return matiere; }
QString examen::getTypeExamen() const { return type_examen; }
QString examen::getCentreExamen() const { return centre_examen; }

// Setters
void examen::setDateExamen(const QDate &date_examen) { this->date_examen = date_examen; }
void examen::setHeureExamen(const QString &heure_examen) { this->heure_examen = heure_examen; }
void examen::setMatiere(const QString &matiere) { this->matiere = matiere; }
void examen::setTypeExamen(const QString &type_examen) { this->type_examen = type_examen; }
void examen::setCentreExamen(const QString &centre_examen) { this->centre_examen = centre_examen; }

// Méthode pour vérifier si un examen existe
bool examen::exists(int id_examen) {
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM EXAMEN WHERE id_examen = :id_examen");
    query.bindValue(":id_examen", id_examen);

    if (query.exec()) {
        if (query.next()) {
            return query.value(0).toInt() > 0; // Retourne true si l'examen existe
        }
    }
    return false; // Retourne false en cas d'erreur ou si l'examen n'existe pas
}

// Méthode Create
bool examen::create() {
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("INSERT INTO EXAMEN (date_examen, heure_examen, matiere, type_examen, centre_examen) "
                  "VALUES (TO_DATE(:date_examen, 'YYYY-MM-DD'), :heure_examen, :matiere, :type_examen, :centre_examen)");

    query.bindValue(":date_examen", date_examen.toString("yyyy-MM-dd"));
    query.bindValue(":heure_examen", heure_examen);
    query.bindValue(":matiere", matiere);
    query.bindValue(":type_examen", type_examen);
    query.bindValue(":centre_examen", centre_examen);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'insertion :" << query.lastError();
        return false;
    }

    // Récupérer l'ID généré
    id_examen = query.lastInsertId().toInt();
    return true;
}

// Méthode afficher
QSqlQueryModel* examen::afficher() {
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return nullptr;
    }

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM EXAMEN", db);

    // Configuration des en-têtes de colonnes
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID Examen"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date Examen"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Heure Examen"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Matière"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Type Examen"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Centre Examen"));

    return model;
}

// Méthode Remove
bool examen::remove(int id_examen) {
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("DELETE FROM EXAMEN WHERE id_examen = :id_examen");
    query.bindValue(":id_examen", id_examen);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la suppression :" << query.lastError();
        return false;
    }

    return true;
}

// Méthode Read
examen examen::read(int id_examen) {
    examen e;  // Créer un objet examen vide
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return e;
    }

    QSqlQuery query(db);
    query.prepare("SELECT * FROM EXAMEN WHERE id_examen = :id_examen");
    query.bindValue(":id_examen", id_examen);

    if (query.exec()) {
        if (query.next()) {  // Si un résultat est trouvé
            e.setIdExamen(query.value("id_examen").toInt());
            e.setDateExamen(QDate::fromString(query.value("date_examen").toString(), "yyyy-MM-dd"));
            e.setHeureExamen(query.value("heure_examen").toString());
            e.setMatiere(query.value("matiere").toString());
            e.setTypeExamen(query.value("type_examen").toString());
            e.setCentreExamen(query.value("centre_examen").toString());
        } else {
            qDebug() << "Aucun examen trouvé avec l'ID:" << id_examen;
        }
    } else {
        qDebug() << "Erreur lors de la récupération de l'examen :" << query.lastError().text();
    }

    return e;  // Retourner l'objet examen
}

// Méthode Update
bool examen::update(int id_examen, const QDate &date_examen, const QString &heure_examen, const QString &matiere,
                    const QString &type_examen, const QString &centre_examen) {
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);


    // Préparer la requête de mise à jour
    query.prepare("UPDATE EXAMEN SET date_examen = :date_examen, heure_examen = :heure_examen, "
                  "matiere = :matiere, type_examen = :type_examen, centre_examen = :centre_examen "
                  "WHERE id_examen = :id_examen");

    query.bindValue(":date_examen", date_examen);
    query.bindValue(":heure_examen", heure_examen);
    query.bindValue(":matiere", matiere);
    query.bindValue(":type_examen", type_examen);
    query.bindValue(":centre_examen", centre_examen);
    query.bindValue(":id_examen", id_examen);

    // Exécuter la requête et vérifier si elle a réussi
    if (!query.exec()) {
        qDebug() << "Erreur lors de la mise à jour de l'examen : " << query.lastError().text();
        return false;  // Si l'exécution échoue
    }

    qDebug() << "Examen avec ID " << id_examen << " modifié avec succès.";
    return true;
}
QMap<QString, int> examen::obtenirStatistiques() {
    QMap<QString, int> stats;
    QSqlQuery query;
    query.prepare("SELECT type_examen, COUNT(*) FROM EXAMEN GROUP BY type_examen");
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


// Méthode pour trier les examens
QSqlQueryModel* examen::trier(const QString& critere, bool ascendant) {
    QSqlQuery query;
    QString queryString = "SELECT * FROM EXAMEN";

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

// Méthode pour rechercher des examens
QSqlQueryModel* examen::rechercher(const QString& valeur) {
    QSqlQuery query;
    QString queryString;

    if (valeur.toInt() > 0) {
        // Recherche par ID (si la valeur est un entier positif)
        queryString = "SELECT * FROM EXAMEN WHERE id_examen = :valeur";
    } else {
        // Recherche par matiere, type_examen ou centre_examen
        queryString = "SELECT * FROM EXAMEN "
                      "WHERE matiere LIKE :valeurLike "
                      "OR type_examen LIKE :valeurLike "
                      "OR centre_examen LIKE :valeurLike";
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
QString examen::genererContenuPDF() {
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
        <h1>Rapport des Examens</h1>
        <table>
            <tr>
                <th>ID Examen</th>
                <th>Date Examen</th>
                <th>Heure Examen</th>
                <th>Matière</th>
                <th>Type Examen</th>
                <th>Centre Examen</th>
            </tr>
    )";

    // Ajouter les examens à la table dans la boucle
    QSqlQuery query("SELECT * FROM EXAMEN");
    while (query.next()) {
        int id_examen = query.value(0).toInt();
        QString date_examen = query.value(1).toString();
        QString heure_examen = query.value(2).toString();
        QString matiere = query.value(3).toString();
        QString type_examen = query.value(4).toString();
        QString centre_examen = query.value(5).toString();

        html += QString(
                    "<tr>"
                    "<td>%1</td>"
                    "<td>%2</td>"
                    "<td>%3</td>"
                    "<td>%4</td>"
                    "<td>%5</td>"
                    "<td>%6</td>"
                    "</tr>"
                    ).arg(id_examen)
                    .arg(date_examen)
                    .arg(heure_examen)
                    .arg(matiere)
                    .arg(type_examen)
                    .arg(centre_examen);
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
void examen::genererPDF(const QString& fichierPDF) {
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
