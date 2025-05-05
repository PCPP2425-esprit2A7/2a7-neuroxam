#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// === Qt Widgets / UI ===
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QDate>
#include <QTime>
#include <QPixmap>
#include <QPrinter>
#include <QPainter>
#include <QPrintDialog>
#include <QStandardItemModel>

// === Qt Quick & Cartographie ===
#include <QtQuickWidgets/QQuickWidget>
#include <QGeoCoordinate>

// === Modules Métiers ===
#include "centre.h"
#include "recommendation.h"
#include "examen.h"
#include "employe.h"
#include "chatbotia.h"
#include "materielManager.h"
#include "etudiantservice.h"

// === Fenêtres Secondaires ===
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
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    // === Centre ===
    void on_modifier_3_clicked();
    void on_sup_3_clicked();
    void on_recuperer_clicked();
    void on_tri_3_clicked();
    void on_cherchebut_clicked();
    void on_pdf_clicked();
    void on_ajoute_3_clicked();
    void on_stat_clicked();
    void onMapClicked(double latitude, double longitude);
    void on_next_clicked();
    void on_back_clicked();
    void verifierNom();
    void verifierads();
    void verifierdtc();

    // === Recommandation / Chat IA ===
    void on_chat_clicked();
    void onChatSendClicked();
    void onExitChatClicked();
    void displayRecommendations(const QVector<centre> &recommendations);  // ✅ AJOUTÉ ICI

    // === Accès Arduino ===
    void on_ard_clicked();

    // === SlideBar Navigation ===
    void on_pushButton_9_clicked();
    void on_pushButton_2_clicked();
    void on_mexam_clicked();
    void on_emp_clicked();
    void on_etud_clicked();
    void on_materl_clicked();
    void on_formation_clicked();

    // === Examens ===
    void loadCenterNames();
    void mettreAJourCalendrier();
    void on_ajoute_4_clicked();
    void on_modifier_4_clicked();
    void on_sup_4_clicked();
    void on_tri_4_clicked();
    void on_cherchebut_3_clicked();
    void on_pdf_3_clicked();
    void on_stat_3_clicked();
    void on_calendar_examen_2_clicked(const QDate &date);
    void on_recuperer_3_clicked();
    void on_btn_ouvrirEmailDialog_clicked();

    // === Employés ===
    void on_ajoute_clicked();
    void on_modifier_clicked();
    void on_supprimer_clicked();
    void on_recuperer_5_clicked();
    void on_tri_clicked();
    void on_cherchebut_5_clicked();
    void on_pdf_5_clicked();
    void on_stat_5_clicked();
    void verifierNomp();
    void verifierNumeroTelephone();

    // === Formations ===
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
    void on_btnStat_clicked();
    void on_btnCharger_clicked();
    void on_btnCertificat_clicked();

    void on_chercher_textChanged(const QString &text);
    void viderBaseFormations();
    void refreshTable();
    int obtenirDernierIDFormation();
    void envoyerNotifDiscord(const QString &sujet, const QDate &date, const QString &action);
    void envoyerSMS_Twilio(const QString &sujet, const QDate &date, const QTime &heure, const QString &statut, const QString &operation);
    void dessinerStatistiques();

    // === Matériel ===
    void on_addButton_clicked();
    void on_loadButton_clicked();
    void on_editButton_clicked();
    void on_deleteButton_clicked();
    void on_searchButton_clicked();
    void on_resetButton_clicked();
    void on_sortButton_clicked();
    void on_pdfButton_clicked();
    void on_tab1_p1_clicked();
    void on_tab2_p1_clicked();
    void on_tab1_p2_clicked();
    void on_tab2_p2_clicked();
    void on_allouerButton_clicked();
    void on_clearButton_clicked();
    void on_optimiserButton_clicked();

    // === Étudiants ===
    void loadStudents(const QString &sortBy = "");
    void onAddStudent();
    void onUpdateStudent();
    void onDeleteStudent();
    void onSortStudents(const QString &criteria);
    void onSearch();
    void onShowStats();
    void onSavePDF();
    void onSaveStudentPDF();
    void onBrowseImage();
    void onLoadStudentDetails(int studentId);
    void clearFields();
    void onOpenChatDialog();

    // === UI Masquage Panels ===
    void on_hide_clicked();
    void on_hide_3_clicked();
    void on_hide_4_clicked();
    void on_hide_5_clicked();
    void on_hide_6_clicked();
    void on_hide_7_clicked();
    void on_hide_8_clicked();
    void on_hide_9_clicked();

    void on_disconnectButton_clicked();

    void on_MainWindow_toolButtonStyleChanged(const Qt::ToolButtonStyle &toolButtonStyle);

signals:
    void disconnect();

private:
    Ui::MainWindow *ui;

    // === Composants principaux ===
    centre c;
    examen e;
    employe ep;
    RecommendationSystem *recommender;
    ChatbotIA *chatbot = nullptr;

    // === Interface & Dynamique ===
    QQuickWidget *mapWidget = nullptr;
    QVBoxLayout *chatLayout = nullptr;
    QStandardItemModel *modeld = nullptr;
    QString currentPhotoPath;
    int currentStudentId = -1;
    int idFormationCourante = -1;
    int loadedMaterielId = -1;

    // === Fenêtres secondaires ===
    FenetreSignatures *fenetreSignatures = nullptr;
    FenetreScanBadges *fenetre = nullptr;
    TodoList *todoList = nullptr;
    FenetreStatsF *fenetreStats = nullptr;
    Deplome *fenetreDeplome = nullptr;

    // === Services internes ===
    MaterielManager manager;
    EtudiantService service;

    // === Initialisation ===
    void setupMap();
    void loadCentresToMap();
    void setupChatUI();
    void setupTable();
    void setupConnections();
    void setupValidators();
    void loadCenterNamesIntoCombos();

    // === Outils statistiques / matériels ===
    void loadMaterielsIntoTable();
    void drawStatistics();
    int countEtat(const QString &etat);
    int countDisponibilite(const QString &disponibilite);
    QStringList getCenterNames() const;
};

#endif // MAINWINDOW_H
