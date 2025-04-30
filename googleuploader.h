#ifndef GOOGLEUPLOADER_H
#define GOOGLEUPLOADER_H

#include <QObject>
#include <QNetworkAccessManager>

class GoogleUploader : public QObject
{
    Q_OBJECT

public:
    explicit GoogleUploader(QObject *parent = nullptr);
    void uploadWithoutAuthModule(const QString &filePath);

private:
    QNetworkAccessManager *manager;
};

#endif // GOOGLEUPLOADER_H
