#ifndef FENETRECONTROLERFID_H
#define FENETRECONTROLERFID_H

#include <QDialog>
#include <QSerialPort>
#include <QCloseEvent>

namespace Ui {
class FenetreControleRFID;
}

class FenetreControleRFID : public QDialog
{
    Q_OBJECT

public:
    explicit FenetreControleRFID(QWidget *parent = nullptr);
    ~FenetreControleRFID();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void lireDonneesSerie();         // 🔄 Lecture des données série
    void ouvrirManuel();             // 🔓 Ouverture manuelle
    void fermerManuel();             // 🔒 Fermeture manuelle

private:
    bool verifierUID(const QString &uid);              // ✅ Vérifier UID dans la base
    void enregistrerEntree(const QString &uid);        // 🟢 Enregistrer entrée
    void enregistrerSortie(const QString &uid);        // 🟣 Enregistrer sortie
    void lancerAlerte(const QString &message);         // 🚨 Afficher alerte

    Ui::FenetreControleRFID *ui;
    QSerialPort *serial;
    QString buffer;                 // 🧩 Données série en attente
    QString dernierUIDValide;       // 🆔 Dernier UID accepté
};

#endif // FENETRECONTROLERFID_H
