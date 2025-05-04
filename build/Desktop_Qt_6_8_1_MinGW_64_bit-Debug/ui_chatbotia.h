/********************************************************************************
** Form generated from reading UI file 'chatbotia.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATBOTIA_H
#define UI_CHATBOTIA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ChatbotIA
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelTitre;
    QLineEdit *lineEditInputQuestion;
    QHBoxLayout *horizontalLayoutButtons;
    QPushButton *btnEnvoyerQuestion;
    QPushButton *btnRecommander;
    QPushButton *btnCopierTexte;
    QPlainTextEdit *plainTextEditReponse;

    void setupUi(QDialog *ChatbotIA)
    {
        if (ChatbotIA->objectName().isEmpty())
            ChatbotIA->setObjectName("ChatbotIA");
        ChatbotIA->resize(620, 500);
        ChatbotIA->setStyleSheet(QString::fromUtf8("\n"
"QDialog {\n"
"    background-color: qlineargradient(x1:0, y1:0, x2:1, y2:1,\n"
"                      stop:0 #ecf0f1, stop:1 #d0e0f0);\n"
"    border-radius: 15px;\n"
"}\n"
"QLabel#labelTitre {\n"
"    font-size: 18pt;\n"
"    font-weight: bold;\n"
"    color: #2c3e50;\n"
"    padding: 10px;\n"
"    border-bottom: 2px solid #95a5a6;\n"
"}\n"
"QLineEdit {\n"
"    background-color: rgba(255, 255, 255, 0.8);\n"
"    font-size: 12pt;\n"
"    padding: 8px;\n"
"    border-radius: 10px;\n"
"    border: 1px solid #ccc;\n"
"}\n"
"QPushButton {\n"
"    font-weight: bold;\n"
"    font-size: 11pt;\n"
"    padding: 10px;\n"
"    border-radius: 8px;\n"
"    color: white;\n"
"}\n"
"QPushButton#btnEnvoyerQuestion {\n"
"    background-color: #3498db;\n"
"}\n"
"QPushButton#btnEnvoyerQuestion:hover {\n"
"    background-color: #2980b9;\n"
"}\n"
"QPushButton#btnRecommander {\n"
"    background-color: #27ae60;\n"
"}\n"
"QPushButton#btnRecommander:hover {\n"
"    background-color: #1e8449;\n"
"}\n"
"QPushButton#btnCopierTexte {"
                        "\n"
"    background-color: #e67e22;\n"
"}\n"
"QPushButton#btnCopierTexte:hover {\n"
"    background-color: #d35400;\n"
"}\n"
"QPlainTextEdit {\n"
"    background-color: rgba(255, 255, 255, 0.85);\n"
"    font-size: 11pt;\n"
"    border-radius: 10px;\n"
"    padding: 8px;\n"
"    border: 1px solid #bbb;\n"
"}\n"
"   "));
        verticalLayout = new QVBoxLayout(ChatbotIA);
        verticalLayout->setSpacing(15);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(20, 20, 20, 20);
        labelTitre = new QLabel(ChatbotIA);
        labelTitre->setObjectName("labelTitre");
        labelTitre->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelTitre);

        lineEditInputQuestion = new QLineEdit(ChatbotIA);
        lineEditInputQuestion->setObjectName("lineEditInputQuestion");
        lineEditInputQuestion->setMinimumHeight(40);

        verticalLayout->addWidget(lineEditInputQuestion);

        horizontalLayoutButtons = new QHBoxLayout();
        horizontalLayoutButtons->setObjectName("horizontalLayoutButtons");
        btnEnvoyerQuestion = new QPushButton(ChatbotIA);
        btnEnvoyerQuestion->setObjectName("btnEnvoyerQuestion");

        horizontalLayoutButtons->addWidget(btnEnvoyerQuestion);

        btnRecommander = new QPushButton(ChatbotIA);
        btnRecommander->setObjectName("btnRecommander");

        horizontalLayoutButtons->addWidget(btnRecommander);

        btnCopierTexte = new QPushButton(ChatbotIA);
        btnCopierTexte->setObjectName("btnCopierTexte");

        horizontalLayoutButtons->addWidget(btnCopierTexte);


        verticalLayout->addLayout(horizontalLayoutButtons);

        plainTextEditReponse = new QPlainTextEdit(ChatbotIA);
        plainTextEditReponse->setObjectName("plainTextEditReponse");
        plainTextEditReponse->setReadOnly(true);
        plainTextEditReponse->setMinimumHeight(250);

        verticalLayout->addWidget(plainTextEditReponse);


        retranslateUi(ChatbotIA);

        QMetaObject::connectSlotsByName(ChatbotIA);
    } // setupUi

    void retranslateUi(QDialog *ChatbotIA)
    {
        ChatbotIA->setWindowTitle(QCoreApplication::translate("ChatbotIA", "Assistant IA - Aide \303\240 la d\303\251cision", nullptr));
        labelTitre->setText(QCoreApplication::translate("ChatbotIA", "Posez une question ou demandez une recommandation :", nullptr));
        lineEditInputQuestion->setPlaceholderText(QCoreApplication::translate("ChatbotIA", "Ex : Quelle formation certifiante recommandez-vous ?", nullptr));
        btnEnvoyerQuestion->setText(QCoreApplication::translate("ChatbotIA", "Envoyer", nullptr));
        btnRecommander->setText(QCoreApplication::translate("ChatbotIA", "Recommandations IA", nullptr));
        btnCopierTexte->setText(QCoreApplication::translate("ChatbotIA", "Copier", nullptr));
        plainTextEditReponse->setPlaceholderText(QCoreApplication::translate("ChatbotIA", "R\303\251ponse de l'IA ici...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatbotIA: public Ui_ChatbotIA {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATBOTIA_H
