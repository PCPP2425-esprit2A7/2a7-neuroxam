#ifndef FENETRESCANBADGES_H
#define FENETRESCANBADGES_H

#include <QDialog>
#include <QSerialPort>
#include <QCloseEvent>

namespace Ui {
class FenetreScanBadges;
}

class FenetreScanBadges : public QDialog
{
    Q_OBJECT

public:
    explicit FenetreScanBadges(int idFormation, QWidget *parent = nullptr);
    ~FenetreScanBadges();

signals:
    void badgesMisAJour();  // 🔄 Signal pour notifier la mise à jour des badges RFID

private slots:
    void lireBadge();                   // 🔍 Lire les données du port série et détecter les UID
    void enregistrerBadge(QString uid); // ✅ Ajouter un badge à la formation + insérer dans BADGE_ENTREES

protected:
    void closeEvent(QCloseEvent *event) override;  // 🔌 Fermer le port série à la fermeture

private:
    void initialiserPortSerie();   // 🔌 Configurer et ouvrir le port série
    void mettreAJourBase();        // 💾 Mettre à jour la colonne CODES_RFID de la formation
    void chargerBadgesExistants(); // 📋 Charger les badges déjà enregistrés pour cette formation
    void fermerPortSerie();        // 🔌 Fermer proprement le port série si ouvert

    Ui::FenetreScanBadges *ui;     // Interface utilisateur
    QSerialPort *serialPort;       // Gestion du port série Arduino
    int idFormation;               // ID de la formation concernée
    QStringList listeBadges;       // Liste des badges ajoutés
    QString dernierUID;            // Pour éviter les scans doublons immédiats
    bool attenteLecture;           // Gère les délais de lecture UID
    QString buffer;                // 🔹 Pour accumuler les données fragmentées du port série
};

#endif // FENETRESCANBADGES_H
