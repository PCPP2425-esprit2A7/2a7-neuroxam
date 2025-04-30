#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QTime>

// 📂 Inclusions des autres classes
#include "chatbotia.h"
#include "googleuploader.h"
#include "fenetresignatures.h"
#include "todolist.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // 🟢 Gestion CRUD
    void on_btnAjouter_clicked();
    void on_btnCharger_clicked();
    void on_btnModifier_clicked();
    void on_btnSupprimer_clicked();
    void on_btnRechercher_clicked();
    void on_btnTrier_clicked();
    void on_btnAfficherTout_clicked();

    // 🟢 PDF et Statistiques
    void on_btnGenererPDF_clicked();
    void dessinerStatistiques();

    // 🟢 Chatbot IA
    void on_btnOuvrirChatbotIA_clicked();

    // 🟢 Gestion des Signatures PDF
    void on_btnVerifier_clicked();
    void on_btnVerifier1_clicked();
    void on_btnOngletSignatures_clicked();

    // 🟢 To-Do List
    void on_btnTodo_clicked();

    // 🟢 RFID - Scan
    void on_btnScanRFID_clicked();

    // 🟢 Utilitaires internes
    void viderBaseFormations();
    void refreshTable();

    // 🟢 Notifications
    void envoyerNotifDiscord(const QString &sujet, const QDate &date, const QString &action);

    // 🟢 SMS Twilio
    void envoyerSMS_Twilio(const QString &message);
    void envoyerSMS_Twilio(const QString &sujet, const QDate &date, const QTime &heure, const QString &statut, const QString &operation);
    void on_btnVoirHistorique_clicked();

    // 🟢 Récupération ID Formation
    int obtenirDernierIDFormation();

private:
    Ui::MainWindow *ui;

    // 🟢 Pointeurs vers autres classes
    ChatbotIA *chatbot = nullptr;
    GoogleUploader *uploader = nullptr;
    FenetreSignatures *fenetreSignatures = nullptr;
    TodoList *todoList = nullptr;
};

#endif // MAINWINDOW_H
