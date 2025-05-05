#include "logdialog.h"
#include "ui_logdialog.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QInputDialog>
#include <QProcess>
#include <QUuid>
#include <QRandomGenerator>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    authenticated(false)
{
    ui->setupUi(this);
    connect(ui->forgotPasswordBtn, &QPushButton::clicked,this, &Dialog::onForgotPasswordClicked);
    connect(ui->Login, &QPushButton::clicked, this, &Dialog::handleLogin);
    connect(ui->Login_2, &QPushButton::clicked,this, &Dialog::on_Login_2_clicked);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::handleLogin()
{
    QString email = ui->lineEdit->text().trimmed();
    QString password = ui->lineEdit_2->text().trimmed();

    if (email.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Échec de connexion", "L'e-mail et le mot de passe ne peuvent pas être vides.");
        return;
    }

    bool ok;
    int a = QRandomGenerator::global()->bounded(1, 10);
    int b = QRandomGenerator::global()->bounded(1, 10);
    int answer = QInputDialog::getInt(this, "CAPTCHA",
                                      QString("Combien font %1 + %2 ?").arg(a).arg(b),
                                      0, 0, 100, 1, &ok);
    if (!ok || answer != (a + b)) {
        QMessageBox::warning(this, "Captcha échoué", "Réponse incorrecte.");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYE WHERE LOWER(email)=LOWER(:email) AND password=:password");
    query.bindValue(":email", email);
    query.bindValue(":password", password);

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur base de données", query.lastError().text());
        return;
    }

    if (query.next()) {
        // Connexion réussie
        authenticated = true;
        QMessageBox::information(this, "Connexion réussie", "Bienvenue !");
        accept();  // Ferme la boîte de dialogue et affiche MainWindow
    } else {
        QMessageBox::warning(this, "Échec de connexion", "E-mail ou mot de passe incorrect.");
    }
}

void Dialog::onForgotPasswordClicked()
{
    QString email = QInputDialog::getText(this, "Récupération de mot de passe", "Entrez votre e-mail :");
    qDebug() << "📧 Email entré par l'utilisateur :" << email;

    if (email.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "L'e-mail ne peut pas être vide !");
        return;
    }

    QSqlQuery checkAll;
    checkAll.exec("SELECT email FROM EMPLOYE");
    qDebug() << "📦 Emails existants dans la table EMPLOYE :";
    while (checkAll.next()) {
        qDebug() << " - " << checkAll.value(0).toString();
    }

    QSqlQuery query;
    query.prepare("SELECT numero_telephone, password FROM EMPLOYE WHERE LOWER(email) = LOWER(:email)");
    query.bindValue(":email", email);

    if (!query.exec()) {
        qDebug() << "❌ Échec de l'exécution de la requête :" << query.lastError().text();
        QMessageBox::critical(this, "Erreur", "La requête vers la base de données a échoué.");
        return;
    }

    if (!query.next()) {
        qDebug() << "❌ Aucun e-mail correspondant trouvé pour :" << email;
        QMessageBox::warning(this, "Erreur", "E-mail introuvable dans la base de données !");
        return;
    }

    QString phone = query.value(0).toString();
    QString password = query.value(1).toString();
    QString message = "Votre mot de passe actuel est : " + password;

    qDebug() << "📱 Téléphone :" << phone;
    qDebug() << "🔑 Mot de passe :" << password;

    if (sendSMS(phone, message)) {
        QMessageBox::information(this, "Succès", "Mot de passe envoyé par SMS !");
    } else {
        qDebug() << "❌ Échec de l'envoi du SMS";
        QMessageBox::critical(this, "Erreur", "Échec de l'envoi du SMS.");
    }
}

bool Dialog::sendSMS(const QString &phoneNumber, const QString &message)
{
    QProcess curl;
    QString accountSID = "";
    QString authToken = "";
    QString fromPhone = "";  // Numéro d'essai Twilio

    QString curlPath = "C:/Windows/System32/curl.exe";

    QStringList args;
    args << "--ssl-no-revoke"
         << "-X" << "POST"
         << QString("https://api.twilio.com/2010-04-01/Accounts/%1/Messages.json").arg(accountSID)
         << "--data-urlencode" << "To=" + phoneNumber
         << "--data-urlencode" << "From=" + fromPhone
         << "--data-urlencode" << "Body=" + message
         << "-u" << accountSID + ":" + authToken;

    qDebug() << "📤 Utilisation du chemin curl :" << curlPath;
    qDebug() << "📤 Arguments curl complets :" << args;

    curl.start(curlPath, args);
    curl.waitForFinished();

    QString output = curl.readAllStandardOutput();
    QString errorOutput = curl.readAllStandardError();

    qDebug() << "✅ Sortie standard Twilio :" << output;
    qDebug() << "❌ Erreur standard Twilio :" << errorOutput;

    // Retour sécurisé : accepte queued, sent, delivered
    bool success = output.contains("queued") || output.contains("sent") || output.contains("delivered");

    qDebug() << "✔️ Envoi du SMS réussi :" << success;
    return success;
}

void Dialog::on_Login_2_clicked()
{
    QProcess faceCheck;

    QString scriptPath = "C:/Users/user/Documents/GTemploye/verify_face.py";
    QString pythonPath = "C:/Users/user/AppData/Local/Programs/Python/Python311/python.exe"; // mettre à jour si nécessaire

    qDebug() << "👤 Exécution du script FaceID avec Python :" << pythonPath;
    qDebug() << "📄 Chemin du script :" << scriptPath;

    faceCheck.setProgram("C:/Users/user/AppData/Local/Programs/Python/Python313/python.exe");
    faceCheck.setArguments(QStringList() << scriptPath);
    faceCheck.setWorkingDirectory("C:/Users/user/Documents/GTemploye");

    faceCheck.start();
    faceCheck.waitForFinished();

    QString stdOut = faceCheck.readAllStandardOutput().trimmed();
    QString stdErr = faceCheck.readAllStandardError().trimmed();

    qDebug() << "✅ STDOUT du script :" << stdOut;
    qDebug() << "❌ STDERR du script :" << stdErr;

    if (stdOut.startsWith("SUCCESS:")) {
        QString userFile = stdOut.section(':', 1, 1);         // ex : "user1.jpg"
        QString username = userFile.section('.', 0, 0);       // ex : "user1"
        QMessageBox::information(this, "Reconnaissance faciale", "✅ Bienvenue, " + username);
        accept();
    } else {
        QMessageBox::warning(this, "Reconnaissance faciale", "❌ Visage non reconnu. Veuillez réessayer.");
    }
}
