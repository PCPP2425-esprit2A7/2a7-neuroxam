#ifndef CHATBOTSERVICE_H
#define CHATBOTSERVICE_H

#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QObject>
#include <QList>
#include <QDateTime>
#include "etudiant.h"

// Structure to store a chat message
struct ChatMessage {
    QString text;
    bool isUser;
    QDateTime timestamp;
    
    ChatMessage(const QString &text, bool isUser)
        : text(text), isUser(isUser), timestamp(QDateTime::currentDateTime()) {}
};

class ChatbotService : public QObject
{
    Q_OBJECT

public:
    explicit ChatbotService(QObject *parent = nullptr);
    ~ChatbotService();

    // Send a message to the chatbot with student data
    void sendMessage(const QString &message, const QList<Etudiant> &studentData);
    
    // Set the API key
    void setApiKey(const QString &key);
    
    // Get conversation history (const version for read-only access)
    const QList<ChatMessage>& getConversationHistory() const { return conversationHistory; }
    
    // Add a message to conversation history
    void addMessageToHistory(const ChatMessage &message);
    
    // Clear conversation history
    void clearConversationHistory() { conversationHistory.clear(); }

signals:
    // Signal emitted when a response is received
    void responseReceived(const QString &response);
    
    // Signal emitted if there's an error
    void errorOccurred(const QString &errorMessage);
    
    // Signal emitted when history is updated
    void conversationHistoryUpdated();

private slots:
    void handleNetworkReply(QNetworkReply *reply);

private:
    QNetworkAccessManager *networkManager;
    QString apiKey;
    QList<ChatMessage> conversationHistory;
    
    // Format student data for the API
    QString formatStudentData(const QList<Etudiant> &students);
    
    // Format the conversation history for the API
    QString formatConversationHistory();
};

#endif // CHATBOTSERVICE_H 