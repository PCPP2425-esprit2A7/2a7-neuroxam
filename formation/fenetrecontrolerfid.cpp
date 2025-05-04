#include "fenetrecontrolerfid.h"
#include "ui_fenetrecontrolerfid.h"

#include <QSerialPortInfo>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

FenetreControleRFID::FenetreControleRFID(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::FenetreControleRFID),
    serial(new QSerialPort(this))
{
    ui->setupUi(this);

    ui->labelUID->setText("UID Scanné : ---");
    ui->labelStatut->setText("Statut Porte : ---");
    ui->labelStatut->setStyleSheet("font-size: 14pt; color: blue; font-weight: bold;");

    connect(serial, &QSerialPort::readyRead, this, &FenetreControleRFID::lireDonneesSerie);

    bool portOK = false;
    for (const QSerialPortInfo &info : QSerialPortInfo::availablePorts()) {
        if (info.description().contains("Arduino", Qt::CaseInsensitive) || info.vendorIdentifier() == 0x2341) {
            serial->setPort(info);
            serial->setBaudRate(QSerialPort::Baud9600);
            if (serial->open(QIODevice::ReadWrite)) {
                qDebug() << "✅ Port série ouvert :" << info.portName();
                portOK = true;
                break;
            }
        }
    }

    if (!portOK) {
        QMessageBox::critical(this, "Erreur", "Aucun port Arduino trouvé !");
        return;
    }

    connect(ui->btnOuvrir, &QPushButton::clicked, this, &FenetreControleRFID::ouvrirManuel);
    connect(ui->btnFermer, &QPushButton::clicked, this, &FenetreControleRFID::fermerManuel);

    serial->write("MODE_AUTO\n");
}

FenetreControleRFID::~FenetreControleRFID()
{
    if (serial && serial->isOpen()) {
        serial->write("MODE_AUTO\n");
        serial->flush();
        serial->close();
        qDebug() << "🔌 Port série fermé proprement.";
    }
    delete ui;
}

void FenetreControleRFID::closeEvent(QCloseEvent *event)
{
    if (serial && serial->isOpen()) {
        serial->write("MODE_AUTO\n");
        serial->flush();
        serial->close();
        qDebug() << "🔌 Port série fermé via closeEvent.";
    }
    QDialog::closeEvent(event);
}

/* ------------------------------------------------------------------ *
 *                   RÉCEPTION DES DONNÉES SÉRIE                      *
 * ------------------------------------------------------------------ */
void FenetreControleRFID::lireDonneesSerie()
{
    if (!serial || !serial->isOpen()) return;

    buffer += QString::fromUtf8(serial->readAll());

    int idx;
    while ((idx = buffer.indexOf('\n')) != -1) {
        QString ligne = buffer.left(idx).trimmed().toUpper();
        buffer.remove(0, idx + 1);

        if (ligne.isEmpty()) continue;
        qDebug() << "🔄 Ligne série :" << ligne;

        // 1️⃣ UID détecté
        if (ligne.startsWith("UID:")) {
            QString uid = ligne.mid(4).trimmed();
            if (uid.length() == 8 && verifierUID(uid)) {
                dernierUIDValide = uid;
                ui->labelUID->setText("UID Scanné : " + uid);
                ui->labelStatut->setText("✅ UID valide - Porte Ouverte");
                ui->labelStatut->setStyleSheet("font-size: 14pt; color: green; font-weight: bold;");
                serial->write("OPEN\n");
            } else {
                dernierUIDValide.clear();
                ui->labelStatut->setText("❌ UID refusé !");
                ui->labelStatut->setStyleSheet("font-size: 14pt; color: red; font-weight: bold;");
            }
            continue;
        }

        // 2️⃣ FLUX_ENTREE:UID reçu
        if (ligne.startsWith("FLUX_ENTREE:")) {
            QString uid = ligne.mid(QString("FLUX_ENTREE:").length()).trimmed();
            enregistrerEntree(uid);
            ui->listWidgetUIDs->addItem("✅ ENTRÉE : " + uid);
            ui->labelStatut->setText("🚪 Entrée enregistrée - Porte Fermée");
            ui->labelStatut->setStyleSheet("font-size: 14pt; color: blue; font-weight: bold;");
            serial->write("CLOSE\n");
            continue;
        }

        // 3️⃣ FLUX_SORTIE:UID reçu
        if (ligne.startsWith("FLUX_SORTIE:")) {
            QString uid = ligne.mid(QString("FLUX_SORTIE:").length()).trimmed();
            enregistrerSortie(uid);
            ui->listWidgetUIDs->addItem("✅ SORTIE : " + uid);
            ui->labelStatut->setText("🚪 Sortie enregistrée - Porte Fermée");
            ui->labelStatut->setStyleSheet("font-size: 14pt; color: purple; font-weight: bold;");
            serial->write("CLOSE\n");
            continue;
        }

        // 🚨 ALERTE Arduino
        if (ligne.contains("ALERTE")) {
            lancerAlerte("🚨 Alarme déclenchée !");
            serial->write("CLOSE\n");
            continue;
        }
    }
}

/* ------------------------------------------------------------------ *
 *                    VÉRIFICATION UID RFID                           *
 * ------------------------------------------------------------------ */
bool FenetreControleRFID::verifierUID(const QString &uid)
{
    QSqlQuery q;
    q.prepare("SELECT COUNT(*) FROM FORMATION WHERE INSTR(CODES_RFID, :uid) > 0");
    q.bindValue(":uid", uid);
    if (q.exec() && q.next()) {
        return q.value(0).toInt() > 0;
    }
    return false;
}

/* ------------------------------------------------------------------ *
 *                    ENREGISTRER ENTRÉE/SORTIE                       *
 * ------------------------------------------------------------------ */
void FenetreControleRFID::enregistrerEntree(const QString &uid)
{
    QSqlQuery q;
    q.prepare("SELECT NOM_FORMATEUR, ID_FORMATION FROM FORMATION WHERE INSTR(CODES_RFID, :uid) > 0");
    q.bindValue(":uid", uid);
    if (q.exec() && q.next()) {
        QString formateur = q.value(0).toString();
        int idFormation = q.value(1).toInt();

        QSqlQuery insert;
        insert.prepare("INSERT INTO BADGE_ENTREES (UID_BADGE, NOM_FORMATEUR, ID_FORMATION, DATE_ENTREE) "
                       "VALUES (:uid, :formateur, :id_formation, SYSDATE)");
        insert.bindValue(":uid", uid);
        insert.bindValue(":formateur", formateur);
        insert.bindValue(":id_formation", idFormation);
        insert.exec();
    }
}

void FenetreControleRFID::enregistrerSortie(const QString &uid)
{
    QSqlQuery update;
    update.prepare("UPDATE BADGE_ENTREES SET DATE_SORTIE = SYSDATE WHERE UID_BADGE = :uid AND DATE_SORTIE IS NULL");
    update.bindValue(":uid", uid);
    update.exec();
}

/* ------------------------------------------------------------------ *
 *                       ALERTES ET BOUTONS                           *
 * ------------------------------------------------------------------ */
void FenetreControleRFID::lancerAlerte(const QString &message)
{
    ui->labelStatut->setText(message);
    ui->labelStatut->setStyleSheet("font-size: 14pt; color: red; font-weight: bold;");
    ui->listWidgetUIDs->addItem(message);
}

void FenetreControleRFID::ouvrirManuel()
{
    if (!serial || !serial->isOpen()) return;
    serial->write("OPEN\n");
    ui->labelStatut->setText("Ouverture manuelle");
    ui->labelStatut->setStyleSheet("font-size: 14pt; color: orange; font-weight: bold;");
}

void FenetreControleRFID::fermerManuel()
{
    if (!serial || !serial->isOpen()) return;
    serial->write("CLOSE\n");
    ui->labelStatut->setText("Fermeture manuelle");
    ui->labelStatut->setStyleSheet("font-size: 14pt; color: blue; font-weight: bold;");
}
