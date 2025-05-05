#include "chatbotservice.h"
#include <QNetworkRequest>
#include <QUrl>
#include <QUrlQuery>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>

ChatbotService::ChatbotService(QObject *parent) : QObject(parent)
{
    networkManager = new QNetworkAccessManager(this);
    apiKey = "AIzaSyAhxwe-YYXay3DXsXdZMjfCwJ5M7pmveow"; // Default API key
    connect(networkManager, &QNetworkAccessManager::finished, this, &ChatbotService::handleNetworkReply);
}

ChatbotService::~ChatbotService()
{
    // QNetworkAccessManager will be automatically deleted by Qt's parent-child system
}

void ChatbotService::setApiKey(const QString &key)
{
    apiKey = key;
}

void ChatbotService::testApiConnection()
{
    if (apiKey.isEmpty()) {
        emit errorOccurred("API key is not set");
        return;
    }

    // Create the request URL with the API key
    QUrl url(QString("https://generativelanguage.googleapis.com/v1beta/models/gemini-2.0-flash:generateContent?key=%1")
             .arg(apiKey));
    
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Prepare a simple test request
    QJsonObject rootObject;
    QJsonArray contentsArray;
    
    QJsonObject messageObject;
    QJsonArray partsArray;
    QJsonObject textPart;
    
    textPart["text"] = "Test connection: Please respond with 'Connection successful'";
    partsArray.append(textPart);
    
    messageObject["role"] = "user";
    messageObject["parts"] = partsArray;
    
    contentsArray.append(messageObject);
    rootObject["contents"] = contentsArray;
    
    // Convert to JSON document
    QJsonDocument jsonDoc(rootObject);
    QByteArray jsonData = jsonDoc.toJson();
    
    qDebug() << "Sending test request to Gemini API: " << jsonData;
    
    // Send the request
    networkManager->post(request, jsonData);
}

void ChatbotService::sendMessage(const QString &message, const QList<Etudiant> &studentData)
{
    if (apiKey.isEmpty()) {
        emit errorOccurred("API key is not set");
        return;
    }

    // Add the message to conversation history
    ChatMessage userMessage(message, true);
    addMessageToHistory(userMessage);
    emit conversationHistoryUpdated();

    // Create the request URL with the API key
    QUrl url(QString("https://generativelanguage.googleapis.com/v1beta/models/gemini-2.0-flash:generateContent?key=%1")
             .arg(apiKey));
    
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Prepare the request body
    QJsonObject rootObject;
    QJsonArray contentsArray;
    
    // Construct the prompt with student data and conversation history
    QString dataContext = formatStudentData(studentData);
    QString historyContext = formatConversationHistory();
    
    // Add system prompt as the first message
    QJsonObject systemMessageObject;
    QJsonArray systemPartsArray;
    QJsonObject systemTextPart;
    
    QString systemPrompt = QString("You are an AI assistant that helps with student data. "
                                  "Here's the student data you have access to:\n%1\n\n"
                                  "Please maintain context of our conversation and remember previous questions and answers. "
                                  "Be helpful and concise in your responses.")
                             .arg(dataContext);
    
    systemTextPart["text"] = systemPrompt;
    systemPartsArray.append(systemTextPart);
    systemMessageObject["role"] = "system";
    systemMessageObject["parts"] = systemPartsArray;
    contentsArray.append(systemMessageObject);
    
    // Add conversation history as previous messages
    for (int i = 0; i < conversationHistory.size(); i++) {
        const ChatMessage &chatMessage = conversationHistory[i];
        
        QJsonObject messageObject;
        QJsonArray partsArray;
        QJsonObject textPart;
        
        textPart["text"] = chatMessage.text;
        partsArray.append(textPart);
        
        messageObject["role"] = chatMessage.isUser ? "user" : "model";
        messageObject["parts"] = partsArray;
        
        contentsArray.append(messageObject);
    }
    
    rootObject["contents"] = contentsArray;
    
    // Convert to JSON document
    QJsonDocument jsonDoc(rootObject);
    QByteArray jsonData = jsonDoc.toJson();
    
    qDebug() << "Sending request to Gemini API: " << jsonData;
    
    // Send the request
    networkManager->post(request, jsonData);
}

void ChatbotService::handleNetworkReply(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Network error: " << reply->errorString();
        emit errorOccurred("Network error: " + reply->errorString());
        reply->deleteLater();
        return;
    }
    
    QByteArray responseData = reply->readAll();
    qDebug() << "Received response: " << responseData;
    
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    QJsonObject jsonObj = jsonDoc.object();
    
    // Parse the Gemini API response
    if (jsonObj.contains("candidates") && jsonObj["candidates"].isArray()) {
        QJsonArray candidates = jsonObj["candidates"].toArray();
        if (!candidates.isEmpty()) {
            QJsonObject candidate = candidates.at(0).toObject();
            if (candidate.contains("content") && candidate["content"].isObject()) {
                QJsonObject content = candidate["content"].toObject();
                if (content.contains("parts") && content["parts"].isArray()) {
                    QJsonArray parts = content["parts"].toArray();
                    if (!parts.isEmpty() && parts.at(0).isObject()) {
                        QJsonObject part = parts.at(0).toObject();
                        if (part.contains("text") && part["text"].isString()) {
                            QString responseText = part["text"].toString();
                            
                            // Add the response to conversation history
                            ChatMessage responseMessage(responseText, false);
                            addMessageToHistory(responseMessage);
                            emit conversationHistoryUpdated();
                            
                            emit responseReceived(responseText);
                            reply->deleteLater();
                            return;
                        }
                    }
                }
            }
        }
    }
    
    // If we get here, we couldn't parse the response correctly
    qDebug() << "Invalid response format:" << responseData;
    emit errorOccurred("Invalid response format from AI service");
    reply->deleteLater();
}

QString ChatbotService::formatStudentData(const QList<Etudiant> &students)
{
    if (students.isEmpty()) {
        return "No student data available.";
    }
    
    QString formattedData = "Student Data:\n";
    int count = 1;
    
    for (const Etudiant &student : students) {
        formattedData += QString("Student %1:\n").arg(count);
        formattedData += QString("- ID: %1\n").arg(student.getId());
        formattedData += QString("- Name: %1\n").arg(student.getName());
        formattedData += QString("- Family Name: %1\n").arg(student.getFamilyName());
        formattedData += QString("- CIN: %1\n").arg(student.getCin());
        formattedData += QString("- Speciality: %1\n").arg(student.getSpeciality());
        formattedData += QString("- Note: %1\n").arg(student.getNote());
        formattedData += QString("- Gender: %1\n").arg(student.getGender());
        formattedData += QString("- Phone: %1\n").arg(student.getPhoneNumber());
        formattedData += QString("- Email: %1\n").arg(student.getEmail());
        formattedData += QString("- Birth Date: %1\n").arg(student.getBirthDate().toString("yyyy-MM-dd"));
        formattedData += "\n";
        count++;
        
        // Limit the number of students to prevent overwhelming the API
        if (count > 10) {
            formattedData += "... (more students available but not shown)\n";
            break;
        }
    }
    
    return formattedData;
}

QString ChatbotService::formatConversationHistory()
{
    QString history = "Conversation History:\n";
    
    for (const ChatMessage &message : conversationHistory) {
        QString role = message.isUser ? "User" : "AI";
        history += QString("[%1] %2: %3\n\n")
                .arg(message.timestamp.toString("hh:mm:ss"))
                .arg(role)
                .arg(message.text);
    }
    
    return history;
}

void ChatbotService::addMessageToHistory(const ChatMessage &message)
{
    conversationHistory.append(message);
    // Don't emit the signal here to avoid triggering UI updates when loading history
    // The caller should decide when to emit this signal
} 