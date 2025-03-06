#ifndef CENTRE_H
#define CENTRE_H

#include <QString>
#include <QSqlQueryModel>

class centre
{
public:
    centre();
    centre(const QString &nom, const QString &adresse, const QString &directeur,
            const QString &facilities,
            int status,int capacite );

    int getId() const;
    QString getNom() const;
    QString getAdresse() const;
    QString getDirecteur() const;
    QString getFacilities() const;
    int getStatus() const;
    int getCapacite() const;

    void setId(int id) { this->id = id; }
    void setNom(const QString &nom);
    void setAdresse(const QString &adresse);
    void setDirecteur(const QString &directeur);
    void setFacilities(const QString &facilities);
    void setStatus(int status);
    void setCapacite(int capacite);


    bool create();
    static bool remove(int id);
    static centre read(int id);
    bool update(int id, const QString &nom, const QString &adresse, const QString &directeur,
                const QString &facilities, int status, int capacite);


    QSqlQueryModel* afficher();
    static bool exists(int id);


    QSqlQueryModel* trier(const QString& critere, bool ascendant = true);
    QSqlQueryModel* rechercher(const QString& keyword);
    QString genererContenuPDF();
    void genererPDF(const QString& fichierPDF);
    QMap<QString, int> obtenirStatistiques();

private:
    int id;
    QString nom;
    QString adresse;
    QString directeur;
    QString facilities;
    int status;
    int capacite;
};

#endif // CENTRE_H
