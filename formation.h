#ifndef FORMATION_H
#define FORMATION_H

#include <QString>
#include <QDate>
#include <QTime>
#include <QSqlQueryModel>

class Formation
{
private:
    int id;
    QString sujet;
    QDate date;
    QTime heure;
    int duree;
    QString statut;
    QString nom_formateur;       // 🔹 Remplace id_employe par nom_formateur
    QString nom_centre;          // 🔹 Nom du centre
    int nbre_invites;            // 🔹 Nombre d'invités
    QString codes_rfid;          // 🔹 Codes RFID

public:
    // 🔹 Constructeurs
    Formation();
    Formation(QString sujet, QDate date, QTime heure, int duree, QString statut, QString nom_formateur, QString nom_centre, int nbre_invites, QString codes_rfid = "");
    Formation(int id, QString sujet, QDate date, QTime heure, int duree, QString statut, QString nom_formateur, QString nom_centre, int nbre_invites, QString codes_rfid = "");

    // 🔹 Getters
    int getId() const;
    QString getSujet() const;
    QDate getDate() const;
    QTime getHeure() const;
    int getDuree() const;
    QString getStatut() const;
    QString getNomFormateur() const;    // 🔹 Getter pour nom_formateur
    QString getNomCentre() const;       // 🔹 Getter pour nom_centre
    int getNbreInvites() const;         // 🔹 Getter pour nbre_invites
    QString getCodesRFID() const;       // 🔹 Getter pour codes_rfid

    // 🔹 Setters
    void setCodesRFID(const QString &codes);  // 🔹 Setter pour RFID

    // 🔹 Méthodes de manipulation
    bool ajouter();
    bool modifier(int id);
    bool supprimer(int id);
    bool existe(int id);
    Formation getById(int id);

    // 🔹 Affichage et requêtes
    QSqlQueryModel* afficher();
    QSqlQueryModel* afficherCombinéDateHeure();
    QSqlQueryModel* rechercherParSujet(const QString &sujet);
    QSqlQueryModel* rechercherMulticritere(const QString &input);
    QSqlQueryModel* trierPar(const QString &critere, const QString &ordre);
    QSqlQueryModel* filtrerParStatut(const QString &statut);
    int compterParStatut(const QString &statut);
    QStringList getTousLesSujets();
};

#endif // FORMATION_H
