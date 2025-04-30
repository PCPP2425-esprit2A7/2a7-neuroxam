#include "fenetrescanbadges.h"
#include "ui_fenetrescanbadges.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSerialPortInfo>
#include <QTimer>
#include <QMessageBox>
#include <QDebug>

FenetreScanBadges::FenetreScanBadges(int idFormation, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FenetreScanBadges),
    idFormation(idFormation),
    dernierUID(""),
    attenteLecture(false),
    buffer("")
{
    ui->setupUi(this);
    ui->labelTitre->setText("📋 Scan des Badges pour Formation ID : " + QString::number(idFormation));

    initialiserPortSerie();

    connect(ui->btnTerminer, &QPushButton::clicked, this, [=]() {
        fermerPortSerie();
        this->close();
    });

    chargerBadgesExistants();
}

FenetreScanBadges::~FenetreScanBadges()
{
    fermerPortSerie();
    delete ui;
}

void FenetreScanBadges::closeEvent(QCloseEvent *event)
{
    fermerPortSerie();
    QDialog::closeEvent(event);
}

void FenetreScanBadges::fermerPortSerie()
{
    if (serialPort && serialPort->isOpen()) {
        serialPort->write("MODE_AUTO\n");
        serialPort->flush();
        serialPort->close();
        qDebug() << "🔌 Port série fermé (fermerPortSerie).";
    }
}

void FenetreScanBadges::initialiserPortSerie() {
    serialPort = new QSerialPort(this);
    bool portTrouve = false;

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        if (info.description().contains("Arduino") || info.vendorIdentifier() == 0x2341) {
            serialPort->setPort(info);
            serialPort->setBaudRate(QSerialPort::Baud9600);
            if (serialPort->open(QIODevice::ReadWrite)) {
                connect(serialPort, &QSerialPort::readyRead, this, &FenetreScanBadges::lireBadge);
                serialPort->write("MODE_SCAN\n");
                serialPort->flush();
                qDebug() << "✅ Port série détecté et ouvert : " << info.portName();
                portTrouve = true;
                break;
            }
        }
    }

    if (!portTrouve) {
        qDebug() << "❌ Aucun port série trouvé pour scan.";
        QMessageBox::critical(this, "Erreur", "Aucun port série Arduino détecté !");
    }
}

void FenetreScanBadges::lireBadge() {
    if (!serialPort || !serialPort->isOpen()) return;

    QByteArray data = serialPort->readAll();
    buffer += QString::fromUtf8(data);

    while (buffer.contains('\n')) {
        int index = buffer.indexOf('\n');
        QString ligne = buffer.left(index).trimmed().toUpper();
        buffer = buffer.mid(index + 1);

        qDebug() << "📝 Ligne complète : " << ligne;

        if (!ligne.startsWith("UID:")) {
            qDebug() << "⏭️ Ignoré : " << ligne;
            continue;
        }

        QString uid = ligne.mid(4);

        if (uid == dernierUID) {
            qDebug() << "🔁 UID déjà traité : " << uid;
            continue;
        }

        dernierUID = uid;
        attenteLecture = true;
        QTimer::singleShot(2000, this, [=]() { attenteLecture = false; });

        qDebug() << "🔍 Nouveau Badge détecté : " << uid;
        enregistrerBadge(uid);
    }
}

void FenetreScanBadges::enregistrerBadge(QString uid) {
    if (!listeBadges.contains(uid)) {
        listeBadges.append(uid);
        ui->listWidgetBadges->addItem(uid);
        mettreAJourBase();

        // 🔥 Insérer dans BADGE_ENTREES
        QSqlQuery query;
        query.prepare(R"(
            INSERT INTO BADGE_ENTREES (UID_BADGE, ID_FORMATION, NOM_FORMATEUR, HEURE_ENTREE)
            VALUES (:uid, :id_formation,
            (SELECT NOM_FORMATEUR FROM FORMATION WHERE ID_FORMATION = :id_formation),
            SYSDATE)
        )");

        query.bindValue(":uid", uid);
        query.bindValue(":id_formation", idFormation);

        if (!query.exec()) {
            qDebug() << "❌ Erreur insertion historique badge :" << query.lastError().text();
        } else {
            qDebug() << "✅ Badge inséré dans BADGE_ENTREES";
        }

        QMessageBox::information(this, "Succès", "✅ Badge ajouté : " + uid);
    } else {
        qDebug() << "⚠️ Badge déjà enregistré : " << uid;
        QMessageBox::information(this, "Info", "⚠️ Badge déjà enregistré !");
    }
}

void FenetreScanBadges::mettreAJourBase() {
    QString nouvelleChaine = listeBadges.join(",");
    QSqlQuery query;
    query.prepare("UPDATE FORMATION SET CODES_RFID = :codes_rfid WHERE ID_FORMATION = :id_formation");
    query.bindValue(":codes_rfid", nouvelleChaine);
    query.bindValue(":id_formation", idFormation);

    if (!query.exec()) {
        qDebug() << "❌ Erreur MAJ base : " << query.lastError().text();
        QMessageBox::critical(this, "Erreur SQL", "❌ Impossible de mettre à jour la base !");
    } else {
        qDebug() << "✅ Base mise à jour avec : " << nouvelleChaine;
        emit badgesMisAJour();
    }
}

void FenetreScanBadges::chargerBadgesExistants() {
    QSqlQuery query;
    query.prepare("SELECT CODES_RFID FROM FORMATION WHERE ID_FORMATION = :id_formation");
    query.bindValue(":id_formation", idFormation);

    if (query.exec() && query.next()) {
        QString codesExistants = query.value(0).toString();
        if (!codesExistants.isEmpty()) {
            listeBadges = codesExistants.split(",", Qt::SkipEmptyParts);
            foreach (const QString &badge, listeBadges) {
                ui->listWidgetBadges->addItem(badge);
            }
            qDebug() << "🔄 Badges existants chargés : " << codesExistants;
        }
    } else {
        qDebug() << "❌ Erreur chargement badges existants : " << query.lastError().text();
    }
}
