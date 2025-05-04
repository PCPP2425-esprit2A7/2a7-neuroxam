#include "centrewindow.h"
#include "ui_centrewindow.h"
#include <QMessageBox>
#include <QString>
#include <QFileDialog>
#include <QTextList>
#include <QTextEdit>
#include "centre.h"
#include "recommendation.h"
#include "piechartwidget.h"
#include <QQmlContext>
#include <QQuickItem>
#include "tmpdialog.h"
#include <QDialog>
#include <QMessageBox>
#include <QQuickWidget>

centrewindow::centrewindow(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::centrewindow)
{
    ui->setupUi(this);
    setupMap();

    // Initialize RecommendationSystem
    RecommendationSystem recommender;
    recommender.trainModel();  // Load and train the recommendation model

    centre c;  // Assuming centre is correctly set up
    QSqlQueryModel *model = c.afficher();
    qDebug() << "Nombre de centre :" << model->rowCount();
    ui->aff->setModel(model);
    loadCentresToMap();
}

centrewindow::~centrewindow()
{
    delete ui;
}

// Inside centrewindow.cpp

void centrewindow::setupChatUI()
{
    // Prevent duplicate UI setup
    if (chatLayout != nullptr) return;

    // Create the chat input
    QTextEdit *chatInput = new QTextEdit(this);
    chatInput->setObjectName("chatInput");
    chatInput->setPlaceholderText("Describe what you're looking for in a centre...");
    chatInput->setMaximumHeight(100);

    // Create the chat display
    QTextEdit *chatDisplay = new QTextEdit(this);
    chatDisplay->setObjectName("chatDisplay");
    chatDisplay->setReadOnly(true);

    // Send button
    QPushButton *sencentrewindowutton = new QPushButton("Send", this);
    connect(sencentrewindowutton, &QPushButton::clicked, this, &centrewindow::onChatSendClicked);

    // Exit button
    QPushButton *exitButton = new QPushButton("Exit", this);
    connect(exitButton, &QPushButton::clicked, this, &centrewindow::onExitChatClicked);

    // Layout
    chatLayout = new QVBoxLayout();
    chatLayout->addWidget(new QLabel("Centre Recommendation Chat", this));
    chatLayout->addWidget(chatDisplay);
    chatLayout->addWidget(chatInput);
    chatLayout->addWidget(sencentrewindowutton);
    chatLayout->addWidget(exitButton);

    ui->verticalLayout_5->addLayout(chatLayout);
}

void centrewindow::onExitChatClicked()
{
    if (chatLayout) {
        QLayoutItem *child;
        while ((child = chatLayout->takeAt(0)) != nullptr) {
            if (child->widget()) {
                child->widget()->deleteLater();
            }
            delete child;
        }
        delete chatLayout;
        chatLayout = nullptr;
    }
}

void centrewindow::onChatSendClicked()
{
    qDebug() << "Send button clicked";

    // Find widgets by name
    QTextEdit *chatInput = findChild<QTextEdit*>("chatInput");
    QTextEdit *chatDisplay = findChild<QTextEdit*>("chatDisplay");

    if (!chatInput || !chatDisplay) {
        qDebug() << "Could not find chat input or display!";
        return;
    }

    QString userMessage = chatInput->toPlainText();
    if (userMessage.isEmpty()) return;

    // Display user message
    chatDisplay->append("<b>You:</b> " + userMessage);
    chatInput->clear();

    // Get recommendations from the recommender
    QVector<centre> recommendations = recommender->recommendCentres(userMessage);

    qDebug() << "Number of recommendations: " << recommendations.size();

    displayRecommendations(recommendations);
}

void centrewindow::displayRecommendations(const QVector<centre> &recommendations)
{
    QTextEdit *chatDisplay = findChild<QTextEdit*>();

    if (recommendations.isEmpty()) {
        chatDisplay->append("<b>System:</b> No matching centres found. Please try a different description.");
        return;
    }

    chatDisplay->append("<b>System:</b> Here are the top matching centres:");

    for (const centre &c : recommendations) {
        QString message = QString("<b>%1</b><br>"
                                  "Address: %2<br>"
                                  "Director: %3<br>"
                                  "Facilities: %4<br>"
                                  "Capacity: %5<br>"
                                  "Status: %6")
                              .arg(c.getNom())
                              .arg(c.getAdresse())
                              .arg(c.getDirecteur())
                              .arg(c.getFacilities())
                              .arg(c.getCapacite())
                              .arg(c.getStatus() == 0 ? "Closed" : "Open");

        chatDisplay->append(message);
    }
}

void centrewindow::setupMap()
{
    mapWidget = new QQuickWidget(this);
    mapWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    mapWidget->setSource(QUrl("qrc:/map.qml"));

    if (mapWidget->status() != QQuickWidget::Ready) {
        qDebug() << "Error loading QML file:" << mapWidget->errors();
        return;
    }

    // Add map to your UI layout
    ui->verticalLayout_6->insertWidget(0, mapWidget);

    // Connect signals
    QObject::connect(mapWidget->rootObject(), SIGNAL(mapClicked(double, double)),
                     this, SLOT(onMapClicked(double, double)));
}

void centrewindow::loadCentresToMap()
{
    QList<QPair<QString, QGeoCoordinate>> centres = centre::getAllCoordinates();
    QObject *rootObject = mapWidget->rootObject();

    // Create a QVariantList of markers
    QVariantList markers;
    for (const auto &centre : centres) {
        QVariantMap marker;
        marker["lat"] = centre.second.latitude();
        marker["lon"] = centre.second.longitude();
        marker["title"] = centre.first;
        markers.append(marker);
    }

    // Call the QML function
    QMetaObject::invokeMethod(rootObject, "addMarkers",
                              Q_ARG(QVariant, QVariant::fromValue(markers)));
}

void centrewindow::onMapClicked(double latitude, double longitude)
{
    // Update the address field with coordinates
    QString coordinates = QString("%1, %2").arg(latitude).arg(longitude);
    ui->adresse_2->setText(coordinates);

    // You might want to update the current centre's coordinate
    c.setCoordinate(latitude, longitude);
}



void centrewindow::verifierNom()
{
    QString nom = ui->nom_2->text();
    QRegularExpression regex("^[A-Za-zÀ-ÖØ-öø-ÿ]+$");
    if (nom.isEmpty()) {
        ui->nomeror_2->clear();
    } else if (!regex.match(nom).hasMatch()) {
        ui->nomeror_2->setText("Le nom doit contenir uniquement des lettres.");
    } else {
        ui->nomeror_2->clear();
    }
}

void centrewindow::verifierads()
{
    QString adresse = ui->adresse_2->text().trimmed();
    if (adresse.isEmpty()) {
        ui->adseror_2->clear();
    } else {
        ui->adseror_2->clear();
    }
}

void centrewindow::verifierdtc()
{
    QString directeur = ui->directeur_2->text().trimmed();
    QRegularExpression regex("^[A-Za-zÀ-ÖØ-öø-ÿ]+$");
    if (directeur.isEmpty()) {
        ui->drteror_2->clear();
    } else if (!regex.match(directeur).hasMatch()) {
        ui->drteror_2->setText("Le nom de dir doit contenir uniquement des lettres.");
    } else {
        ui->drteror_2->clear();
    }
}

// You can add more slots for other UI interactions...



void centrewindow::on_ajoute_2_clicked()
{
    QString nom = ui->nom_2->text().trimmed();
    QString adresse = ui->adresse_2->text().trimmed();
    QString directeur = ui->directeur_2->text().trimmed();
    QString facilities = ui->facilities_2->text().trimmed();
    int status = ui->status_2->currentIndex();
    int capacite = ui->capacite_2->text().toInt();
    int temp = ui->temp->text().toInt();
    centrewindow::verifierNom();
    centrewindow::verifierdtc();
    centrewindow::verifierads();
    if (nom.isEmpty() || adresse.isEmpty() || directeur.isEmpty() || facilities.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs obligatoires.");
        return;
    }

    int s =0;
    QRegularExpression regex("^[A-Za-zÀ-ÖØ-öø-ÿ]+$");
    if (!regex.match(nom).hasMatch()) {
        s=1;
    }


    if (capacite <= 0) {
        ui->cpteror_2->setText("La capacité doit être positive.");
        s=1;
    }
    if (s==1){
        return;
    }
    centre newCentre(nom, adresse, directeur, facilities, status, capacite,temp);

    if (newCentre.create()) {
        QMessageBox::information(this, "Succès", "Le centre a été ajouté avec succès !");
        ui->aff->setModel(newCentre.afficher());
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout du centre.");
    }
    ui->nom_2->clear();
    ui->adresse_2->clear();
    ui->directeur_2->clear();
    ui->facilities_2->clear();
    ui->capacite_2->clear();
    ui->temp->clear();
}


void centrewindow::on_recuperer_clicked()
{
    QString idText = ui->idedit->text();

    bool ok;
    int id = idText.toInt(&ok);


    if (!ok || id <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide.");
        return;
    }

    if (!centre::exists(id)) {
        QMessageBox::warning(this, "Erreur", "Centre non trouvé.");
        return;
    }
    centre c = centre::read(id);
    ui->nom_2->setText(c.getNom());
    ui->adresse_2->setText(c.getAdresse());
    ui->directeur_2->setText(c.getDirecteur());
    ui->facilities_2->setText(c.getFacilities());
    ui->status_2->setCurrentIndex(c.getStatus());
    ui->capacite_2->setText(QString::number(c.getCapacite()));
    ui->temp->setText(QString::number(c.gettemp()));
}



void centrewindow::on_modifier_2_clicked()
{
    QString idText = ui->idedit->text();
    bool ok;
    int id = idText.toInt(&ok);
    if (!ok || id <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide.");
        return;
    }
    if (!centre::exists(id)) {
        QMessageBox::warning(this, "Erreur", "Centre non trouvé.");
        return;
    }
    QString nom = ui->nom_2->text().trimmed();
    QString adresse = ui->adresse_2->text().trimmed();
    QString directeur = ui->directeur_2->text().trimmed();
    QString facilities = ui->facilities_2->text().trimmed();
    int status = ui->status_2->currentIndex();
    int capacite = ui->capacite_2->text().toInt();
    int temp = ui->temp->text().toInt();
    centre c;
    if (c.update(id, nom, adresse, directeur, facilities, status, capacite,temp)) {
        QMessageBox::information(this, "Succès", "Le centre a été modifié avec succès.");
        ui->aff->setModel(c.afficher());
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible de modifier le centre.");
    }
    ui->nom_2->clear();
    ui->adresse_2->clear();
    ui->directeur_2->clear();
    ui->facilities_2->clear();
    ui->capacite_2->clear();
    ui->temp->clear();
}


void centrewindow::on_sup_clicked()
{
    QString idText = ui->idedit->text();

    bool ok;
    int id = idText.toInt(&ok);

    if (!ok || id <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide.");
        return;
    }

    centre c;
    if (c.remove(id)) {
        QMessageBox::information(this, "Succès", "centre supprimé avec succès.");
        ui->aff->setModel(c.afficher());


    } else {
        QMessageBox::warning(this, "Erreur", "Échec de la suppression de le centre.");
    }
}





void centrewindow::on_tri_clicked()
{
    centre c;
    QString critere = ui->trie->currentText().toLower();


    if (critere == "id") {
        critere = "id";
    } else if (critere == "status") {
        critere = "status";
    } else if (critere == "capacite") {
        critere = "capacite";
    }

    bool ascendant = true;
    QSqlQueryModel* model = c.trier(critere, ascendant);
    ui->aff->setModel(model);
}


void centrewindow::on_cherchebut_clicked()
{
    centre c;
    QString valeur = ui->cherche->text();

    QSqlQueryModel* model = c.rechercher(valeur);
    ui->aff->setModel(model);
}


void centrewindow::on_pdf_clicked()
{
    QString fichierPDF = QFileDialog::getSaveFileName(this, "Enregistrer le PDF", "", "*.pdf");

    if (!fichierPDF.isEmpty()) {
        if (!fichierPDF.endsWith(".pdf", Qt::CaseInsensitive)) {
            fichierPDF += ".pdf";
        }

        centre c;
        c.genererPDF(fichierPDF);
        QMessageBox::information(this, "Succès", "Le PDF a été généré avec succès.");
    } else {
        QMessageBox::warning(this, "Annulé", "La génération du PDF a été annulée.");
    }
}




void centrewindow::on_stat_clicked()
{
    centre c;
    QMap<QString, int> stats = c.obtenirStatistiques();

    if (stats.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Impossible de récupérer les statistiques.");
        return;
    }

    // Créer une nouvelle fenêtre de type QDialog
    QDialog* statWindow = new QDialog(this);
    statWindow->setWindowTitle("Statistiques par poste");

    // Créer le widget du graphique
    PieChartWidget* chartWidget = new PieChartWidget(stats, statWindow);

    // Appliquer un layout
    QVBoxLayout* layout = new QVBoxLayout(statWindow);
    layout->addWidget(chartWidget);
    statWindow->setLayout(layout);

    // Afficher la fenêtre
    statWindow->resize(600, 600);
    statWindow->exec();  // Or .show() if you prefer modeless
}




void centrewindow::on_next_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void centrewindow::on_back_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
}


void centrewindow::on_chat_clicked()
{
    setupChatUI();
}




void centrewindow::on_ard_clicked()
{
    TDialog td;
    td.exec();
}

