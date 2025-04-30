#include "googleuploader.h"

#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <QHttpMultiPart>
#include <QNetworkReply>           // ✅ Manquant !
#include <QMessageBox>             // ✅ Manquant !
#include <QNetworkRequest>

GoogleUploader::GoogleUploader(QObject *parent)
    : QObject(parent), manager(new QNetworkAccessManager(this))
{
}

void GoogleUploader::uploadWithoutAuthModule(const QString &filePath)
{
    QFileInfo fileInfo(filePath);
    if (!fileInfo.exists()) {
        qDebug() << "Fichier introuvable :" << filePath;
        return;
    }

    QFile tokenFile("access_token.txt");
    if (!tokenFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Impossible de lire access_token.txt";
        return;
    }
    QString accessToken = tokenFile.readAll().trimmed();
    tokenFile.close();

    QFile *file = new QFile(filePath);
    if (!file->open(QIODevice::ReadOnly)) {
        qDebug() << "Impossible d'ouvrir le fichier.";
        return;
    }

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader,
                       QVariant("form-data; name=\"file\"; filename=\"" + fileInfo.fileName() + "\""));
    filePart.setBodyDevice(file);
    file->setParent(multiPart);

    QUrl url("https://www.googleapis.com/upload/drive/v3/files?uploadType=multipart");
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", "Bearer " + accessToken.toUtf8());

    QNetworkReply *reply = manager->post(request, multiPart);
    connect(reply, &QNetworkReply::finished, [reply]() {
        QByteArray response = reply->readAll();
        qDebug() << "[Réponse Google Drive]" << response;

        if (reply->error() == QNetworkReply::NoError)
            QMessageBox::information(nullptr, "✅ Upload", "Fichier sauvegardé sur Google Drive !");
        else
            QMessageBox::critical(nullptr, "❌ Erreur", reply->errorString());

        reply->deleteLater();
    });
}
