#include "deplome.h"
#include "ui_deplome.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include <QPdfWriter>
#include <QPainter>
#include <QFile>
#include <QCryptographicHash>
#include <QDateTime>
#include <QDesktopServices>
#include <QUrl>
#include <QTextStream>
#include <QFileInfo>

Deplome::Deplome(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Deplome)
{
    ui->setupUi(this);

    ui->labelSujet->setText("Sujet : ---");
    ui->labelDate->setText("Date  : ---");
    ui->labelHeure->setText("Heure : ---");
    ui->labelDuree->setText("Durée : ---");

    connect(ui->btnRechercherFormation, &QPushButton::clicked, this, &Deplome::on_btnRechercherFormation_clicked);
    connect(ui->btnValider, &QPushButton::clicked, this, &Deplome::on_btnValider_clicked);
    connect(ui->btnChoisirImage, &QPushButton::clicked, this, &Deplome::on_btnChoisirImage_clicked);
    connect(ui->btnOuvrirHistorique, &QPushButton::clicked, this, &Deplome::on_btnOuvrirHistorique_clicked);
}

Deplome::~Deplome()
{
    delete ui;
}

void Deplome::on_btnRechercherFormation_clicked()
{
    QString id = ui->lineEditIdFormation->text().trimmed();
    if (id.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir un ID de formation.");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT SUJET, DATE_FORMATION, HEURE_FORMATION, DUREE FROM FORMATION WHERE ID_FORMATION = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        sujet = query.value(0).toString();
        date = query.value(1).toDate();
        heure = query.value(2).toTime();
        duree = query.value(3).toInt();

        ui->labelSujet->setText("Sujet : " + sujet);
        ui->labelDate->setText("Date  : " + date.toString("dd/MM/yyyy"));
        ui->labelHeure->setText("Heure : " + heure.toString("hh:mm"));
        ui->labelDuree->setText("Durée : " + QString::number(duree) + " minutes");
    } else {
        QMessageBox::warning(this, "Erreur", "Formation introuvable.");
    }
}

void Deplome::on_btnChoisirImage_clicked()
{
    imagePath = QFileDialog::getOpenFileName(this, "Choisir une image", "", "Images (*.png *.jpg *.jpeg)");
    if (!imagePath.isEmpty()) {
        ui->labelImage->setText("🖼️ Image sélectionnée : " + QFileInfo(imagePath).fileName());
    } else {
        ui->labelImage->setText("📁 Aucune image sélectionnée");
    }
}

void Deplome::on_btnValider_clicked()
{
    QString nomEmploye = ui->lineEditNomEmploye->text().trimmed();
    if (nomEmploye.isEmpty() || sujet.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Remplissez tous les champs nécessaires.");
        return;
    }

    QString nomFichierParDefaut = "certificat_" + nomEmploye + "_" + sujet + ".pdf";
    nomFichierParDefaut.replace(" ", "_");

    QString filename = QFileDialog::getSaveFileName(this, "Enregistrer le certificat", nomFichierParDefaut, "PDF (*.pdf)");
    if (filename.isEmpty()) return;
    if (!filename.endsWith(".pdf")) filename += ".pdf";

    QPdfWriter writer(filename);
    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setResolution(300);
    QPainter painter(&writer);
    QRect fullPage(0, 0, writer.width(), writer.height());

    QLinearGradient gradient(fullPage.topLeft(), fullPage.bottomRight());
    gradient.setColorAt(0, QColor("#DCEEFF"));
    gradient.setColorAt(1, Qt::white);
    painter.fillRect(fullPage, gradient);

    painter.setPen(QPen(Qt::blue, 2));
    painter.drawRect(fullPage.adjusted(30, 30, -30, -30));

    if (!imagePath.isEmpty()) {
        QImage logo(imagePath);
        if (!logo.isNull()) {
            QRect logoRect(writer.width() / 2 - 50, 50, 100, 100);
            painter.drawImage(logoRect, logo.scaled(100, 100, Qt::KeepAspectRatio));
        }
    }

    int x = 100;
    int y = 200;
    int lineSpacing = 70;
    QString dateCreation = QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm");

    painter.setPen(QColor("#003366"));
    painter.setFont(QFont("Segoe UI", 18, QFont::Bold));
    painter.drawText(x, y, "🎓 Certificat de Réussite");
    painter.setFont(QFont("Segoe UI", 12));
    painter.setPen(Qt::black);
    y += lineSpacing * 2;
    painter.drawText(x, y, "Ce certificat atteste que :");
    y += lineSpacing;
    painter.setFont(QFont("Segoe UI", 13, QFont::Bold));
    painter.drawText(x, y, nomEmploye);
    y += lineSpacing;
    painter.setFont(QFont("Segoe UI", 12));
    painter.drawText(x, y, "a suivi avec succès la formation suivante :");
    y += lineSpacing;
    painter.setFont(QFont("Segoe UI", 12, QFont::Bold));
    painter.drawText(x, y, "📘 Sujet  : " + sujet);
    y += lineSpacing;
    painter.drawText(x, y, "📅 Date   : " + date.toString("dd/MM/yyyy"));
    y += lineSpacing;
    painter.drawText(x, y, "⏰ Heure  : " + heure.toString("hh:mm"));
    y += lineSpacing;
    painter.drawText(x, y, "⏱️ Durée  : " + QString::number(duree) + " minutes");
    y += lineSpacing;
    painter.drawText(x, y, "🕓 Date de création : " + dateCreation);
    y += lineSpacing;
    painter.drawText(x, y, "🎉 Félicitations pour votre réussite !");
    painter.end();

    QFile filePDF(filename);
    if (!filePDF.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir le PDF pour le hash.");
        return;
    }

    QByteArray hash = QCryptographicHash::hash(filePDF.readAll(), QCryptographicHash::Sha256).toHex();
    filePDF.close();

    QFile log("signatures_certificats.txt");
    if (log.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&log);
        out << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") << " | "
            << nomEmploye << " | " << sujet << " | " << hash << "\n";
        log.close();
    }

    QDesktopServices::openUrl(QUrl::fromLocalFile(filename));
    QMessageBox::information(this, "Succès", "🎉 Certificat généré et signé !");
}

void Deplome::on_btnOuvrirHistorique_clicked()
{
    QString logPath = "signatures_certificats.txt";
    if (!QFile::exists(logPath)) {
        QMessageBox::warning(this, "Fichier introuvable", "Aucune signature n'a encore été enregistrée.");
        return;
    }

    QDesktopServices::openUrl(QUrl::fromLocalFile(QFileInfo(logPath).absoluteFilePath()));
}
