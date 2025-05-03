/********************************************************************************
** Form generated from reading UI file 'chatbotdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATBOTDIALOG_H
#define UI_CHATBOTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ChatBotDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTextEdit *chatTextEdit;
    QHBoxLayout *horizontalLayout;
    QLineEdit *messageEdit;
    QPushButton *sendButton;

    void setupUi(QDialog *ChatBotDialog)
    {
        if (ChatBotDialog->objectName().isEmpty())
            ChatBotDialog->setObjectName("ChatBotDialog");
        ChatBotDialog->resize(500, 600);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/chat_icon.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ChatBotDialog->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(ChatBotDialog);
        verticalLayout->setObjectName("verticalLayout");
        chatTextEdit = new QTextEdit(ChatBotDialog);
        chatTextEdit->setObjectName("chatTextEdit");
        chatTextEdit->setReadOnly(true);

        verticalLayout->addWidget(chatTextEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        messageEdit = new QLineEdit(ChatBotDialog);
        messageEdit->setObjectName("messageEdit");

        horizontalLayout->addWidget(messageEdit);

        sendButton = new QPushButton(ChatBotDialog);
        sendButton->setObjectName("sendButton");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/send_icon.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        sendButton->setIcon(icon1);

        horizontalLayout->addWidget(sendButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(ChatBotDialog);

        QMetaObject::connectSlotsByName(ChatBotDialog);
    } // setupUi

    void retranslateUi(QDialog *ChatBotDialog)
    {
        ChatBotDialog->setWindowTitle(QCoreApplication::translate("ChatBotDialog", "AI Assistant", nullptr));
        chatTextEdit->setHtml(QCoreApplication::translate("ChatBotDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        messageEdit->setPlaceholderText(QCoreApplication::translate("ChatBotDialog", "Type your message here...", nullptr));
        sendButton->setText(QCoreApplication::translate("ChatBotDialog", "Send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatBotDialog: public Ui_ChatBotDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATBOTDIALOG_H
