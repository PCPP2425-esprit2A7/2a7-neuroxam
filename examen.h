#ifndef EXAMEN_H
#define EXAMEN_H

#include <QString>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDate>
#include <QTime>

class Examen {
public:
    Examen();
    Examen(int id, QDate date, QTime heure, QString matiere, QString centre, QString type);
    Examen(QDate date, QTime heure, QString matiere, QString centre, QString type);

    // Getter methods
    int getID() const;
    QDate getDateExamen() const;
    QTime getHeureExamen() const;
    QString getMatiere() const;
    QString getCentreExamen() const;
    QString getTypeExamen() const;

    // Setter methods
    void setID(int id);
    void setDateExamen(QDate date);
    void setHeureExamen(QTime heure);
    void setMatiere(QString matiere);
    void setCentreExamen(QString centre);
    void setTypeExamen(QString type);

    // Database operations
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int id);
    bool modifier(int id);
    static QSqlQueryModel* rechercherParMatiere(QString matiere);
    QSqlQueryModel* Tri(QString cls, QString champ);

private:
    int id;
    QDate dateExamen;
    QTime heureExamen;
    QString matiere;
    QString centreExamen;
    QString typeExamen;
};

#endif // EXAMEN_H
