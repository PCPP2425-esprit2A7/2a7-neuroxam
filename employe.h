#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QString>
#include <QSqlQueryModel>
#include <QDate>

class employe
{
public:
    employe();
    employe(const QString &nom, const QString &prenom, const QString &numero_telephone,
            const QString &email, const QString &password, const QDate &date_dembauche);

    int getId() const;
    QString getNom() const;
    QString getPrenom() const;
    QString getNumeroTelephone() const;
    QString getEmail() const;
    QString getPassword() const;
    QDate getDateDembauche() const;

    void setId(int id) { this->id = id; }
    void setNom(const QString &nom);
    void setPrenom(const QString &prenom);
    void setNumeroTelephone(const QString &numero_telephone);
    void setEmail(const QString &email);
    void setPassword(const QString &password);
    void setDateDembauche(const QDate &date_dembauche) ;
    bool create();
    static employe read(int id);
    static bool exists(int id);
    QSqlQueryModel* afficher();
    bool update(int id, const QString &nom, const QString &prenom, const QString &numero_telephone,
     const QString &email, const QString &password, const QDate &date_dembauche);
    static bool remove(int id);

private:
    int id;
    QString nom;
    QString prenom;
    QString numero_telephone;
    QString email;
    QString password;
    QDate date_dembauche;
};

#endif // EMPLOYE_H
