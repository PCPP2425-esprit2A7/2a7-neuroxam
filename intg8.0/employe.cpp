#include "employe.h"
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
employe::employe() : id(-1) {}

// Constructeur paramétré
employe::employe(const QString &nom, const QString &prenom, const QString &numero_telephone,
                 const QString &email, const QString &password, const QDate &date_dembauche)
    : id(-1), nom(nom), prenom(prenom), numero_telephone(numero_telephone),
    email(email), password(password), date_dembauche(date_dembauche) {}

// Getters
int employe::getId() const { return id; }
QString employe::getNom() const { return nom; }
QString employe::getPrenom() const { return prenom; }
QString employe::getNumeroTelephone() const { return numero_telephone; }
QString employe::getEmail() const { return email; }
QString employe::getPassword() const { return password; }
QDate employe::getDateDembauche() const { return date_dembauche; }

// Setters
void employe::setId(int id) { this->id = id; }
void employe::setNom(const QString &nom) { this->nom = nom; }
void employe::setPrenom(const QString &prenom) { this->prenom = prenom; }
void employe::setNumeroTelephone(const QString &numero_telephone) { this->numero_telephone = numero_telephone; }
void employe::setEmail(const QString &email) { this->email = email; }
void employe::setPassword(const QString &password) { this->password = password; }
void employe::setDateDembauche(const QDate &date_dembauche) { this->date_dembauche = date_dembauche; }

bool employe::create() {
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("INSERT INTO employe (id, nom, prenom, numero_telephone, email, password, date_dembauche) "
                  "VALUES (EMPLOYE_SEQ.NEXTVAL, :nom, :prenom, :numero_telephone, :email, :password, TO_DATE(:date_dembauche, 'YYYY-MM-DD'))");

    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":numero_telephone", numero_telephone);
    query.bindValue(":email", email);
    query.bindValue(":password", password);
    query.bindValue(":date_dembauche", date_dembauche.toString("yyyy-MM-dd"));

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'insertion :" << query.lastError();
        return false;
    }

    id = query.lastInsertId().toInt();  // Récupérer l'ID auto-généré
    return true;
}

// Read
employe employe::read(int id) {
    employe emp;  // Créer un objet employe vide
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return emp;
    }

    QSqlQuery query(db);
    query.prepare("SELECT * FROM employe WHERE id = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        if (query.next()) {  // Si un résultat est trouvé
            emp.setId(query.value("id").toInt());
            emp.setNom(query.value("nom").toString());
            emp.setPrenom(query.value("prenom").toString());
            emp.setNumeroTelephone(query.value("numero_telephone").toString());
            emp.setEmail(query.value("email").toString());
            emp.setPassword(query.value("password").toString());
            emp.setDateDembauche(query.value("date_dembauche").toDate());
        } else {
            qDebug() << "Aucun employé trouvé avec l'ID:" << id;
        }
    } else {
        qDebug() << "Erreur lors de la récupération de l'employé :" << query.lastError().text();
    }

    return emp;  // Retourner l'objet employe
}

// Afficher
QSqlQueryModel* employe::afficher() {
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return nullptr;
    }

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM employe", db);

    // Configuration des en-têtes de colonnes
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Telephone"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Password"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date Dembauche"));

    return model;
}

// Update
bool employe::update(int id, const QString &nom, const QString &prenom, const QString &numero_telephone,
                     const QString &email, const QString &password, const QDate &date_dembauche) {
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("UPDATE employe SET nom = :nom, prenom = :prenom, numero_telephone = :numero_telephone, "
                  "email = :email, password = :password, date_dembauche = TO_DATE(:date_dembauche, 'YYYY-MM-DD') "
                  "WHERE id = :id");

    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":numero_telephone", numero_telephone);
    query.bindValue(":email", email);
    query.bindValue(":password", password);
    query.bindValue(":date_dembauche", date_dembauche.toString("yyyy-MM-dd"));
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la mise à jour de l'employé : " << query.lastError().text();
        return false;
    }

    return true;
}

// Remove
bool employe::remove(int id) {
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("DELETE FROM employe WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la suppression :" << query.lastError();
        return false;
    }
    return true;
}


QMap<QString, int> employe::obtenirStatistiques()
{
    QMap<QString, int> stats;
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return stats;
    }

    QSqlQuery query(db);
    query.prepare("SELECT prenom, COUNT(*) FROM EMPLOYE GROUP BY prenom");

    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError().text();
        return stats;  // ❗ return explicitly if the query fails
    }

    while (query.next()) {
        stats.insert(query.value(0).toString(), query.value(1).toInt());
    }

    return stats;  // ✅ always reached
}



// Exists
bool employe::exists(int id) {
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM employe WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête :" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        return query.value(0).toInt() > 0;
    }

    return false;
}
QSqlQueryModel* employe::rechercher(const QString& valeur) {
    QSqlQuery query;
    QString queryString;

    if (valeur.toInt() > 0) {
        queryString = "SELECT * FROM EMPLOYE WHERE ID = :valeur";
    } else {
        queryString = "SELECT * FROM EMPLOYE "
                      "WHERE NOM LIKE :valeurLike "
                      "OR PRENOM LIKE :valeurLike "
                      "OR NUMERO_TELEPHONE LIKE :valeurLike "
                      "OR EMAIL LIKE :valeurLike";
    }

    query.prepare(queryString);

    if (valeur.toInt() > 0) {
        query.bindValue(":valeur", valeur);
    } else {
        query.bindValue(":valeurLike", "%" + valeur + "%");
    }

    qDebug() << "Query:" << queryString;
    if (!query.exec()) {
        qDebug() << "Erreur requête:" << query.lastError().text();
    }

    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(std::move(query));

    return model;
}
QSqlQueryModel* employe::trier(const QString& critere, bool ascendant) {
    QSqlQuery query;
    QString queryString = "SELECT * FROM EMPLOYE";

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
QString employe::genererContenuPDF() {
    QString html = R"(
    <html>
    <head>
        <style>
            body { font-family: Arial; margin: 0; padding: 0; }
            h1 { text-align: center; color: #333; font-size: 18px; }
            table { width: 100%; border-collapse: collapse; }
            th, td { border: 1px solid #ccc; padding: 8px; font-size: 9px; white-space: nowrap; }
            th { background-color: #f2f2f2; font-weight: bold; }
            .footer { text-align: center; font-size: 10px; color: #666; margin-top: 15px; }
        </style>
    </head>
    <body>
        <h1>Rapport des Employés</h1>
        <table>
            <tr>
                <th>ID</th>
                <th>Nom</th>
                <th>Prénom</th>
                <th>Téléphone</th>
                <th>Email</th>
                <th>Password</th>
                <th>Date d'embauche</th>
            </tr>
    )";

    QSqlQuery query("SELECT * FROM EMPLOYE");
    while (query.next()) {
        html += QString(
                    "<tr>"
                    "<td>%1</td><td>%2</td><td>%3</td>"
                    "<td>%4</td><td>%5</td><td>%6</td><td>%7</td>"
                    "</tr>")
                    .arg(query.value(0).toInt())
                    .arg(query.value(1).toString())
                    .arg(query.value(2).toString())
                    .arg(query.value(3).toString())
                    .arg(query.value(4).toString())
                    .arg(query.value(5).toString())
                    .arg(query.value(6).toString());
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

void employe::genererPDF(const QString& fichierPDF) {
    QString contenuHTML = genererContenuPDF();

    QTextDocument document;
    document.setHtml(contenuHTML);

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageOrientation(QPageLayout::Landscape);
    printer.setOutputFileName(fichierPDF);
    printer.setPageMargins(QMarginsF(5, 5, 5, 5));

    document.print(&printer);
}
