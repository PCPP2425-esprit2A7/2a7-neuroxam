#ifndef ETUDIANTSERVICE_H
#define ETUDIANTSERVICE_H

#include <QString>
#include <QDate>
#include <QSqlRecord>
#include <QList>
#include <QMap>
#include "etudiant.h"

class EtudiantService
{
public:
    EtudiantService();
    
    // CRUD operations
    bool add(const Etudiant &etudiant);
    bool add(const QString &name, const QString &familyName, const QString &cin, 
             const QString &speciality, double note, const QString &gender,
             const QString &phone, const QString &email, const QString &birthDate,
             const QString &photoPath);
             
    bool update(const Etudiant &etudiant);
    bool update(int id, const QString &name, const QString &familyName, const QString &cin, 
                const QString &speciality, double note, const QString &gender,
                const QString &phone, const QString &email, const QString &birthDate,
                const QString &photoPath);
                
    bool remove(int id);
    
    Etudiant getById(int id);
    QList<Etudiant> getAll();
    QList<Etudiant> getSortedBy(const QString &column);
    QList<Etudiant> searchByCriteria(const QString &criteria, const QString &value);
    
    // Image handling
    bool saveImage(const QString &sourcePath, QString &destinationPath);
    
    // Statistics functions
    int getTotalCount();
    int getCountByGender(const QString &gender);
    double getAverageNote();
    QMap<QString, int> getStatsBySpeciality();
    QMap<QString, double> getAverageNoteBySpeciality();
    
    // PDF generation
    bool generatePDF(const QString &filename, const QList<Etudiant> &students);
    bool generateStudentPDF(const QString &filename, const Etudiant &student);
    
private:
    int getNextId();
    bool createTableIfNotExists();
};

#endif // ETUDIANTSERVICE_H
