#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QDialog>
#include <QList>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSplitter>
#include <QScreen>
#include <QGuiApplication>
#include <QFrame>
#include <QCloseEvent>
#include "chatbotservice.h"
#include "etudiantservice.h"

class ChatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChatDialog(QWidget parent = nullptr);
    ~ChatDialog();

protected:
    // Override closeEvent to save conversation history
    void closeEvent(QCloseEventevent) override;

private slots:
    void sendMessage();
    void displayResponse(const QString &response);
    void displayError(const QString &errorMessage);
    void updateConversationDisplay();
    void clearChat();
    void exportChat();
    void testConnection();

private:
    void setupUi();
    void addMessageToChat(const QString &message, bool isUser);
    void loadPreviousConversation();
    void saveConversation();

    QTextEdit chatDisplay;
    QLineEditmessageInput;
    QPushButton sendButton;
    QPushButtonclearButton;
    QPushButton exportButton;
    QPushButtontestConnectionButton;
    QLabel statusLabel;

    ChatbotServicechatbotService;
    EtudiantService etudiantService;

    static const QString CHAT_HISTORY_FILE;
};

#endif // CHATDIALOG_H
