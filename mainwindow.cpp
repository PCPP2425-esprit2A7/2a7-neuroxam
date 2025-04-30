#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "formation.h"
#include "dialogid.h"
#include "dialogrecherche.h"
#include <QMessageBox>
#include <QPainter>
#include <QDate>
#include <QDir>
#include <QPixmap>
#include <QFileDialog>
#include <QMetaType>
#include <QHeaderView>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "chatbotia.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrlQuery>
#include "qrcodegen.hpp"
#include <QFile>
#include <QCryptographicHash>
#include <QDateTime>
#include <QPdfDocument>
#include <QPdfPageRenderer>
#include <QImage>
#include <QPdfWriter>
#include <QTextDocument>
#include <QDesktopServices>
#include <QRegularExpression>
#include <QSqlQuery>
#include <QSqlError>  // (Optionnel : pour afficher l'erreur SQL en cas d'échec)
#include "fenetresignatures.h"
#include "todolist.h"
#include "ui_dialogrecherche.h"
#include "fenetrescanbadges.h"
#include "fenetrecontrolerfid.h"
#include "historiquebadges.h"

using qrcodegen::QrCode;
using qrcodegen::QrSegment;

class DateDelegate : public QStyledItemDelegate {
public:
    DateDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    QString displayText(const QVariant &value, const QLocale &locale) const override {
        if (value.canConvert<QDateTime>()) {
            return value.toDateTime().date().toString("dd/MM/yyyy");
        } else if (value.canConvert<QDate>()) {
            return value.toDate().toString("dd/MM/yyyy");
        }
        return QStyledItemDelegate::displayText(value, locale);
    }
};



class TimeDelegate : public QStyledItemDelegate {
public:
    TimeDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    QString displayText(const QVariant &value, const QLocale &locale) const override {
        // Si c'est un QTime, on affiche au format HH:mm
        if (value.canConvert<QTime>()) {
            return value.toTime().toString("HH:mm");
        }

        // Si c'est une chaîne de type "09/04/2025 03:05", on coupe pour ne garder que l'heure
        QString str = value.toString();
        if (str.contains(" ")) {
            return str.split(" ").value(1); // Garde "03:05"
        }

        return str;
    }
};


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->showMaximized();  // ✅ Fenêtre plein écran
    this->setWindowTitle("Gestion des Formations 📚");

    // 🔹 Configuration TableView
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 🔹 Charger les formations existantes
    refreshTable();

    // 🔹 Initialisation de l'ordre de tri
    ui->comboBoxOrdre->setCurrentIndex(0);  // Croissant par défaut
    dessinerStatistiques();

    // 🔹 Gestion du tri (exemple simple basé sur DATE_FORMATION)
    connect(ui->comboBoxTri, &QComboBox::currentTextChanged, this, [=](const QString &text){
        ui->comboBoxValeur->clear();
        ui->comboBoxValeur->setEnabled(false);
        ui->comboBoxOrdre->setEnabled(text == "DATE_FORMATION");
    });

    // 🔹 Rafraîchir la table à chaque retour sur l'onglet principal
    connect(ui->tabAffichage, &QTabWidget::currentChanged, this, [=](int index) {
        if (ui->tabAffichage->widget(index)->objectName() == "tabAff") {
            refreshTable();
            dessinerStatistiques();
        }
    });

    // 🔹 Connexions pour les fonctionnalités additionnelles
    connect(ui->btnVerifier, &QPushButton::clicked, this, &MainWindow::on_btnVerifier_clicked);
    connect(ui->btnVerifier, &QPushButton::clicked, this, &MainWindow::on_btnVerifier1_clicked);
    connect(ui->btnViderBase, &QPushButton::clicked, this, &MainWindow::viderBaseFormations);
    connect(ui->btnOngletSignatures, &QPushButton::clicked, this, &MainWindow::on_btnOngletSignatures_clicked);
    connect(ui->btnTodo, &QPushButton::clicked, this, &MainWindow::on_btnTodo_clicked);
    connect(ui->btnHistoriqueBadges, &QPushButton::clicked, this, &MainWindow::on_btnVoirHistorique_clicked);

    // 🔹 Gestion des logs Google Drive
    uploader = new GoogleUploader(this);
    QString logPath = QCoreApplication::applicationDirPath() + "/logs/logs_notifications.txt";
    if (QFile::exists(logPath)) {
        uploader->uploadWithoutAuthModule(logPath);
    } else {
        qDebug() << "⚠️ Le fichier de logs est introuvable à :" << logPath;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnAjouter_clicked()
{
    QString sujet = ui->lineEditSujet->text().trimmed();
    QDate date = ui->dateEdit->date();
    QTime heure = ui->timeEdit->time();
    int duree = ui->spinBoxDuree->value();
    QString statut = ui->comboStatut->currentText();
    QString nom_formateur = ui->lineEditFormateur->text().trimmed();  // Remplacement
    QString nom_centre = ui->lineEditCentre->text().trimmed();
    int nbreInvites = ui->spinBoxNbreInvites->value();
    QString codes_rfid = "";

    QStringList erreurs;
    if (sujet.isEmpty() || sujet.length() < 3) erreurs << "🔹 Le *Sujet* doit contenir au moins 3 caractères.";
    if (date < QDate::currentDate()) erreurs << "🔹 La *date* ne peut pas être dans le passé.";
    if (!heure.isValid()) erreurs << "🔹 L'heure saisie est invalide.";
    if (duree <= 0) erreurs << "🔹 La *durée* doit être supérieure à zéro.";
    if (nom_formateur.isEmpty()) erreurs << "🔹 Le *Nom du formateur* est requis.";
    if (nom_centre.isEmpty()) erreurs << "🔹 Le *Nom du centre* est requis.";
    if (nbreInvites <= 0) erreurs << "🔹 Le *nombre d'invités* doit être supérieur à zéro.";

    if (!erreurs.isEmpty()) {
        QMessageBox::warning(this, "Champs invalides", erreurs.join("\n"));
        return;
    }

    Formation f(sujet, date, heure, duree, statut, nom_formateur, nom_centre, nbreInvites, codes_rfid);
    if (f.ajouter()) {
        QMessageBox::information(this, "Succès", "📨 Formation ajoutée avec succès.");
        refreshTable(); dessinerStatistiques(); ui->tabAffichage->setCurrentWidget(ui->tabAff);
        envoyerSMS_Twilio(sujet, date, heure, statut, "✅ Ajout");
        envoyerNotifDiscord(sujet, date, "✅ Formation ajoutée");
        uploader->uploadWithoutAuthModule("logs/logs_notifications.txt");
        int idNouvelleFormation = obtenirDernierIDFormation();
        FenetreScanBadges *fenetre = new FenetreScanBadges(idNouvelleFormation, this);
        fenetre->exec();
    } else {
        QMessageBox::critical(this, "Erreur", "❌ Échec de l'ajout.");
    }
    refreshTable();
}

void MainWindow::on_btnCharger_clicked()
{
    DialogID dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        int id = dialog.getID();
        Formation f;
        if (!f.existe(id)) {
            QMessageBox::warning(this, "Erreur", "Formation non trouvée.");
            return;
        }
        Formation data = f.getById(id);
        ui->spinBoxID->setValue(id);
        ui->lineEditSujet->setText(data.getSujet());
        ui->dateEdit->setDate(data.getDate());
        ui->timeEdit->setTime(data.getHeure());
        ui->spinBoxDuree->setValue(data.getDuree());
        ui->comboStatut->setCurrentText(data.getStatut());
        ui->lineEditFormateur->setText(data.getNomFormateur());  // Changement
        ui->lineEditCentre->setText(data.getNomCentre());
        ui->spinBoxNbreInvites->setValue(data.getNbreInvites());
    }
}

void MainWindow::on_btnModifier_clicked()
{
    int id = ui->spinBoxID->value();
    Formation f;
    if (!f.existe(id)) {
        QMessageBox::warning(this, "Erreur", "Formation non trouvée.");
        return;
    }

    QString sujet = ui->lineEditSujet->text().trimmed();
    QDate date = ui->dateEdit->date();
    QTime heure = ui->timeEdit->time();
    int duree = ui->spinBoxDuree->value();
    QString statut = ui->comboStatut->currentText();
    QString nom_formateur = ui->lineEditFormateur->text().trimmed();  // Changement
    QString nom_centre = ui->lineEditCentre->text().trimmed();
    int nbreInvites = ui->spinBoxNbreInvites->value();
    QString codes_rfid = "";

    Formation update(id, sujet, date, heure, duree, statut, nom_formateur, nom_centre, nbreInvites, codes_rfid);
    if (update.modifier(id)) {
        QMessageBox::information(this, "Succès", "Formation modifiée.");
        refreshTable(); dessinerStatistiques();
        envoyerSMS_Twilio(sujet, date, heure, statut, "✏️ Modification");
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification.");
    }
}

void MainWindow::on_btnSupprimer_clicked()
{
    DialogID dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        int id = dialog.getID();
        Formation f;
        if (!f.existe(id)) {
            QMessageBox::warning(this, "Erreur", "Formation non trouvée.");
            return;
        }

        Formation formationASupprimer = f.getById(id);
        if (f.supprimer(id)) {
            QMessageBox::information(this, "Succès", "Formation supprimée.");
            refreshTable();
            envoyerSMS_Twilio(formationASupprimer.getSujet(),
                              formationASupprimer.getDate(),
                              formationASupprimer.getHeure(),
                              formationASupprimer.getStatut(),
                              "🗑️ Suppression");
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de la suppression.");
        }
        dessinerStatistiques();
    }
}

void MainWindow::dessinerStatistiques()
{
    // 📐 Image plus grande pour éviter le débordement
    int largeur = 1000;
    int hauteur = 800;
    QPixmap pixmap(largeur, hauteur);
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);

    // 🎯 Centrer le camembert
    QRect rect((largeur - 300) / 2, 50, 300, 300);

    // 📊 Données
    int nbPrevue = Formation().compterParStatut("Prévue");
    int nbEncours = Formation().compterParStatut("En cours");
    int nbTerminee = Formation().compterParStatut("Terminée");
    int total = nbPrevue + nbEncours + nbTerminee;
    if (total == 0) return;

    // 🎂 Calcul des angles
    int anglePrevue = static_cast<int>(360.0 * nbPrevue / total);
    int angleEncours = static_cast<int>(360.0 * nbEncours / total);
    int angleTerminee = 360 - anglePrevue - angleEncours;

    // 🍰 Dessin des parts
    int startAngle = 0;
    painter.setBrush(Qt::blue);
    painter.drawPie(rect, startAngle * 16, anglePrevue * 16);
    startAngle += anglePrevue;

    painter.setBrush(Qt::green);
    painter.drawPie(rect, startAngle * 16, angleEncours * 16);
    startAngle += angleEncours;

    painter.setBrush(Qt::red);
    painter.drawPie(rect, startAngle * 16, angleTerminee * 16);

    // 🧾 Légende plus bas, plus grande, plus lisible
    QFont font = painter.font();
    font.setPointSize(14);  // ✅ Plus lisible
    painter.setFont(font);

    painter.setPen(Qt::blue);
    painter.drawText(50, 400, QString("🔵 Prévue : %1").arg(nbPrevue));

    painter.setPen(Qt::green);
    painter.drawText(50, 440, QString("🟢 En cours : %1").arg(nbEncours));

    painter.setPen(Qt::red);
    painter.drawText(50, 480, QString("🔴 Terminée : %1").arg(nbTerminee));

    // 🔁 Met à jour la scène avec une taille plus grande
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addPixmap(pixmap);
    ui->graphicsViewStats->setScene(scene);
    ui->graphicsViewStats->setSceneRect(pixmap.rect());  // ✅ Permet scroll horizontal/vertical si besoin
}

void MainWindow::on_btnOuvrirChatbotIA_clicked()
{
    if (!chatbot) {
        chatbot = new ChatbotIA(this);
    }
    chatbot->show();
}

void MainWindow::envoyerSMS_Twilio(const QString &message)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QUrl url("https://textbelt.com/text");

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["phone"] = "+21620924006";  // Ton numéro
    json["message"] = message;
    json["key"] = "textbelt"; // ou ta clé API si personnalisée

    QJsonDocument doc(json);
    QByteArray data = doc.toJson();

    QNetworkReply *reply = manager->post(request, data);

    connect(reply, &QNetworkReply::finished, this, [reply]() {
        QByteArray response = reply->readAll();
        qDebug() << "Réponse : " << response;

        if (reply->error() == QNetworkReply::NoError)
            QMessageBox::information(nullptr, "SMS", "✅ SMS envoyé !");
        else
            QMessageBox::critical(nullptr, "Erreur SMS", "❌ " + reply->errorString());

        reply->deleteLater();
    });
}

void MainWindow::envoyerSMS_Twilio(const QString &sujet, const QDate &date, const QTime &heure, const QString &statut, const QString &operation)
{
    // ⚠️ Vérifie si l'envoi SMS est activé
    if (ui->checkBoxSMS && !ui->checkBoxSMS->isChecked()) {
        qDebug() << "[SMS] Envoi désactivé par l'utilisateur.";
        return;
    }

    // 🔧 Préparation de la requête HTTP
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QUrl url("https://api.twilio.com/2010-04-01/Accounts/AC8cd66192bee7ebeb9ff05e23722070da/Messages.json");
    QNetworkRequest request(url);

    // 🔐 Authentification (Base64)
    QString accountSid = "AC8cd66192bee7ebeb9ff05e23722070da";
    QString authToken  = "85c1fa7f304de434f675be6d1085e026";
    QString credentials = accountSid + ":" + authToken;
    QByteArray encodedAuth = credentials.toUtf8().toBase64();
    request.setRawHeader("Authorization", "Basic " + encodedAuth);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    // 📤 Construction du message
    QUrlQuery query;
    query.addQueryItem("From", "+16813256152"); // Numéro Twilio
    query.addQueryItem("To", "+21620924006");   // Numéro du destinataire
    query.addQueryItem("Body",
                       operation + " Formation :\n"
                                   "📘 Sujet: " + sujet +
                           "\n📅 Date: " + date.toString("dd/MM/yyyy") +
                           "\n🕒 Heure: " + heure.toString("HH:mm") +
                           "\n📌 Statut: " + statut
                       );

    // 📡 Envoi POST
    QNetworkReply *reply = manager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    // 🎯 Traitement de la réponse
    connect(reply, &QNetworkReply::finished, this, [reply]() {
        QByteArray response = reply->readAll();
        qDebug() << "[SMS] Réponse Twilio :" << response;

        if (reply->error() == QNetworkReply::NoError) {
            QMessageBox::information(nullptr, "SMS", "✅ SMS envoyé avec succès !");
        } else {
            QMessageBox::critical(nullptr, "Erreur SMS", "❌ Erreur : " + reply->errorString());
        }

        reply->deleteLater();
    });
}


void MainWindow::on_btnVerifier_clicked()  // bouton "🔁 certif"
{
    QString fileName = QFileDialog::getOpenFileName(this, "Choisir un PDF à signer", "", "PDF Files (*.pdf)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir le PDF.");
        return;
    }

    QByteArray content = file.readAll();
    file.close();

    QByteArray hash = QCryptographicHash::hash(content, QCryptographicHash::Sha256).toHex();
    QString signatureHex = QString(hash);
    QString dateStr = QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm:ss");
    QString fileNameOnly = QFileInfo(fileName).fileName();

    QString outputFile = QFileInfo(fileName).absolutePath() + "/signed_" + fileNameOnly;
    QPdfWriter writer(outputFile);
    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setResolution(300);

    QPainter painter(&writer);
    QString responsable = "Khalil Khouaja – Directeur\nGestion de Formation";
    QString signatureText = QString(
                                "Fichier signé : %1\nDate : %2\nResponsable : %3\nCode :\n%4")
                                .arg(fileNameOnly)
                                .arg(dateStr)
                                .arg(responsable)
                                .arg(signatureHex);

    painter.setPen(Qt::red);
    painter.setFont(QFont("Arial", 10, QFont::Bold));
    painter.drawText(QRect(50, 50, writer.width() - 100, 400), Qt::AlignLeft | Qt::TextWordWrap, signatureText);
    painter.end();

    // 🔒 Enregistrement dans la base de données Oracle
    QSqlQuery query;
    query.prepare("INSERT INTO PDF_SIGNATURES (NOM_FICHIER, HASH_SHA256, DATE_SIGNATURE) "
                  "VALUES (:nom, :hash, TO_DATE(:date_signature, 'DD/MM/YYYY HH24:MI:SS'))");

    query.bindValue(":nom", fileNameOnly);
    query.bindValue(":hash", signatureHex);
    query.bindValue(":date_signature", QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm:ss"));

    if (!query.exec()) {
        qDebug() << "❌ Erreur d'insertion dans PDF_SIGNATURES:" << query.lastError().text();
    } else {
        qDebug() << "✅ Signature insérée dans la base de données.";
    }

    QMessageBox::information(this, "Succès", "PDF signé et code enregistré dans la base !");
    QDesktopServices::openUrl(QUrl::fromLocalFile(outputFile));
}

void MainWindow::on_btnVerifier1_clicked()  // Vérification par recalcul réel du hash
{
    QString fileName = QFileDialog::getOpenFileName(this, "Choisir un PDF à vérifier", "", "PDF Files (*.pdf)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir le fichier.");
        return;
    }

    QByteArray content = file.readAll();  // 🔹 Lit tout le contenu binaire
    file.close();

    QByteArray hash = QCryptographicHash::hash(content, QCryptographicHash::Sha256).toHex();  // 🔐 SHA256
    QString signatureHex = QString(hash);

    // 🔍 Requête SQL pour vérifier si ce hash existe
    QSqlQuery query;
    query.prepare("SELECT NOM_FICHIER, DATE_SIGNATURE FROM PDF_SIGNATURES WHERE HASH_SHA256 = :hash");
    query.bindValue(":hash", signatureHex);

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "❌ Erreur SQL : " + query.lastError().text());
        return;
    }

    if (query.next()) {
        QString nomFichier = query.value(0).toString();
        QString date = query.value(1).toString();
        QMessageBox::information(this, "Vérification réussie",
                                 QString("✅ Ce fichier est signé.\n\nNom : %1\nDate : %2\nHash :\n%3")
                                     .arg(nomFichier)
                                     .arg(date)
                                     .arg(signatureHex));
    } else {
        QMessageBox::critical(this, "Fichier inconnu",
                              "❌ Ce fichier n’a pas été signé ou n’est pas reconnu.\n\nHash :\n" + signatureHex);
    }
}

void MainWindow::viderBaseFormations()
{
    QSqlQuery query;
    if (query.exec("DELETE FROM FORMATION")) {
        QMessageBox::information(this, "Nettoyage", "✅ Toutes les formations ont été supprimées !");
        refreshTable();  // Recharge la tableView
    } else {
        QMessageBox::critical(this, "Erreur", "❌ Échec lors de la suppression : " + query.lastError().text());
    }
}
void MainWindow::envoyerNotifDiscord(const QString &sujet, const QDate &date, const QString &action)
{
    // 🔗 Webhook Discord
    QUrl url("https://discord.com/api/webhooks/1363238138021150740/oDnAD9uYAhLcd66kqEJNmkxcxRNBHEZlvxZlZaNIguzHdBvccBH2KQhGtiq3PGkNoTvq");

    // 📦 Préparer la requête HTTP POST
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // 🧠 Créer le message Discord en JSON
    QJsonObject json;
    json["content"] = QString(
                          "**📢 Notification Formation**\n"
                          "**📘 Sujet :** %1\n"
                          "**📅 Date :** %2\n"
                          "**🔔 Action :** %3")
                          .arg(sujet)
                          .arg(date.toString("dd/MM/yyyy"))
                          .arg(action);

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkReply *reply = manager->post(request, QJsonDocument(json).toJson());

    connect(reply, &QNetworkReply::finished, this, [=]() {
        QByteArray response = reply->readAll();
        qDebug() << "[Discord Notif] Réponse : " << response;
        reply->deleteLater();
    });

    // 📁 🔐 Enregistrement local dans dossier ./logs/
    QDir logDir(QCoreApplication::applicationDirPath() + "/logs");
    if (!logDir.exists()) {
        logDir.mkpath(".");  // Crée le dossier logs s’il n’existe pas
    }

    QString logFilePath = logDir.filePath("logs_notifications.txt");

    QString logLine = QString("[%1] %2 | Sujet: %3 | Date: %4")
                          .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"))
                          .arg(action)
                          .arg(sujet)
                          .arg(date.toString("dd/MM/yyyy"));

    QFile logFile(logFilePath);
    if (logFile.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&logFile);
        out << logLine << "\n";
        logFile.close();
    } else {
        qDebug() << "❌ Impossible d'ouvrir le fichier de logs.";
    }
}
void MainWindow::on_btnOngletSignatures_clicked()
{
    if (!fenetreSignatures) {
        fenetreSignatures = new FenetreSignatures(this);
    } else {
        fenetreSignatures->actualiserTable();  // ✅ Refresh si elle existe déjà
    }

    fenetreSignatures->show();
    fenetreSignatures->raise();
    fenetreSignatures->activateWindow();
}


void MainWindow::on_btnTodo_clicked()
{
    qDebug() << "🟢 Ouverture fenêtre TodoList";

    if (!todoList) {
        todoList = new TodoList(this);
        todoList->setAttribute(Qt::WA_DeleteOnClose, false);

        connect(todoList, &QObject::destroyed, this, [=]() {
            todoList = nullptr;
        });
    }

    todoList->move(300, 200); // ✅ Position visible garantie
    todoList->show();
    todoList->raise();
    todoList->activateWindow();
}

int MainWindow::obtenirDernierIDFormation() {
    QSqlQuery query;
    query.prepare("SELECT MAX(ID_FORMATION) FROM FORMATION");
    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}


// 🔄 Rafraîchir la table avec les données actuelles
void MainWindow::refreshTable() {
    Formation f;
    QSqlQueryModel *model = f.afficher();
    ui->tableView->setModel(model);

    // 🔥 RÉAPPLIQUER les Delegates après chaque setModel()
    ui->tableView->setItemDelegateForColumn(2, new DateDelegate(this));  // Date
    ui->tableView->setItemDelegateForColumn(3, new TimeDelegate(this));  // Heure

    int total = model->rowCount();
    ui->labelCompteur->setText("Nombre de formations : " + QString::number(total));
    dessinerStatistiques();
}

// 🔍 Rechercher bouton
void MainWindow::on_btnRechercher_clicked() {
    DialogRecherche dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString sujet = dialog.getSujetSelectionne();  // méthode à ajouter si tu veux récupérer un sujet choisi
        Formation f;
        QSqlQueryModel *model = f.rechercherMulticritere(sujet);
        if (model) {
            ui->tableView->setModel(model);
        }
    }
}

// 🔃 Trier bouton
void MainWindow::on_btnTrier_clicked() {
    QString critere = ui->comboBoxTri->currentText();
    QString ordre = ui->comboBoxOrdre->currentText();
    Formation f;

    if (critere == "DATE_FORMATION") {
        QString ordre_sql = (ordre == "Croissant") ? "ASC" : "DESC";
        ui->tableView->setModel(f.trierPar("DATE_FORMATION", ordre_sql));
    } else {
        refreshTable();
    }
}

// 📂 Afficher tout bouton
void MainWindow::on_btnAfficherTout_clicked() {
    refreshTable();
    dessinerStatistiques();
}

// 🧾 Générer PDF bouton
void MainWindow::on_btnGenererPDF_clicked()
{
    QString defaultName = "Liste_Formations_" + QDate::currentDate().toString("dd-MM-yyyy") + ".pdf";
    QString filename = QFileDialog::getSaveFileName(this, "Enregistrer le PDF", QDir::homePath() + "/" + defaultName, "Fichiers PDF (*.pdf)");
    if (filename.isEmpty()) return;

    QPdfWriter pdf(filename);
    pdf.setPageSize(QPageSize::A4);
    pdf.setResolution(300);

    QPainter painter(&pdf);

    // === 1. Logo centré ===
    QPixmap logo(":/resources/logo.png");
    int logoWidth = 220;
    int logoHeight = 80;
    painter.drawPixmap((pdf.width() - logoWidth) / 2, 20, logoWidth, logoHeight, logo);

    // === 2. Titre principal ===
    painter.setFont(QFont("Arial", 20, QFont::Bold));
    painter.setPen(Qt::black);
    painter.drawText(QRect(0, logoHeight + 30, pdf.width(), 50), Qt::AlignCenter, "📋 Liste des Formations");

    // === 3. Récupérer le modèle de la table ===
    QAbstractItemModel *model = ui->tableView->model();
    if (!model) return;

    int cols = model->columnCount();
    int rows = model->rowCount();

    QFont headerFont("Arial", 11, QFont::Bold);
    QFont cellFont("Arial", 10);
    QFontMetrics headerFM(headerFont);
    QFontMetrics cellFM(cellFont);

    painter.setFont(cellFont);
    QVector<int> colWidths(cols, 0);

    for (int col = 0; col < cols; ++col) {
        int max = headerFM.horizontalAdvance(model->headerData(col, Qt::Horizontal).toString()) + 30;
        for (int row = 0; row < rows; ++row) {
            QString data = model->data(model->index(row, col)).toString();
            max = std::max(max, cellFM.horizontalAdvance(data) + 30);
        }
        colWidths[col] = max;
    }

    // === 4. Ajuster largeur des colonnes à la page
    int margin = 50;
    int availableWidth = pdf.width() - 2 * margin;
    int totalWidth = std::accumulate(colWidths.begin(), colWidths.end(), 0);
    double scaleW = double(availableWidth) / totalWidth;
    for (int &w : colWidths) w = int(w * scaleW);

    // === 5. Ajuster hauteur des lignes selon place dispo
    int top = logoHeight + 100;
    int bottomSpace = 200;  // espace QR
    int availableHeight = pdf.height() - top - bottomSpace;
    int rowHeight = availableHeight / (rows + 1);  // +1 pour l'en-tête

    int startX = margin;
    int startY = top;

    // === 6. En-tête
    painter.setFont(headerFont);
    painter.setPen(Qt::white);
    painter.setBrush(QColor("#444444"));
    int x = startX;
    for (int col = 0; col < cols; ++col) {
        QRect rect(x, startY, colWidths[col], rowHeight);
        painter.fillRect(rect, QColor("#444444"));
        painter.drawRect(rect);
        painter.drawText(rect, Qt::AlignCenter, model->headerData(col, Qt::Horizontal).toString());
        x += colWidths[col];
    }

    // === 7. Lignes de données
    painter.setFont(cellFont);
    painter.setPen(Qt::black);
    startY += rowHeight;

    for (int row = 0; row < rows; ++row) {
        int x = startX;
        for (int col = 0; col < cols; ++col) {
            QRect rect(x, startY, colWidths[col], rowHeight);
            painter.drawRect(rect);

            QString data = model->data(model->index(row, col)).toString();
            if (col == 2 && data.contains("T")) data = QDate::fromString(data.left(10), "yyyy-MM-dd").toString("dd/MM/yyyy");
            if (col == 3 && data.contains("T")) data = QTime::fromString(data.mid(11, 5), "HH:mm").toString("HH:mm");

            painter.drawText(rect, Qt::AlignCenter | Qt::TextWordWrap, data);
            x += colWidths[col];
        }
        startY += rowHeight;
    }

    // === 8. Générer QR Code
    QString texteQR = QString("Responsable : Direction Formation\nDate : %1 à %2")
                          .arg(QDate::currentDate().toString("dd/MM/yyyy"))
                          .arg(QTime::currentTime().toString("HH:mm"));
    std::string utf8 = texteQR.toUtf8().constData();
    QrCode qr = QrCode::encodeText(utf8.c_str(), QrCode::Ecc::MEDIUM);

    const int size = qr.getSize();
    const int scaleQR = 5;
    QImage qrImage(size * scaleQR, size * scaleQR, QImage::Format_RGB32);
    qrImage.fill(Qt::white);
    QPainter qrPainter(&qrImage);
    qrPainter.setBrush(Qt::black);
    qrPainter.setPen(Qt::NoPen);
    for (int y = 0; y < size; ++y)
        for (int x = 0; x < size; ++x)
            if (qr.getModule(x, y))
                qrPainter.drawRect(x * scaleQR, y * scaleQR, scaleQR, scaleQR);
    qrPainter.end();

    // === 9. Ajouter QR Code + signature
    int qrX = margin;
    int qrY = pdf.height() - qrImage.height() - 60;
    painter.drawImage(qrX, qrY, qrImage);

    painter.setFont(QFont("Arial", 10, QFont::Bold));
    painter.drawText(qrX + qrImage.width() + 20, qrY + qrImage.height()/2,
                     "Responsable : Responsable Direction de Formation");

    painter.end();
    QMessageBox::information(this, "✅ Succès", "PDF généré avec succès !");
}


void MainWindow::on_btnScanRFID_clicked()
{
    FenetreControleRFID *fenetreControle = new FenetreControleRFID(this);
    fenetreControle->exec();  // Affiche la fenêtre modale
}
void MainWindow::on_btnVoirHistorique_clicked()
{
    HistoriqueBadges historique(this);
    historique.exec();
}
