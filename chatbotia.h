#ifndef CHATBOTIA_H
#define CHATBOTIA_H

#include <QDialog>

namespace Ui {
class ChatbotIA;
}

class ChatbotIA : public QDialog
{
    Q_OBJECT

public:
    explicit ChatbotIA(QWidget *parent = nullptr);
    ~ChatbotIA();

private slots:
    void on_btnEnvoyerQuestion_clicked();     //  Envoyer une question manuelle
    void on_btnRecommander_clicked();         //  Recommandations IA
    void on_btnCopierTexte_clicked();         //  Copier la réponse

private:
    Ui::ChatbotIA *ui;
    void envoyerPromptIA(const QString &texte); //  Fonction d'envoi vers OpenRouter
    QString genererPromptDepuisBase();          // 🗂 Génère prompt avec les sujets de formation
};

#endif // CHATBOTIA_H
