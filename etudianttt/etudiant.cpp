#include "etudiant.h"

Etudiant::Etudiant() {}

Etudiant::Etudiant(int id, const QString &name, const QString &familyName, const QString &cin,
                   const QString &speciality, float note, const QString &photoPath,
                   const QString &phoneNumber, const QString &email,
                   const QDate &birthDate, const QString &gender)
    : id(id), name(name), familyName(familyName), cin(cin), 
      speciality(speciality), note(note), photoPath(photoPath),
      phoneNumber(phoneNumber), email(email), birthDate(birthDate), gender(gender) {}

Etudiant::Etudiant(const QString &name, const QString &familyName, const QString &cin,
                   const QString &speciality, float note, const QString &photoPath,
                   const QString &phoneNumber, const QString &email,
                   const QDate &birthDate, const QString &gender)
    : id(-1), name(name), familyName(familyName), cin(cin), 
      speciality(speciality), note(note), photoPath(photoPath),
      phoneNumber(phoneNumber), email(email), birthDate(birthDate), gender(gender) {}

int Etudiant::getId() const { return id; }
QString Etudiant::getName() const { return name; }
QString Etudiant::getFamilyName() const { return familyName; }
QString Etudiant::getCin() const { return cin; }
QString Etudiant::getSpeciality() const { return speciality; }
float Etudiant::getNote() const { return note; }
QString Etudiant::getPhotoPath() const { return photoPath; }
QString Etudiant::getPhoneNumber() const { return phoneNumber; }
QString Etudiant::getEmail() const { return email; }
QDate Etudiant::getBirthDate() const { return birthDate; }
QString Etudiant::getGender() const { return gender; }

void Etudiant::setId(int id) { this->id = id; }
void Etudiant::setName(const QString &name) { this->name = name; }
void Etudiant::setFamilyName(const QString &familyName) { this->familyName = familyName; }
void Etudiant::setCin(const QString &cin) { this->cin = cin; }
void Etudiant::setSpeciality(const QString &speciality) { this->speciality = speciality; }
void Etudiant::setNote(float note) { this->note = note; }
void Etudiant::setPhotoPath(const QString &photoPath) { this->photoPath = photoPath; }
void Etudiant::setPhoneNumber(const QString &phoneNumber) { this->phoneNumber = phoneNumber; }
void Etudiant::setEmail(const QString &email) { this->email = email; }
void Etudiant::setBirthDate(const QDate &birthDate) { this->birthDate = birthDate; }
void Etudiant::setGender(const QString &gender) { this->gender = gender; }
