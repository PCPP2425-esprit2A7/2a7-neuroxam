#include "chatdialog.h"
#include <QDateTime>
#include <QScrollBar>
#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QStandardPaths>
#include <QDir>
#include <QFileDialog>
#include <QCloseEvent>
#include <QGuiApplication>
#include <QIcon>
#include <cmath>

// Define static constant for chat history file
const QString ChatDialog::CHAT_HISTORY_FILE = "student_chat_history.json";

ChatDialog::ChatDialog(QWidget *parent) : QDialog(parent)
{
    // Set up the UI components
    setupUi();
    
    // Initialize chatbot service
    chatbotService = new ChatbotService(this);
    
    // Connect signals and slots
    connect(sendButton, &QPushButton::clicked, this, &ChatDialog::sendMessage);
    connect(messageInput, &QLineEdit::returnPressed, this, &ChatDialog::sendMessage);
    connect(chatbotService, &ChatbotService::responseReceived, this, &ChatDialog::displayResponse);
    connect(chatbotService, &ChatbotService::errorOccurred, this, &ChatDialog::displayError);
    connect(chatbotService, &ChatbotService::conversationHistoryUpdated, this, &ChatDialog::updateConversationDisplay);
    connect(clearButton, &QPushButton::clicked, this, &ChatDialog::clearChat);
    connect(exportButton, &QPushButton::clicked, this, &ChatDialog::exportChat);
    
    // Load previous conversation if exists
    loadPreviousConversation();
    
    // If no previous conversation, add welcome message
    if (chatbotService->getConversationHistory().isEmpty()) {
        // Add welcome message
        QString welcomeMessage = "Bonjour! Je suis votre assistant IA. Je peux répondre à vos questions concernant les données des étudiants. Comment puis-je vous aider aujourd'hui?";
        addMessageToChat(welcomeMessage, false);
        
        // Also add to conversation history
        ChatMessage msg(welcomeMessage, false);
        chatbotService->addMessageToHistory(msg);
    }
    
    // Set window properties
    setWindowTitle("Assistant IA");
    resize(700, 500);
}

ChatDialog::~ChatDialog()
{
    // Save conversation on close
    saveConversation();
    
    // Qt will handle the memory cleanup through parent-child relationships
}

void ChatDialog::closeEvent(QCloseEvent *event)
{
    saveConversation();
    event->accept();
}

void ChatDialog::setupUi()
{
    // Set window position to bottom right corner
    QRect screenGeometry;
    
    // Use QGuiApplication and QScreen which are available in all modern Qt versions
    QScreen *screen = QGuiApplication::primaryScreen();
    if (screen) {
        screenGeometry = screen->availableGeometry();
    } else {
        // Fallback to a reasonable default if we can't get screen info
        screenGeometry = QRect(0, 0, 1024, 768);
    }

    int x = screenGeometry.width() - 400; // 400px width
    int y = screenGeometry.height() - 600; // 600px height
    
    // Ensure position is not negative
    x = std::max(0, x);
    y = std::max(0, y);
    
    setGeometry(x, y, 400, 600);
    
    // Set window flags for a chat-like window
    setWindowFlags(Qt::Window | Qt::WindowStaysOnTopHint | Qt::CustomizeWindowHint | 
                  Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint);
    
    // Main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(5, 5, 5, 5);
    mainLayout->setSpacing(5);
    
    // Header with title and status
    QHBoxLayout *headerLayout = new QHBoxLayout();
    QLabel *titleLabel = new QLabel("Assistant IA", this);
    titleLabel->setStyleSheet("QLabel { font-weight: bold; font-size: 14px; }");
    headerLayout->addWidget(titleLabel);
    
    statusLabel = new QLabel(this);
    statusLabel->setText("●");
    statusLabel->setStyleSheet("QLabel { color: green; font-size: 14px; }");
    statusLabel->setToolTip("Connecté");
    headerLayout->addWidget(statusLabel, 0, Qt::AlignRight);
    
    mainLayout->addLayout(headerLayout);
    
    // Add separator line
    QFrame *line = new QFrame(this);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    mainLayout->addWidget(line);
    
    // Chat display area with fixed-width messages
    chatDisplay = new QTextEdit(this);
    chatDisplay->setReadOnly(true);
    chatDisplay->setStyleSheet(
        "QTextEdit { background-color: #f8f9fa; border: 1px solid #ddd; border-radius: 5px; }"
    );
    chatDisplay->setMinimumHeight(400);
    
    // Set document CSS for chat styling
    chatDisplay->document()->setDefaultStyleSheet(
        "body { font-family: Arial, sans-serif; }"
        ".msg { margin-bottom: 10px; max-width: 80%; clear: both; }"
        ".user { float: right; background-color: #dcf8c6; padding: 8px; border-radius: 10px; }"
        ".ai { float: left; background-color: #f1f0f0; padding: 8px; border-radius: 10px; }"
        ".timestamp { font-size: 10px; color: gray; margin-top: 4px; }"
    );
    
    mainLayout->addWidget(chatDisplay, 1);
    
    // Input area with rounded corners
    QHBoxLayout *inputLayout = new QHBoxLayout();
    inputLayout->setSpacing(5);
    
    messageInput = new QLineEdit(this);
    messageInput->setPlaceholderText("Tapez votre message ici...");
    messageInput->setStyleSheet(
        "QLineEdit { border: 1px solid #ddd; border-radius: 18px; padding: 8px 15px; }"
    );
    inputLayout->addWidget(messageInput);
    
    sendButton = new QPushButton(this);
    sendButton->setIcon(QIcon::fromTheme("arrow-right", QIcon(":/icons/send.png")));
    sendButton->setToolTip("Envoyer");
    sendButton->setFixedSize(36, 36);
    sendButton->setStyleSheet(
        "QPushButton { background-color: #007bff; color: white; border-radius: 18px; }"
        "QPushButton:hover { background-color: #0069d9; }"
    );
    inputLayout->addWidget(sendButton);
    
    mainLayout->addLayout(inputLayout);
    
    // Bottom toolbar with additional options
    QHBoxLayout *toolbarLayout = new QHBoxLayout();
    
    clearButton = new QPushButton("Effacer", this);
    clearButton->setStyleSheet(
        "QPushButton { background: none; border: none; color: #dc3545; }"
        "QPushButton:hover { text-decoration: underline; }"
    );
    toolbarLayout->addWidget(clearButton);
    
    exportButton = new QPushButton("Exporter", this);
    exportButton->setStyleSheet(
        "QPushButton { background: none; border: none; color: #28a745; }"
        "QPushButton:hover { text-decoration: underline; }"
    );
    toolbarLayout->addWidget(exportButton);
    
    toolbarLayout->addStretch();
    
    mainLayout->addLayout(toolbarLayout);
    setLayout(mainLayout);
}

void ChatDialog::sendMessage()
{
    QString message = messageInput->text().trimmed();
    if (message.isEmpty()) {
        return;
    }
    
    // Display user message
    addMessageToChat(message, true);
    
    // Clear input field
    messageInput->clear();
    
    // Show "thinking" status
    statusLabel->setText("●");
    statusLabel->setStyleSheet("QLabel { color: orange; font-size: 14px; }");
    statusLabel->setToolTip("L'IA réfléchit...");
    
    // Get all students to provide context
    QList<Etudiant> students = etudiantService.getAll();
    
    // Send to chatbot
    chatbotService->sendMessage(message, students);
}

void ChatDialog::displayResponse(const QString &response)
{
    // Display AI response
    addMessageToChat(response, false);
    
    // Update status
    statusLabel->setText("●");
    statusLabel->setStyleSheet("QLabel { color: green; font-size: 14px; }");
    statusLabel->setToolTip("Connecté");
}

void ChatDialog::displayError(const QString &errorMessage)
{
    // Create HTML for error message
    QString html = QString(
        "<div style='margin: 10px 0; text-align: center;'>"
        "  <div style='color: red; font-weight: bold;'>Erreur: %1</div>"
        "</div>"
    ).arg(errorMessage.toHtmlEscaped());
    
    chatDisplay->append(html);
    
    // Update status indicator
    statusLabel->setText("●");
    statusLabel->setStyleSheet("QLabel { color: red; font-size: 14px; }");
    statusLabel->setToolTip("Erreur de connexion");
    
    // Scroll to bottom
    QScrollBar *scrollbar = chatDisplay->verticalScrollBar();
    scrollbar->setValue(scrollbar->maximum());
}

void ChatDialog::updateConversationDisplay()
{
    // This method can be used to reload the entire conversation if needed
    // For now, we're adding messages individually as they come in
    // We could implement a full refresh here if needed
}

void ChatDialog::clearChat()
{
    // Confirm with user
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Effacer la conversation", 
        "Êtes-vous sûr de vouloir effacer toute la conversation?",
        QMessageBox::Yes | QMessageBox::No
    );
    
    if (reply == QMessageBox::Yes) {
        // Clear the chat history
        chatbotService->clearConversationHistory();
        chatDisplay->clear();
        
        // Add welcome message
        QString welcomeMessage = "Conversation effacée. Comment puis-je vous aider aujourd'hui?";
        addMessageToChat(welcomeMessage, false);
        
        // Also add to conversation history
        ChatMessage msg(welcomeMessage, false);
        chatbotService->addMessageToHistory(msg);
        
        // Save the conversation (with just the welcome message)
        saveConversation();
    }
}

void ChatDialog::exportChat()
{
    QString filePath = QFileDialog::getSaveFileName(
        this, "Exporter la conversation", 
        QDir::homePath() + "/conversation.html", 
        "Fichiers HTML (*.html);;Fichiers texte (*.txt)"
    );
    
    if (filePath.isEmpty()) {
        return;
    }
    
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        
        if (filePath.endsWith(".html", Qt::CaseInsensitive)) {
            // Export as HTML
            stream << "<!DOCTYPE html>\n<html>\n<head>\n"
                   << "<meta charset=\"UTF-8\">\n"
                   << "<title>Conversation avec l'Assistant IA</title>\n"
                   << "<style>\n"
                   << "body { font-family: Arial, sans-serif; max-width: 800px; margin: 0 auto; padding: 20px; }\n"
                   << ".message { margin: 10px 0; padding: 10px; border-radius: 10px; }\n"
                   << ".user { background-color: #dcf8c6; margin-left: 50px; }\n"
                   << ".ai { background-color: #f1f0f0; margin-right: 50px; }\n"
                   << ".timestamp { font-size: 12px; color: gray; margin-bottom: 5px; }\n"
                   << "</style>\n</head>\n<body>\n"
                   << "<h1>Conversation avec l'Assistant IA</h1>\n"
                   << "<p>Exportée le " << QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss") << "</p>\n";
            
            const QList<ChatMessage>& history = chatbotService->getConversationHistory();
            for (const ChatMessage& msg : history) {
                QString cssClass = msg.isUser ? "user" : "ai";
                QString role = msg.isUser ? "Vous" : "Assistant IA";
                
                stream << "<div class=\"message " << cssClass << "\">\n"
                       << "  <div class=\"timestamp\">" << role << " - " << msg.timestamp.toString("hh:mm:ss") << "</div>\n"
                       << "  <div>" << msg.text.toHtmlEscaped().replace("\n", "<br>") << "</div>\n"
                       << "</div>\n";
            }
            
            stream << "</body>\n</html>";
        } else {
            // Export as plain text
            stream << "Conversation avec l'Assistant IA\n"
                   << "Exportée le " << QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss") << "\n\n";
            
            const QList<ChatMessage>& history = chatbotService->getConversationHistory();
            for (const ChatMessage& msg : history) {
                QString role = msg.isUser ? "Vous" : "Assistant IA";
                stream << "[" << msg.timestamp.toString("hh:mm:ss") << "] " << role << ":\n"
                       << msg.text << "\n\n";
            }
        }
        
        file.close();
        QMessageBox::information(this, "Exportation réussie", "La conversation a été exportée avec succès.");
    } else {
        QMessageBox::critical(this, "Erreur d'exportation", "Impossible d'exporter la conversation.");
    }
}

void ChatDialog::addMessageToChat(const QString &message, bool isUser)
{
    QString timestamp = QDateTime::currentDateTime().toString("hh:mm:ss");
    QString cssClass = isUser ? "user" : "ai";
    QString nameLabel = isUser ? "Vous" : "IA";
    
    QString html = QString(
        "<div class='msg %1'>"
        "  <div>%2</div>"
        "  <div class='timestamp'>%3 - %4</div>"
        "</div>"
        "<div style='clear: both;'></div>"
    ).arg(cssClass, message.toHtmlEscaped().replace("\n", "<br>"), nameLabel, timestamp);
    
    chatDisplay->append(html);
    
    // Scroll to bottom
    QScrollBar *scrollbar = chatDisplay->verticalScrollBar();
    scrollbar->setValue(scrollbar->maximum());
}

void ChatDialog::loadPreviousConversation()
{
    QString filePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + 
                      "/" + CHAT_HISTORY_FILE;
    
    QDir dir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    
    QFile file(filePath);
    if (file.exists() && file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        file.close();
        
        if (doc.isArray()) {
            QJsonArray array = doc.array();
            
            // Clear display before loading
            chatDisplay->clear();
            
            // Temporarily block signals to avoid triggering updates during loading
            chatbotService->blockSignals(true);
            
            for (int i = 0; i < array.size(); ++i) {
                QJsonObject msgObj = array[i].toObject();
                bool isUser = msgObj["isUser"].toBool();
                QString text = msgObj["text"].toString();
                QDateTime timestamp = QDateTime::fromString(msgObj["timestamp"].toString(), Qt::ISODate);
                
                // Create a message and add it to history
                ChatMessage msg(text, isUser);
                msg.timestamp = timestamp;
                chatbotService->addMessageToHistory(msg);
                
                // Use the new message display format
                QString cssClass = isUser ? "user" : "ai";
                QString nameLabel = isUser ? "Vous" : "IA";
                
                QString html = QString(
                    "<div class='msg %1'>"
                    "  <div>%2</div>"
                    "  <div class='timestamp'>%3 - %4</div>"
                    "</div>"
                    "<div style='clear: both;'></div>"
                ).arg(cssClass, text.toHtmlEscaped().replace("\n", "<br>"), 
                      nameLabel, timestamp.toString("hh:mm:ss"));
                
                chatDisplay->append(html);
            }
            
            // Unblock signals
            chatbotService->blockSignals(false);
            
            // Emit a single update after loading all messages
            emit chatbotService->conversationHistoryUpdated();
            
            // Scroll to bottom
            QScrollBar *scrollbar = chatDisplay->verticalScrollBar();
            scrollbar->setValue(scrollbar->maximum());
        }
    }
}

void ChatDialog::saveConversation()
{
    QString filePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + 
                      "/" + CHAT_HISTORY_FILE;
    
    QDir dir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QJsonArray array;
        
        const QList<ChatMessage>& history = chatbotService->getConversationHistory();
        for (const ChatMessage& msg : history) {
            QJsonObject msgObj;
            msgObj["isUser"] = msg.isUser;
            msgObj["text"] = msg.text;
            msgObj["timestamp"] = msg.timestamp.toString(Qt::ISODate);
            array.append(msgObj);
        }
        
        QJsonDocument doc(array);
        file.write(doc.toJson());
        file.close();
    }
} 