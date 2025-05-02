#include "emaildialog.h"
#include "ui_emaildialog.h"
#include <QProcess>
#include <QMessageBox>

EmailDialog::EmailDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmailDialog)
{
    ui->setupUi(this);
    ui->dateEdit_dateExamen->setDate(QDate::currentDate());

    connect(ui->btn_annuler, &QPushButton::clicked, this, &QDialog::reject);
    connect(ui->btn_envoyer, &QPushButton::clicked, this, &EmailDialog::onEnvoyerClicked);
}

EmailDialog::~EmailDialog()
{
    delete ui;
}

void EmailDialog::onEnvoyerClicked()
{
    QString email = ui->lineEdit_email->text().trimmed();
    QString date = ui->dateEdit_dateExamen->date().toString("dd/MM/yyyy");
    QString message = ui->textEdit_message->toPlainText();


    if (email.isEmpty() || message.isEmpty()) {
        QMessageBox::warning(this, "Champs manquants", "Veuillez remplir l'email et le message.");
        return;
    }

    QString contenu = message + "\n\nDate du examen : " + date;
    envoyerEmail(email, "Notification de examen", contenu);

    QMessageBox::information(this, "Succès", "Email envoyé à " + email);
    this->accept();
}

void EmailDialog::envoyerEmail(QString email, QString sujet, QString message)
{
    QString program = "C:/Users/ThinkPad/AppData/Local/Microsoft/WindowsApps/python.exe";
    // Remplace ce chemin par celui où Python est installé
    // ou "python" selon ton système
    QString scriptPath = "C:/esprit 2/int/send_email.py";

    QStringList arguments;
    arguments << scriptPath << email << sujet << message;

    // Debug pour vérifier que les bons arguments sont passés
    qDebug() << "Arguments passés au script Python : " << arguments;

    QProcess process;
    process.start(program, arguments);
    process.waitForFinished();

    QString output = process.readAllStandardOutput();
    QString errors = process.readAllStandardError();
    qDebug() << "Email envoyé à :" << email;
    qDebug() << "Sortie standard : " << process.readAllStandardOutput();
    qDebug() << "Erreur standard : " << process.readAllStandardError();
}
