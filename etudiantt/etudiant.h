#ifndef ETUDIANT_H
#define ETUDIANT_H

#include <QString>
#include <QDate>

class Etudiant {
public:
    Etudiant();
    Etudiant(int id, const QString &name, const QString &familyName, const QString &cin,
             const QString &speciality, float note, const QString &photoPath,
             const QString &phoneNumber, const QString &email,
             const QDate &birthDate, const QString &gender);
    
    Etudiant(const QString &name, const QString &familyName, const QString &cin,
             const QString &speciality, float note, const QString &photoPath,
             const QString &phoneNumber, const QString &email,
             const QDate &birthDate, const QString &gender);

    int getId() const;
    QString getName() const;
    QString getFamilyName() const;
    QString getCin() const;
    QString getSpeciality() const;
    float getNote() const;
    QString getPhotoPath() const;
    QString getPhoneNumber() const;
    QString getEmail() const;
    QDate getBirthDate() const;
    QString getGender() const;

    void setId(int id);
    void setName(const QString &name);
    void setFamilyName(const QString &familyName);
    void setCin(const QString &cin);
    void setSpeciality(const QString &speciality);
    void setNote(float note);
    void setPhotoPath(const QString &photoPath);
    void setPhoneNumber(const QString &phoneNumber);
    void setEmail(const QString &email);
    void setBirthDate(const QDate &birthDate);
    void setGender(const QString &gender);

private:
    int id;
    QString name;
    QString familyName;
    QString cin;
    QString speciality;
    float note;
    QString photoPath;
    QString phoneNumber;
    QString email;
    QDate birthDate;
    QString gender;
};

#endif // ETUDIANT_H
