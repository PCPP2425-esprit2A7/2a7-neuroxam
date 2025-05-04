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
        QMessageBox::warning(this, "Login Failed", "Email and password cannot be empty.");
        return;
    }
    bool ok;
    int a = QRandomGenerator::global()->bounded(1, 10);
    int b = QRandomGenerator::global()->bounded(1, 10);
    int answer = QInputDialog::getInt(this, "CAPTCHA",
                                      QString("What is %1 + %2?").arg(a).arg(b),
                                      0, 0, 100, 1, &ok);
    if (!ok || answer != (a + b)) {
        QMessageBox::warning(this, "Captcha Failed", "Incorrect answer.");
        return;
    }
    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYE WHERE LOWER(email)=LOWER(:email) AND password=:password");
    query.bindValue(":email", email);
    query.bindValue(":password", password);

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
        return;
    }

    if (query.next()) {
        // Login success
        authenticated = true;
        QMessageBox::information(this, "Login Successful", "Welcome!");
        accept();  // Closes the dialog and shows MainWindow
    } else {
        QMessageBox::warning(this, "Login Failed", "Incorrect email or password.");
    }
}


void Dialog::onForgotPasswordClicked()
{
    QString email = QInputDialog::getText(this, "Recover Password", "Enter your email:");
    qDebug() << "📧 Email entered by user:" << email;

    if (email.isEmpty()) {
        QMessageBox::warning(this, "Error", "Email cannot be empty!");
        return;
    }

    QSqlQuery checkAll;
    checkAll.exec("SELECT email FROM EMPLOYE");
    qDebug() << "📦 Existing emails in EMPLOYE table:";
    while (checkAll.next()) {
        qDebug() << " - " << checkAll.value(0).toString();
    }

    QSqlQuery query;
    query.prepare("SELECT numero_telephone, password FROM EMPLOYE WHERE LOWER(email) = LOWER(:email)");
    query.bindValue(":email", email);

    if (!query.exec()) {
        qDebug() << "❌ Query execution failed:" << query.lastError().text();
        QMessageBox::critical(this, "Error", "Database query failed.");
        return;
    }

    if (!query.next()) {
        qDebug() << "❌ No matching email found for:" << email;
        QMessageBox::warning(this, "Error", "Email not found in database!");
        return;
    }

    QString phone = query.value(0).toString();
    QString password = query.value(1).toString();
    QString message = "Your current password is: " + password;

    qDebug() << "📱 Phone:" << phone;
    qDebug() << "🔑 Password:" << password;

    if (sendSMS(phone, message)) {
        QMessageBox::information(this, "Success", "Password sent to your phone via SMS!");
    } else {
        qDebug() << "❌ sendSMS failed";
        QMessageBox::critical(this, "Error", "Failed to send SMS.");
    }
}


bool Dialog::sendSMS(const QString &phoneNumber, const QString &message)
{
    QProcess curl;
    QString accountSID = "";
    QString authToken = "";
    QString fromPhone = "";  // Your Twilio trial number

    QString curlPath = "C:/Windows/System32/curl.exe";

    QStringList args;
    args << "--ssl-no-revoke"
         << "-X" << "POST"
         << QString("https://api.twilio.com/2010-04-01/Accounts/%1/Messages.json").arg(accountSID)
         << "--data-urlencode" << "To=" + phoneNumber
         << "--data-urlencode" << "From=" + fromPhone
         << "--data-urlencode" << "Body=" + message
         << "-u" << accountSID + ":" + authToken;

    qDebug() << "📤 Using curl path:" << curlPath;
    qDebug() << "📤 Full curl arguments:" << args;

    curl.start(curlPath, args);
    curl.waitForFinished();

    QString output = curl.readAllStandardOutput();
    QString errorOutput = curl.readAllStandardError();

    qDebug() << "✅ Twilio STDOUT:" << output;
    qDebug() << "❌ Twilio STDERR:" << errorOutput;

    // SAFER return: accept queued, sent, delivered
    bool success = output.contains("queued") || output.contains("sent") || output.contains("delivered");

    qDebug() << "✔️ SMS send success:" << success;
    return success;
}

void Dialog::on_Login_2_clicked()
{
    QProcess faceCheck;

    QString scriptPath = "C:/Users/user/Documents/GTemploye/verify_face.py";
    QString pythonPath = "C:/Users/user/AppData/Local/Programs/Python/Python311/python.exe"; // update path if needed

    qDebug() << "👤 Running FaceID script with Python:" << pythonPath;
    qDebug() << "📄 Script path:" << scriptPath;

    faceCheck.setProgram("C:/Users/user/AppData/Local/Programs/Python/Python313/python.exe");
    faceCheck.setArguments(QStringList() << scriptPath);
    faceCheck.setWorkingDirectory("C:/Users/user/Documents/GTemploye");

    faceCheck.start();
    faceCheck.waitForFinished();

    QString stdOut = faceCheck.readAllStandardOutput().trimmed();
    QString stdErr = faceCheck.readAllStandardError().trimmed();

    qDebug() << "✅ STDOUT from script:" << stdOut;
    qDebug() << "❌ STDERR from script:" << stdErr;

    if (stdOut.startsWith("SUCCESS:")) {
        QString userFile = stdOut.section(':', 1, 1);         // e.g. "user1.jpg"
        QString username = userFile.section('.', 0, 0);       // e.g. "user1"
        QMessageBox::information(this, "Face ID", "✅ Welcome, " + username);
        accept();
    } else {
        QMessageBox::warning(this, "Face ID", "❌ Face not recognized. Try again.");
    }
}
