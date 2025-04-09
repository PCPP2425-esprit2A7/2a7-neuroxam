#ifndef EXAMEN_H
#define EXAMEN_H

#include <QString>
#include <QSqlQueryModel>
#include <QDate>
#include <QTime>

class examen
{
public:
    examen();
    examen(const QDate &date_examen, const QString &heure_examen, const QString &matiere,
           const QString &type_examen, const QString &centre_examen);

    int getIdExamen() const;
    QDate getDateExamen() const;
    QString getHeureExamen() const;
    QString getMatiere() const;
    QString getTypeExamen() const;
    QString getCentreExamen() const;

    void setIdExamen(int id_examen) { this->id_examen = id_examen; }
    void setDateExamen(const QDate &date_examen);
    void setHeureExamen(const QString &heure_examen);
    void setMatiere(const QString &matiere);
    void setTypeExamen(const QString &type_examen);
    void setCentreExamen(const QString &centre_examen);

    bool create();
    static bool remove(int id_examen);
    static examen read(int id_examen);
    bool update(int id_examen, const QDate &date_examen, const QString &heure_examen, const QString &matiere,
                const QString &type_examen, const QString &centre_examen);

    QSqlQueryModel* afficher();
    static bool exists(int id_examen);

    QSqlQueryModel* trier(const QString& critere, bool ascendant = true);
    QSqlQueryModel* rechercher(const QString& keyword);
    QString genererContenuPDF();
    void genererPDF(const QString& fichierPDF);
    QMap<QString, int> obtenirStatistiques();

private:
    int id_examen;
    QDate date_examen;
    QString heure_examen;
    QString matiere;
    QString type_examen;
    QString centre_examen;
};

#endif // EXAMEN_H
