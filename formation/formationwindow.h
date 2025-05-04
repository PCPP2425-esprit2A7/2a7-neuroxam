#ifndef FORMATION_H
#define FORMATION_H

#include <QWidget>
#include <QtQuickWidgets/QQuickWidget>
#include<QVBoxLayout>
#include <QTime>

#include <QDate>
#include "chatbotia.h"
#include "fenetresignatures.h"
#include "fenetrescanbadges.h"
#include "todolist.h"
#include "fenetrestatsf.h"
#include "deplome.h"


namespace Ui {
class formationwindow;
}

class formationwindow : public QWidget
{
    Q_OBJECT

public:
    formationwindow(QWidget *parent = nullptr);
    ~formationwindow();

private slots:
//form

    void on_btnAjouter_clicked();
    void on_btnModifier_clicked();
    void on_btnSupprimer_clicked();
    void on_btnRechercher_clicked();
    void on_btnTrier_clicked();
    void on_btnAfficherTout_clicked();
    void on_btnGenererPDF_clicked();
    void on_btnOuvrirChatbotIA_clicked();
    void on_btnVerifier_clicked();
    void on_btnVerifier1_clicked();
    void on_btnOngletSignatures_clicked();
    void on_btnTodo_clicked();
    void on_btnScanRFID_clicked();
    void on_btnVoirHistorique_clicked();
    void on_chercher_textChanged(const QString &text);
    void on_btnStat_clicked();
    void on_btnCharger_clicked();
    void on_btnCertificat_clicked ();

    void on_btnViderBase_clicked();

private:
    Ui::formationwindow *ui;
    ChatbotIA *chatbot = nullptr;
    FenetreSignatures *fenetreSignatures = nullptr;
    FenetreScanBadges *fenetre = nullptr;
    TodoList *todoList = nullptr;
    FenetreStatsF *fenetreStats = nullptr;
    int idFormationCourante = -1;  // ✅ Correctement stocké comme variable de membre
    void dessinerStatistiques();
    void refreshTable();
    void envoyerNotifDiscord(const QString &sujet, const QDate &date, const QString &action);
    void envoyerSMS_Twilio(const QString &message);
    void envoyerSMS_Twilio(const QString &sujet, const QDate &date, const QTime &heure, const QString &statut, const QString &operation);
    void viderBaseFormations();
    int obtenirDernierIDFormation();

};
#endif // FORMATION_H
