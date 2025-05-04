#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"centre.h"
#include"recommendation.h"
#include <QMainWindow>
#include <QtQuickWidgets/QQuickWidget>
#include <QGeoCoordinate>
#include<QVBoxLayout>
#include "examen.h"
#include"employe.h"
#include <QTime>

#include <QDate>
#include "chatbotia.h"
#include "fenetresignatures.h"
#include "fenetrescanbadges.h"
#include "todolist.h"
#include "fenetrestatsf.h"
#include "deplome.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
//centre
    void on_modifier_3_clicked();
    void on_sup_3_clicked();
    void on_recuperer_clicked();
    void on_tri_3_clicked();
    void on_cherchebut_clicked();
    void on_pdf_clicked();
    void verifierNom();
    void verifierads();
    void verifierdtc();
    void on_ajoute_3_clicked();
    void on_stat_clicked();
    void onMapClicked(double latitude, double longitude);
    void on_next_clicked();
    void on_back_clicked();
    void onChatSendClicked();
    void displayRecommendations(const QVector<centre>& recommendations);
    void on_chat_clicked();
    void onExitChatClicked();
    void on_ard_clicked();




//slidebar
    void on_pushButton_2_clicked();
    void on_mexam_clicked();
    void on_emp_clicked();
    void on_etud_clicked();
    void on_materl_clicked();
    void on_formation_clicked();





//exam
    void on_ajoute_4_clicked();
    void on_modifier_4_clicked();
    void on_sup_4_clicked();
    void on_tri_4_clicked();
    void on_cherchebut_3_clicked();
    void on_pdf_3_clicked();
    void on_stat_3_clicked();
    void on_btn_ouvrirEmailDialog_clicked();
    void mettreAJourCalendrier();
    void on_calendar_examen_2_clicked(const QDate &date);
    void on_recuperer_3_clicked();


//emp
    void on_ajoute_clicked();
    void on_modifier_clicked();
    void on_supprimer_clicked();
    void on_recuperer_5_clicked();
    void on_tri_clicked();
    void on_cherchebut_5_clicked();
    void on_pdf_5_clicked();
    void verifierNomp();
    void verifierNumeroTelephone();
    void on_stat_5_clicked();





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
    void viderBaseFormations();
    void refreshTable();
    void envoyerNotifDiscord(const QString &sujet, const QDate &date, const QString &action);
    void envoyerSMS_Twilio(const QString &message);
    void envoyerSMS_Twilio(const QString &sujet, const QDate &date, const QTime &heure, const QString &statut, const QString &operation);
    void on_btnVoirHistorique_clicked();
    int obtenirDernierIDFormation();
    void on_chercher_textChanged(const QString &text);
     void on_btnStat_clicked();
     void      on_btnCharger_clicked();
void  on_btnCertificat_clicked ();
     void dessinerStatistiques();

private:
    Ui::MainWindow *ui;
    centre c;
    QQuickWidget *mapWidget;
    void setupMap();
    void loadCentresToMap();
    RecommendationSystem *recommender;
    void setupChatUI();
    QVBoxLayout *chatLayout = nullptr;
    examen e;
    employe ep;
    ChatbotIA *chatbot = nullptr;
    FenetreSignatures *fenetreSignatures = nullptr;
    FenetreScanBadges *fenetre = nullptr;
    TodoList *todoList = nullptr;
    FenetreStatsF *fenetreStats = nullptr;
    int idFormationCourante = -1;  // ✅ Correctement stocké comme variable de membre

};
#endif // MAINWINDOW_H
