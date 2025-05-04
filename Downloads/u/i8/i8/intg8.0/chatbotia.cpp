#include "chatbotia.h"
#include "formation.h"

#include "ui_chatbotia.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QClipboard>
#include <QGuiApplication>

ChatbotIA::ChatbotIA(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChatbotIA)
{
    ui->setupUi(this);
    setWindowTitle("🤖 Assistant IA – Aide à la décision");

    connect(ui->btnEnvoyerQuestion, &QPushButton::clicked, this, &ChatbotIA::on_btnEnvoyerQuestion_clicked);
    connect(ui->btnRecommander, &QPushButton::clicked, this, &ChatbotIA::on_btnRecommander_clicked);
    connect(ui->btnCopierTexte, &QPushButton::clicked, this, &ChatbotIA::on_btnCopierTexte_clicked);
}

ChatbotIA::~ChatbotIA()
{
    delete ui;
}

// Génère un prompt basé sur les sujets de formation
QString ChatbotIA::genererPromptDepuisBase()
{
    Formation f;
    QStringList sujets = f.getTousLesSujets();  // Cette fonction doit exister dans formation.cpp

    QString prompt = "Voici la liste des sujets de formation actuellement disponibles :\n";
    for (const QString &s : sujets) {
        prompt += "- " + s + "\n";
    }

    prompt += "\nMerci de recommander des formations internationales similaires (ex: Coursera, Udemy) avec une brève justification.";
    return prompt;
}

void ChatbotIA::on_btnEnvoyerQuestion_clicked()
{
    QString question = ui->lineEditInputQuestion->text().trimmed();
    if (question.isEmpty()) {
        QMessageBox::warning(this, "Champ vide", "Veuillez entrer une question.");
        return;
    }
    envoyerPromptIA(question);
}

void ChatbotIA::on_btnRecommander_clicked()
{
    QString prompt = genererPromptDepuisBase();
    envoyerPromptIA(prompt);
}

// Copie la réponse
void ChatbotIA::on_btnCopierTexte_clicked()
{
    QString texte = ui->plainTextEditReponse->toPlainText();
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(texte);
}

// Envoie la requête à OpenRouter
void ChatbotIA::envoyerPromptIA(const QString &texte)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    QNetworkRequest request(QUrl("https://openrouter.ai/api/v1/chat/completions"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Clé API

    QJsonArray messages;
    messages.append(QJsonObject{{"role", "user"}, {"content", texte}});

    QJsonObject body;
    body["model"] = "openai/gpt-3.5-turbo";
    body["messages"] = messages;
    body["max_tokens"] = 300;

    QNetworkReply *reply = manager->post(request, QJsonDocument(body).toJson());

    connect(reply, &QNetworkReply::finished, this, [=]() {
        QByteArray response = reply->readAll();

        QJsonParseError parseError;
        QJsonDocument doc = QJsonDocument::fromJson(response, &parseError);

        if (parseError.error != QJsonParseError::NoError || !doc.isObject()) {
            ui->plainTextEditReponse->setPlainText("❌ Réponse invalide de l'IA.");
        } else {
            QJsonObject obj = doc.object();
            QJsonArray choices = obj["choices"].toArray();
            if (!choices.isEmpty()) {
                QString content = choices[0].toObject()["message"].toObject()["content"].toString();
                ui->plainTextEditReponse->setPlainText(content.trimmed());
            } else {
                ui->plainTextEditReponse->setPlainText("❌ L'IA n'a pas renvoyé de contenu.");
            }
        }

        reply->deleteLater();
        manager->deleteLater();
    });
}
