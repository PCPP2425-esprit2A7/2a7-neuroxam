#include "formationwindow.h"
#include "ui_formationwindow.h"
#include "formation.h"
#include <QMessageBox>

#include "dialogid.h"
#include "qrcodegen.hpp"
#include "chatbotia.h"
#include "fenetrecontrolerfid.h"
#include "dialogid.h"
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
// #include <QPdfDocument>
// #include <QPdfPageRenderer>
#include <QImage>
#include <QPdfWriter>
#include <QTextDocument>
#include <QDesktopServices>
#include <QRegularExpression>
#include <QSqlQuery>
#include <QSqlError>
#include "fenetrecontrolerfid.h"
#include "historiquebadges.h"


class Formation
{
private:
    int id;
    QString sujet;
    QDate date;
    QTime heure;
    int duree;
    QString statut;
    QString nom_formateur;       // 🔹 Remplace id_employe par nom_formateur
    QString nom_centre;          // 🔹 Nom du centre
    int nbre_invites;            // 🔹 Nombre d'invités
    QString codes_rfid;          // 🔹 Codes RFID

public:
    // 🔹 Constructeurs
    Formation();
    Formation(QString sujet, QDate date, QTime heure, int duree, QString statut, QString nom_formateur, QString nom_centre, int nbre_invites, QString codes_rfid = "");
    Formation(int id, QString sujet, QDate date, QTime heure, int duree, QString statut, QString nom_formateur, QString nom_centre, int nbre_invites, QString codes_rfid = "");

    // 🔹 Getters
    int getId() const;
    QString getSujet() const;
    QDate getDate() const;
    QTime getHeure() const;
    int getDuree() const;
    QString getStatut() const;
    QString getNomFormateur() const;    // 🔹 Getter pour nom_formateur
    QString getNomCentre() const;       // 🔹 Getter pour nom_centre
    int getNbreInvites() const;         // 🔹 Getter pour nbre_invites
    QString getCodesRFID() const;       // 🔹 Getter pour codes_rfid

    // 🔹 Setters
    void setCodesRFID(const QString &codes);  // 🔹 Setter pour RFID

    // 🔹 Méthodes de manipulation
    bool ajouter();
    bool modifier(int id);
    bool supprimer(int id);
    bool existe(int id);
    Formation getById(int id);
    bool supprimerTout();


    // 🔹 Affichage et requêtes
    QSqlQueryModel* afficher();
    QSqlQueryModel* afficherCombinéDateHeure();
    QSqlQueryModel* rechercherParSujet(const QString &sujet);
    QSqlQueryModel* rechercherMulticritere(const QString &input);
    QSqlQueryModel* trierPar(const QString &critere, const QString &ordre);
    QSqlQueryModel* filtrerParStatut(const QString &statut);
    int compterParStatut(const QString &statut);
    QStringList getTousLesSujets();
    QSqlQueryModel* rechercher(const QString& keyword);
};




#include "qrcodegen.hpp"
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

formationwindow::formationwindow(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::formationwindow)
{
    ui->setupUi(this);
    refreshTable();
    dessinerStatistiques();
}

formationwindow::~formationwindow()
{
    delete ui;
}


void formationwindow::on_btnAjouter_clicked()
{
    QString sujet = ui->lineEditSujet->text().trimmed();
    QDate date = ui->dateEdit->date();
    QTime heure = ui->timeEdit->time();
    int duree = ui->spinBoxDuree->value();
    QString statut = ui->comboStatut->currentText();
    QString nom_formateur = ui->lineEditFormateur->text().trimmed();
    QString nom_centre = ui->lineEditCentre->text().trimmed();
    int nbreInvites = ui->spinBoxNbreInvites->value();
    QString codes_rfid = ""; // laissé vide pour le moment

    // ✅ Validation des champs
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

    // ✅ Création et insertion dans la base
    Formation f(sujet, date, heure, duree, statut, nom_formateur, nom_centre, nbreInvites, codes_rfid);
    if (f.ajouter()) {
        QMessageBox::information(this, "Succès", "📨 Formation ajoutée avec succès.");
        refreshTable();
        dessinerStatistiques();
        ui->tabAffichage->setCurrentWidget(ui->tabAff);

        envoyerSMS_Twilio(sujet, date, heure, statut, "✅ Ajout");
        envoyerNotifDiscord(sujet, date, "✅ Formation ajoutée");

        // ✅ Génération des tâches automatiquement dans la table TACHES
        QStringList taches = {
            QString("📘 %1 — Préparer salle").arg(sujet),
            QString("📘 %1 — Envoyer convocations").arg(sujet),
            QString("📘 %1 — Imprimer documents").arg(sujet),
            QString("📘 %1 — Vérifier participants").arg(sujet),
            QString("📘 %1 — Créer QR code accès").arg(sujet)
        };

        for (const QString &tache : taches) {
            QSqlQuery check;
            check.prepare("SELECT COUNT(*) FROM TACHES WHERE TEXTE = :t");
            check.bindValue(":t", tache);
            check.exec(); check.next();
            if (check.value(0).toInt() == 0) {
                QSqlQuery ins;
                ins.prepare("INSERT INTO TACHES (TEXTE, DATE_LIMITE, TERMINE) VALUES (:t, TO_DATE(:d, 'DD/MM/YYYY'), 0)");
                ins.bindValue(":t", tache);
                ins.bindValue(":d", date.toString("dd/MM/yyyy"));
                ins.exec();
            }
        }

        // ✅ Ouvrir la fenêtre de scan RFID avec ID nouvellement inséré
        int idNouvelleFormation = obtenirDernierIDFormation();
        FenetreScanBadges *fenetre = new FenetreScanBadges(idNouvelleFormation, this);
        fenetre->exec();

    } else {
        QMessageBox::critical(this, "Erreur", "❌ Échec de l'ajout.");
    }
}



void formationwindow::on_btnCharger_clicked()
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

        // 🎯 Remplir le formulaire
        ui->lineEditSujet->setText(data.getSujet());
        ui->dateEdit->setDate(data.getDate());
        ui->timeEdit->setTime(data.getHeure());
        ui->spinBoxDuree->setValue(data.getDuree());
        ui->comboStatut->setCurrentText(data.getStatut());
        ui->lineEditFormateur->setText(data.getNomFormateur());
        ui->lineEditCentre->setText(data.getNomCentre());
        ui->spinBoxNbreInvites->setValue(data.getNbreInvites());

        idFormationCourante = id;  // ✅ Sauvegarde l’ID chargé
        QMessageBox::information(this, "Formation chargée", QString("📥 Formation ID %1 chargée.").arg(id));
    }
}




void formationwindow::on_btnModifier_clicked()
{
    if (idFormationCourante == -1) {
        QMessageBox::warning(this, "Erreur", "❗ Aucune formation chargée à modifier.");
        return;
    }

    // 🧠 Vérifie que l'ID est encore valide
    Formation f;
    if (!f.existe(idFormationCourante)) {
        QMessageBox::warning(this, "Erreur", "❌ La formation n'existe plus.");
        return;
    }

    // 🔄 Lecture des champs du formulaire
    QString sujet = ui->lineEditSujet->text().trimmed();
    QDate date = ui->dateEdit->date();
    QTime heure = ui->timeEdit->time();
    int duree = ui->spinBoxDuree->value();
    QString statut = ui->comboStatut->currentText();
    QString nom_formateur = ui->lineEditFormateur->text().trimmed();
    QString nom_centre = ui->lineEditCentre->text().trimmed();
    int nbreInvites = ui->spinBoxNbreInvites->value();
    QString codes_rfid = "";  // champ laissé vide

    // 🔧 Mise à jour
    Formation update(idFormationCourante, sujet, date, heure, duree, statut, nom_formateur, nom_centre, nbreInvites, codes_rfid);
    if (update.modifier(idFormationCourante)) {
        QMessageBox::information(this, "Succès", QString("✅ Formation ID %1 modifiée avec succès.").arg(idFormationCourante));
        refreshTable();
        dessinerStatistiques();
        envoyerSMS_Twilio(sujet, date, heure, statut, "✏️ Modification");
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification.");
    }
}




void formationwindow::on_btnSupprimer_clicked()
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

void formationwindow::dessinerStatistiques()
{
    // 📐 Image plus grande pour une meilleure lisibilité
    int largeur = 1000;
    int hauteur = 800;
    QPixmap pixmap(largeur, hauteur);
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);

    // 🎯 Rectangle pour dessiner le camembert au centre
    QRect rect((largeur - 300) / 2, 50, 300, 300);

    // 📊 Récupérer les données depuis la base Oracle
    int nbPrevue = Formation().compterParStatut("Prévue");
    int nbEncours = Formation().compterParStatut("En cours");
    int nbTerminee = Formation().compterParStatut("Terminée");
    int total = nbPrevue + nbEncours + nbTerminee;
    if (total == 0) return;  // Aucun graphique si aucune donnée

    // 🎂 Calcul des angles pour chaque part
    int anglePrevue = static_cast<int>(360.0 * nbPrevue / total);
    int angleEncours = static_cast<int>(360.0 * nbEncours / total);
    int angleTerminee = 360 - anglePrevue - angleEncours;

    // 🍰 Dessin des parts colorées
    int startAngle = 0;
    painter.setBrush(Qt::blue);
    painter.drawPie(rect, startAngle * 16, anglePrevue * 16);
    startAngle += anglePrevue;

    painter.setBrush(Qt::green);
    painter.drawPie(rect, startAngle * 16, angleEncours * 16);
    startAngle += angleEncours;

    painter.setBrush(Qt::red);
    painter.drawPie(rect, startAngle * 16, angleTerminee * 16);

    // 🧾 Légende
    QFont font = painter.font();
    font.setPointSize(14);
    painter.setFont(font);

    painter.setPen(Qt::blue);
    painter.drawText(50, 400, QString("🔵 Prévue : %1").arg(nbPrevue));

    painter.setPen(Qt::green);
    painter.drawText(50, 440, QString("🟢 En cours : %1").arg(nbEncours));

    painter.setPen(Qt::red);
    painter.drawText(50, 480, QString("🔴 Terminée : %1").arg(nbTerminee));

    // 🖼️ Création et affectation de la scène dans le bon widget (lié à btnStat)
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addPixmap(pixmap);

    ui->graphicsViewStats->setScene(scene);
    ui->graphicsViewStats->setSceneRect(pixmap.rect());
}


void formationwindow::on_btnOuvrirChatbotIA_clicked()
{
    if (!chatbot) {
        chatbot = new ChatbotIA(this);
    }
    chatbot->show();
}

void formationwindow::envoyerSMS_Twilio(const QString &message)
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

void formationwindow::envoyerSMS_Twilio(const QString &sujet, const QDate &date, const QTime &heure, const QString &statut, const QString &operation)
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


void formationwindow::on_btnVerifier_clicked()  // bouton "🔁 certif"
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

void formationwindow::on_btnVerifier1_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Choisir un PDF à vérifier", "", "PDF Files (*.pdf)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir le fichier.");
        return;
    }

    QByteArray content = file.readAll();
    file.close();

    QByteArray hash = QCryptographicHash::hash(content, QCryptographicHash::Sha256).toHex();
    QString signatureHex = QString(hash);

    // 🔍 Ouvrir le fichier texte des signatures
    QFile txtFile("signatures_certificats.txt");
    if (!txtFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir signatures_certificats.txt");
        return;
    }

    QTextStream in(&txtFile);
    QString ligneTrouvee;
    bool trouve = false;

    while (!in.atEnd()) {
        QString ligne = in.readLine().trimmed();
        if (ligne.contains(signatureHex)) {
            ligneTrouvee = ligne;
            trouve = true;
            break;
        }
    }
    txtFile.close();

    if (trouve) {
        QMessageBox::information(this, "Vérification réussie",
                                 "✅ Ce fichier est reconnu comme signé.\n\nHash :\n" + signatureHex + "\n\nLigne trouvée :\n" + ligneTrouvee);
    } else {
        QMessageBox::critical(this, "Fichier inconnu",
                              "❌ Ce fichier n’a pas été signé ou n’est pas reconnu.\n\nHash :\n" + signatureHex);
    }
}

void formationwindow::viderBaseFormations()
{
    QSqlQuery query;
    if (query.exec("DELETE FROM FORMATION")) {
        QMessageBox::information(this, "Nettoyage", "✅ Toutes les formations ont été supprimées !");
        refreshTable();  // Recharge la tableView
    } else {
        QMessageBox::critical(this, "Erreur", "❌ Échec lors de la suppression : " + query.lastError().text());
    }
}
void formationwindow::envoyerNotifDiscord(const QString &sujet, const QDate &date, const QString &action)
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
void formationwindow::on_btnOngletSignatures_clicked()
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


void formationwindow::on_btnTodo_clicked()
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

int formationwindow::obtenirDernierIDFormation() {
    QSqlQuery query;
    query.prepare("SELECT MAX(ID_FORMATION) FROM FORMATION");
    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}


// 🔄 Rafraîchir la table avec les données actuelles
void formationwindow::refreshTable() {
    Formation f;
    QSqlQueryModel *model = f.afficher();
    ui->tableView->setModel(model);

    // 🔥 RÉAPPLIQUER les Delegates après chaque setModel()
    ui->tableView->setItemDelegateForColumn(2, new DateDelegate(this));  // Date
    ui->tableView->setItemDelegateForColumn(3, new TimeDelegate(this));  // Heure

    int total = model->rowCount();
    ui->labelCompeur->setText("Nombre de formations : " + QString::number(total));
    dessinerStatistiques();
}

void formationwindow::on_btnRechercher_clicked() {
    QString critere = ui->chercher->text().trimmed();  // récupère le texte saisi

    if (critere.isEmpty()) {
        QMessageBox::information(this, "Champ vide", "Veuillez entrer un critère de recherche.");
        return;
    }

    Formation f;
    QSqlQueryModel *model = f.rechercherMulticritere(critere);

    if (model && model->rowCount() > 0) {
        ui->tableView->setModel(model);
    } else {
        QMessageBox::information(this, "Aucun résultat", "Aucune formation trouvée.");
    }
}

// 🔃 Trier bouton
void formationwindow::on_btnTrier_clicked() {
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
void formationwindow::on_btnAfficherTout_clicked() {
    refreshTable();
    dessinerStatistiques();
}

// 🧾 Générer PDF bouton
void formationwindow::on_btnGenererPDF_clicked()
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






    painter.end();
    QMessageBox::information(this, "✅ Succès", "PDF généré avec succès !");
}


void formationwindow::on_btnScanRFID_clicked()
{
    FenetreControleRFID *fenetreControle = new FenetreControleRFID(this);
    fenetreControle->exec();  // Affiche la fenêtre modale
}
void formationwindow::on_btnVoirHistorique_clicked()
{
    HistoriqueBadges historique(this);
    historique.exec();
}

void formationwindow::on_chercher_textChanged(const QString &text) {
    QString critere = text.trimmed();
    Formation f;
    QSqlQueryModel *model = f.rechercher(critere);  // utilise ta fonction déjà définie

    if (model && model->rowCount() > 0) {
        ui->tableView->setModel(model);
    } else {
        ui->tableView->setModel(nullptr);  // vide la table si aucun résultat
    }
}


void formationwindow::on_btnStat_clicked()
{
    if (!fenetreStats) {
        fenetreStats = new FenetreStatsF(this);
    }
    fenetreStats->exec();  // Ouvre la fenêtre modale
}

void formationwindow::on_btnCertificat_clicked()
{
    Deplome *dlg = new Deplome(this);
    dlg->exec();
}

void formationwindow::on_btnViderBase_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Confirmation",
        "Voulez-vous vraiment supprimer toutes les formations ?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes) {
        Formation f;
        if (f.supprimerTout()) {
            QMessageBox::information(this, "Succès", "Toutes les formations ont été supprimées.");
        } else {
            QMessageBox::warning(this, "Échec", "Échec de la suppression des formations.");
        }
    }
}

