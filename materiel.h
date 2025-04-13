#ifndef MATERIEL_H
#define MATERIEL_H
#include <QString>

class Materiel
{
private:
    int m_id;
    QString m_type;
    QString m_etat;
    QString m_localisation;
    QString m_disponibilite;

public:
    Materiel(const QString& type, const QString& etat, const QString& localisation, const QString& disponibilite)
        : m_id(0), m_type(type), m_etat(etat), m_localisation(localisation), m_disponibilite(disponibilite) {}

    int getId() const { return m_id; }
    void setId(int id) { m_id = id; }
    QString getType() const { return m_type; }
    QString getEtat() const { return m_etat; }
    QString getLocalisation() const { return m_localisation; }
    QString getDisponibilite() const { return m_disponibilite; }
};
#endif // MATERIEL_H
