#ifndef FENETRECONTROLERFID_H
#define FENETRECONTROLERFID_H

#include <QDialog>
#include <QSerialPort>
#include <QCloseEvent>

namespace Ui {
class FenetreControleRFID;
}

class FenetreControleRFID : public QDialog
{
    Q_OBJECT

public:
    explicit FenetreControleRFID(QWidget *parent = nullptr);
    ~FenetreControleRFID();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void lireDonneesSerie();
    void ouvrirManuel();
    void fermerManuel();
    void lancerAlerte(const QString &message);

private:
    void enregistrerDansFichier(const QString &type, const QString &uid);

    Ui::FenetreControleRFID *ui;
    QSerialPort *serial;
    QString buffer;
    QString dernierUIDValide;
};

#endif // FENETRECONTROLERFID_H
