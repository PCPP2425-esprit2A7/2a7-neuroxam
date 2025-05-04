#include "logdialog.h"
#include "ui_logdialog.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QInputDialog>
#include <QProcess>
#include <QRandomGenerator>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QCoreApplication>
#include <algorithm> // For std::sort
#include <QProcessEnvironment> // For getting environment variables

logdialog::logdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::logdialog),
    authenticated(false)
{
    ui->setupUi(this);
}

logdialog::~logdialog()
{
    delete ui;
}

void logdialog::on_Login_clicked()
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


bool logdialog::sendSMS(const QString &phoneNumber, const QString &message)
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

void logdialog::on_Login_2_clicked()
{
    QProcess faceCheck;

    QString scriptPath = "C:/Users/il-ye/OneDrive/Bureau/qt/refactoring/neuroxam/verify_face.py";

    // Find Python executable using standard paths
    QString pythonPath;
    QString username = qgetenv("USERNAME"); // Get current username
    QStringList possiblePaths = {
        // Try specific path with current username
        QDir::toNativeSeparators(QString("C:/Users/%1/AppData/Local/Programs/Python/Python312/python.exe").arg(username)),
        // General paths
        "python",                  // System-wide Python (PATH)
        "python3",                 // System-wide Python 3 (PATH)
        QDir::toNativeSeparators(QDir::homePath() + "/AppData/Local/Programs/Python/Python3*/python.exe"), // Windows user install
        "/usr/bin/python3",        // Linux standard path
        "/usr/local/bin/python3",  // macOS/Homebrew standard path
        "C:/Python3*/python.exe"   // Windows system-wide install
    };

    // Try each path to find a working Python
    for (const QString &path : possiblePaths) {
        // Handle wildcards for version numbers
        if (path.contains("*")) {
            QStringList matchingPaths;
            QString basePath = path;
            basePath.replace("*", "");
            QDir baseDir(basePath.section('/', 0, -2));

            // Find matching directories
            QStringList filters;
            filters << path.section('/', -2, -2);
            QStringList dirs = baseDir.entryList(filters, QDir::Dirs);

            // Sort to get latest version
            std::sort(dirs.begin(), dirs.end(), std::greater<QString>());

            for (const QString &dir : dirs) {
                QString testPath = path;
                testPath.replace("*", "");
                testPath.replace(testPath.section('/', -2, -2), dir);
                if (QFile::exists(testPath)) {
                    matchingPaths << testPath;
                }
            }

            if (!matchingPaths.isEmpty()) {
                pythonPath = matchingPaths.first();
                break;
            }
        }
        // Test direct paths
        else {
            QProcess testProcess;
            testProcess.start(path, QStringList() << "--version");
            if (testProcess.waitForFinished(2000) && testProcess.exitCode() == 0) {
                pythonPath = path;
                break;
            }
        }
    }

    if (pythonPath.isEmpty()) {
        QMessageBox::critical(this, "Error", "Python interpreter not found. Please install Python 3.");
        return;
    }

    qDebug() << "👤 Running FaceID script with Python:" << pythonPath;
    qDebug() << "📄 Script path:" << scriptPath;

    // Get application directory path
    QString appDir = QCoreApplication::applicationDirPath();

    faceCheck.setProgram(pythonPath);
    faceCheck.setArguments(QStringList() << scriptPath);
    faceCheck.setWorkingDirectory(appDir);
    faceCheck.start();

    if (!faceCheck.waitForStarted()) {
        QMessageBox::critical(this, "Error", "Failed to start face verification script.");
        return;
    }

    if (!faceCheck.waitForFinished(30000)) { // 30 second timeout
        faceCheck.kill();
        QMessageBox::warning(this, "Face ID", "Face verification timed out. Please try again.");
        return;
    }

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
        QString errorMsg = "❌ Face not recognized.";
        if (!stdErr.isEmpty()) {
            errorMsg += "\nError: " + stdErr;
        }
        QMessageBox::warning(this, "Face ID", errorMsg);
    }
}

void logdialog::on_forgotPasswordBtn_clicked()
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

