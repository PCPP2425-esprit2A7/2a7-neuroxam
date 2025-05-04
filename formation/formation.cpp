#include "formation.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QSqlError>
#include <QDebug>
#include "connection.h"
#include <QSqlQuery>
// 🔹 Constructeurs
Formation::Formation() {}

Formation::Formation(QString sujet, QDate date, QTime heure, int duree, QString statut, QString nom_formateur, QString nom_centre, int nbre_invites, QString codes_rfid)
    : sujet(sujet), date(date), heure(heure), duree(duree), statut(statut), nom_formateur(nom_formateur), nom_centre(nom_centre), nbre_invites(nbre_invites), codes_rfid(codes_rfid) {}

Formation::Formation(int id, QString sujet, QDate date, QTime heure, int duree, QString statut, QString nom_formateur, QString nom_centre, int nbre_invites, QString codes_rfid)
    : id(id), sujet(sujet), date(date), heure(heure), duree(duree), statut(statut), nom_formateur(nom_formateur), nom_centre(nom_centre), nbre_invites(nbre_invites), codes_rfid(codes_rfid) {}

// 🔹 Getters
int Formation::getId() const { return id; }
QString Formation::getSujet() const { return sujet; }
QDate Formation::getDate() const { return date; }
QTime Formation::getHeure() const { return heure; }
int Formation::getDuree() const { return duree; }
QString Formation::getStatut() const { return statut; }
QString Formation::getNomFormateur() const { return nom_formateur; }
QString Formation::getNomCentre() const { return nom_centre; }
int Formation::getNbreInvites() const { return nbre_invites; }
QString Formation::getCodesRFID() const { return codes_rfid; }

void Formation::setCodesRFID(const QString &codes) { this->codes_rfid = codes; }

bool Formation::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO FORMATION ( SUJET, DATE_FORMATION, HEURE_FORMATION, DUREE, STATUT, NOM_FORMATEUR, NOM_CENTRE, NBRE_INVITES, CODES_RFID) "
                  "VALUES ( :sujet, TO_DATE(:date, 'YYYY-MM-DD'), TO_DATE(:heure, 'YYYY-MM-DD HH24:MI:SS'), :duree, :statut, :nom_formateur, :nom_centre, :nbre_invites, :codes_rfid)");

    QDateTime dateHeure(date, heure);
    QString dateStr = QLocale::c().toString(date, "yyyy-MM-dd");
    QString heureStr = QLocale::c().toString(dateHeure, "yyyy-MM-dd HH:mm:ss");

    query.bindValue(":sujet", sujet);
    query.bindValue(":date", dateStr);
    query.bindValue(":heure", heureStr);
    query.bindValue(":duree", duree);
    query.bindValue(":statut", statut);
    query.bindValue(":nom_formateur", nom_formateur);
    query.bindValue(":nom_centre", nom_centre);
    query.bindValue(":nbre_invites", nbre_invites);
    query.bindValue(":codes_rfid", codes_rfid);

    if (!query.exec()) {
        qDebug() << "Erreur Oracle (ajouter) : " << query.lastError().text();
        return false;
    }
    return true;
}
QSqlQueryModel* Formation::rechercher(const QString& valeur) {
    QSqlQuery query;
    QString queryString;

    if (valeur.toInt() > 0) {
        // Recherche par ID_FORMATION si c'est un entier
        queryString = "SELECT * FROM FORMATION WHERE ID_FORMATION = :valeur";
        query.prepare(queryString);
        query.bindValue(":valeur", valeur);
    } else {
        // Recherche sur les champs texte
        queryString = R"(
            SELECT * FROM FORMATION
            WHERE LOWER(SUJET) LIKE :valeurLike
               OR LOWER(STATUT) LIKE :valeurLike
               OR LOWER(NOM_FORMATEUR) LIKE :valeurLike
               OR LOWER(NOM_CENTRE) LIKE :valeurLike
        )";
        query.prepare(queryString);
        query.bindValue(":valeurLike", "%" + valeur.toLower() + "%");
    }

    qDebug() << "Executing query:" << queryString;
    qDebug() << "Binding value:" << valeur;

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la recherche formation :" << query.lastError().text();
    }

    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(query);

    return model;
}



// 🔹 Modifier une formation
bool Formation::modifier(int id) {
    QSqlQuery query;
    query.prepare("UPDATE FORMATION SET SUJET=:sujet, DATE_FORMATION=:date, HEURE_FORMATION=:heure, DUREE=:duree, STATUT=:statut, "
                  "NOM_FORMATEUR=:nom_formateur, NOM_CENTRE=:nom_centre, NBRE_INVITES=:nbre_invites, CODES_RFID=:codes_rfid WHERE ID_FORMATION=:id");
    query.bindValue(":sujet", sujet);
    query.bindValue(":date", date);
    query.bindValue(":heure", QDateTime(date, heure));
    query.bindValue(":duree", duree);
    query.bindValue(":statut", statut);
    query.bindValue(":nom_formateur", nom_formateur);
    query.bindValue(":nom_centre", nom_centre);
    query.bindValue(":nbre_invites", nbre_invites);
    query.bindValue(":codes_rfid", codes_rfid);
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Erreur Oracle (modifier) : " << query.lastError().text();
        return false;
    }
    return true;
}

// 🔹 getById
Formation Formation::getById(int id) {
    QSqlQuery query;
    query.prepare("SELECT * FROM FORMATION WHERE ID_FORMATION = :id");
    query.bindValue(":id", id);
    if (query.exec() && query.next()) {
        return Formation(
            query.value("ID_FORMATION").toInt(),
            query.value("SUJET").toString(),
            query.value("DATE_FORMATION").toDate(),
            QTime::fromString(query.value("HEURE_FORMATION").toDateTime().time().toString("HH:mm"), "HH:mm"),
            query.value("DUREE").toInt(),
            query.value("STATUT").toString(),
            query.value("NOM_FORMATEUR").toString(),
            query.value("NOM_CENTRE").toString(),
            query.value("NBRE_INVITES").toInt(),
            query.value("CODES_RFID").toString()
            );
    }
    return Formation();
}

// 🔹 afficher
QSqlQueryModel* Formation::afficher() {
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM FORMATION ORDER BY ID_FORMATION");
    return model;
}

// 🔹 afficherCombinéDateHeure
QSqlQueryModel* Formation::afficherCombinéDateHeure() {
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT ID_FORMATION, SUJET, TO_CHAR(DATE_FORMATION, 'YYYY-MM-DD') AS DATE_FORMATION, "
                    "TO_CHAR(HEURE_FORMATION, 'HH24:MI') AS HEURE_FORMATION, DUREE, STATUT, NOM_FORMATEUR, NOM_CENTRE, NBRE_INVITES, CODES_RFID FROM FORMATION");
    return model;
}

// 🔹 Rechercher par sujet
QSqlQueryModel* Formation::rechercherParSujet(const QString &sujet) {
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM FORMATION WHERE LOWER(SUJET) LIKE :sujet");
    query.bindValue(":sujet", "%" + sujet.toLower() + "%");
    query.exec();
    model->setQuery(query);
    return model;
}

// 🔹 Trier par critère
QSqlQueryModel* Formation::trierPar(const QString &critere, const QString &ordre) {
    QSqlQueryModel *model = new QSqlQueryModel();
    QString queryStr = QString("SELECT * FROM FORMATION ORDER BY %1 %2").arg(critere, ordre);
    model->setQuery(queryStr);
    return model;
}

// 🔹 Filtrer par statut
QSqlQueryModel* Formation::filtrerParStatut(const QString &statut) {
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM FORMATION WHERE STATUT = :statut");
    query.bindValue(":statut", statut);
    query.exec();
    model->setQuery(query);
    return model;
}

// 🔹 Compter par statut
int Formation::compterParStatut(const QString &statut) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM FORMATION WHERE STATUT = :statut");
    query.bindValue(":statut", statut);
    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}

// 🔹 Obtenir tous les sujets
QStringList Formation::getTousLesSujets() {
    QStringList sujets;
    QSqlQuery query("SELECT DISTINCT SUJET FROM FORMATION");
    while (query.next()) {
        QString sujet = query.value(0).toString().trimmed();
        if (!sujet.isEmpty()) {
            sujets << sujet;
        }
    }
    return sujets;
}

// 🔹 Recherche multicritère
QSqlQueryModel* Formation::rechercherMulticritere(const QString &input) {
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    QString cleaned = input.trimmed();
    bool isInt = false;
    int id = cleaned.toInt(&isInt);

    if (isInt) {
        query.prepare("SELECT * FROM FORMATION WHERE ID_FORMATION = :id");
        query.bindValue(":id", id);
    }
    else if (QDate::fromString(cleaned, "dd/MM/yyyy").isValid()) {
        QDate date = QDate::fromString(cleaned, "dd/MM/yyyy");
        query.prepare("SELECT * FROM FORMATION WHERE TRUNC(DATE_FORMATION) = :date");
        query.bindValue(":date", date);
    }
    else if (QStringList{"Prévue", "En cours", "Terminée", "Annulée"}.contains(cleaned, Qt::CaseInsensitive)) {
        query.prepare("SELECT * FROM FORMATION WHERE LOWER(STATUT) = :statut");
        query.bindValue(":statut", cleaned.toLower());
    }
    else {
        query.prepare("SELECT * FROM FORMATION WHERE LOWER(SUJET) LIKE :sujet");
        query.bindValue(":sujet", "%" + cleaned.toLower() + "%");
    }

    query.exec();
    model->setQuery(query);
    return model;
}

// 🔹 Vérifie si une formation existe
bool Formation::existe(int id) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM FORMATION WHERE ID_FORMATION = :id");
    query.bindValue(":id", id);
    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }
    return false;
}

// 🔹 Supprimer une formation
bool Formation::supprimer(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM FORMATION WHERE ID_FORMATION = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Erreur Oracle (supprimer) : " << query.lastError().text();
        return false;
    }
    return true;
}
