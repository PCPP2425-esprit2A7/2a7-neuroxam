#include "fenetrecontrolerfid.h"
#include "ui_fenetrecontrolerfid.h"

#include <QSerialPortInfo>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
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

        if (ligne.startsWith("UID:")) {
            QString uid = ligne.mid(4).trimmed();
            dernierUIDValide = uid;
            ui->labelUID->setText("UID Scanné : " + uid);
            ui->labelStatut->setText("✅ UID scanné - Porte Ouverte");
            ui->labelStatut->setStyleSheet("font-size: 14pt; color: green; font-weight: bold;");
            serial->write("OPEN\n");
            continue;
        }

        if (ligne.startsWith("FLUX_ENTREE:")) {
            QString uid = ligne.mid(QString("FLUX_ENTREE:").length()).trimmed();
            enregistrerDansFichier("ENTREE", uid);
            ui->listWidgetUIDs->addItem("✅ ENTRÉE : " + uid);
            ui->labelStatut->setText("🚪 Entrée enregistrée - Porte Fermée");
            ui->labelStatut->setStyleSheet("font-size: 14pt; color: blue; font-weight: bold;");
            serial->write("CLOSE\n");
            continue;
        }

        if (ligne.startsWith("FLUX_SORTIE:")) {
            QString uid = ligne.mid(QString("FLUX_SORTIE:").length()).trimmed();
            enregistrerDansFichier("SORTIE", uid);
            ui->listWidgetUIDs->addItem("✅ SORTIE : " + uid);
            ui->labelStatut->setText("🚪 Sortie enregistrée - Porte Fermée");
            ui->labelStatut->setStyleSheet("font-size: 14pt; color: purple; font-weight: bold;");
            serial->write("CLOSE\n");
            continue;
        }

        if (ligne.contains("ALERTE")) {
            lancerAlerte("🚨 Alarme déclenchée !");
            serial->write("CLOSE\n");
            continue;
        }
    }
}

void FenetreControleRFID::enregistrerDansFichier(const QString &type, const QString &uid)
{
    QFile fichier("historique_badges.txt");
    if (fichier.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&fichier);
        QString horodatage = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        out << type << " ; " << uid << " ; " << horodatage << "\n";
        fichier.close();
    } else {
        qDebug() << "❌ Erreur ouverture fichier historique_badges.txt";
    }
}

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
