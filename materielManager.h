#ifndef MATERIELMANAGER_H
#define MATERIELMANAGER_H

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <vector>
#include "materiel.h"

class MaterielManager
{
public:
    MaterielManager() = default;

    // crud
    bool addMateriel(const Materiel& materiel);
    bool getMateriel(int id, Materiel& materiel);
    std::vector<Materiel> getAllMateriels();
    bool updateMateriel(const Materiel& materiel);
    bool deleteMateriel(int id);

    // metiers
    bool generatePdf(const QString& filePath);
};

#endif // MATERIELMANAGER_H
