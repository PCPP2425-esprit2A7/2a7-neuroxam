#include "examen.h"
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include "connection.h"

// Constructeurs
Examen::Examen() {}

Examen::Examen(int id, QDate date, QTime heure, QString matiere, QString centre, QString type)
    : id(id), dateExamen(date), heureExamen(heure), matiere(matiere), centreExamen(centre), typeExamen(type) {}

Examen::Examen(QDate date, QTime heure, QString matiere, QString centre, QString type)
    : dateExamen(date), heureExamen(heure), matiere(matiere), centreExamen(centre), typeExamen(type) {}

// Getters
int Examen::getID() const {
    return id;
}

QDate Examen::getDateExamen() const {
    return dateExamen;
}

QTime Examen::getHeureExamen() const {
    return heureExamen;
}

QString Examen::getMatiere() const {
    return matiere;
}

QString Examen::getCentreExamen() const {
    return centreExamen;
}

QString Examen::getTypeExamen() const {
    return typeExamen;
}

// Setters
void Examen::setID(int id) {
    this->id = id;
}

void Examen::setDateExamen(QDate date) {
    this->dateExamen = date;
}

void Examen::setHeureExamen(QTime heure) {
    this->heureExamen = heure;
}

void Examen::setMatiere(QString matiere) {
    this->matiere = matiere;
}

void Examen::setCentreExamen(QString centre) {
    this->centreExamen = centre;
}

void Examen::setTypeExamen(QString type) {
    this->typeExamen = type;
}

// Méthodes de gestion de la base de données
bool Examen::ajouter() {
    QSqlQuery query;

    query.prepare("INSERT INTO examens ( DATE_EXAMEN, HEURE_EXAMEN, MATIERE, CENTRE_EXAMEN, TYPE_EXAMEN) "
                  "VALUES ( :date_examen, :heure_examen, :matiere, :centre_examen, :type_examen)");


    query.bindValue(":date_examen", dateExamen);
    query.bindValue(":heure_examen", heureExamen);
    query.bindValue(":matiere", matiere);
    query.bindValue(":centre_examen", centreExamen);
    query.bindValue(":type_examen", typeExamen);

    return query.exec();
}

QSqlQueryModel* Examen::afficher() {
    Connection c;
    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "Database connection lost, attempting to reconnect...";
        QSqlDatabase::database().open();
    }
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;

    // Only format the time column, leave the date column untouched
    query.prepare("SELECT ID_EXAMEN, MATIERE, CENTRE_EXAMEN, TYPE_EXAMEN, DATE_EXAMEN, "
                  "TO_CHAR(HEURE_EXAMEN, 'HH:MI AM') as HEURE_EXAMEN "
                  "FROM examens ORDER BY ID_EXAMEN");

    if (query.exec()) {
        model->setQuery(query);
        qDebug() << "Data fetched successfully. Rows:" << model->rowCount();
    } else {
        qDebug() << "Failed to execute query:" << query.lastError().text();
    }

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Matière"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Centre"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("heure"));

    return model;
}

bool Examen::supprimer(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM examens WHERE ID_EXAMEN = :id");
    query.bindValue(":id", id);
    return query.exec();
}

bool Examen::modifier(int id) {
    QSqlQuery query;

    query.prepare("UPDATE examens SET DATE_EXAMEN = :date_examen, HEURE_EXAMEN = :heure_examen, "
                  "MATIERE = :matiere, CENTRE_EXAMEN = :centre_examen, TYPE_EXAMEN = :type_examen "
                  "WHERE ID_EXAMEN = :id");

    query.bindValue(":id", id);
    query.bindValue(":date_examen", dateExamen);
    query.bindValue(":heure_examen", heureExamen);
    query.bindValue(":matiere", matiere);
    query.bindValue(":centre_examen", centreExamen);
    query.bindValue(":type_examen", typeExamen);

    return query.exec();
}


