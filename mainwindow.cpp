#include "mainwindow.h"
#include "ui_mainwindow.h"
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
#include "dialog.h"
#include <QFileDialog>
#include "examen.h"
#include "EmailDialog.h"
#include <QTextCharFormat>
#include <QBrush>
#include <QColor>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "connection.h"  // Ajoute cette ligne si 'Connection' est dans ce fichier
#include <QDateEdit>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupMap();

    // Initialize RecommendationSystem
    recommender = new RecommendationSystem(this);
    recommender->trainModel();  // Load and train the recommendation model

    centre c;  // Assuming centre is correctly set up
    QSqlQueryModel *model = c.afficher();
    qDebug() << "Nombre de centre :" << model->rowCount();
    ui->aff->setModel(model);
    loadCentresToMap();

}

// Inside MainWindow.cpp

void MainWindow::setupChatUI()
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
    QPushButton *sendButton = new QPushButton("Send", this);
    connect(sendButton, &QPushButton::clicked, this, &MainWindow::onChatSendClicked);

    // Exit button
    QPushButton *exitButton = new QPushButton("Exit", this);
    connect(exitButton, &QPushButton::clicked, this, &MainWindow::onExitChatClicked);

    // Layout
    chatLayout = new QVBoxLayout();
    chatLayout->addWidget(new QLabel("Centre Recommendation Chat", this));
    chatLayout->addWidget(chatDisplay);
    chatLayout->addWidget(chatInput);
    chatLayout->addWidget(sendButton);
    chatLayout->addWidget(exitButton);

    ui->verticalLayout_5->addLayout(chatLayout);
}

void MainWindow::onExitChatClicked()
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

void MainWindow::onChatSendClicked()
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

void MainWindow::displayRecommendations(const QVector<centre> &recommendations)
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

void MainWindow::setupMap()
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

void MainWindow::loadCentresToMap()
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

void MainWindow::onMapClicked(double latitude, double longitude)
{
    // Update the address field with coordinates
    QString coordinates = QString("%1, %2").arg(latitude).arg(longitude);
    ui->adresse_3->setText(coordinates);

    // You might want to update the current centre's coordinate
    c.setCoordinate(latitude, longitude);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::verifierNom()
{
    QString nom = ui->nom_3->text();
    QRegularExpression regex("^[A-Za-zÀ-ÖØ-öø-ÿ]+$");
    if (nom.isEmpty()) {
        ui->nomeror_3->clear();
    } else if (!regex.match(nom).hasMatch()) {
        ui->nomeror_3->setText("Le nom doit contenir uniquement des lettres.");
    } else {
        ui->nomeror_3->clear();
    }
}

void MainWindow::verifierads()
{
    QString adresse = ui->adresse_3->text().trimmed();
    if (adresse.isEmpty()) {
        ui->adseror_3->clear();
    } else {
        ui->adseror_3->clear();
    }
}

void MainWindow::verifierdtc()
{
    QString directeur = ui->directeur_3->text().trimmed();
    QRegularExpression regex("^[A-Za-zÀ-ÖØ-öø-ÿ]+$");
    if (directeur.isEmpty()) {
        ui->drteror_3->clear();
    } else if (!regex.match(directeur).hasMatch()) {
        ui->drteror_3->setText("Le nom de dir doit contenir uniquement des lettres.");
    } else {
        ui->drteror_3->clear();
    }
}

// You can add more slots for other UI interactions...



void MainWindow::on_ajoute_3_clicked()
{
    QString nom = ui->nom_3->text().trimmed();
    QString adresse = ui->adresse_3->text().trimmed();
    QString directeur = ui->directeur_3->text().trimmed();
    QString facilities = ui->facilities_3->text().trimmed();
    int status = ui->status_3->currentIndex();
    int capacite = ui->capacite_3->text().toInt();
    int temp = ui->temp_2->text().toInt();
    MainWindow::verifierNom();
    MainWindow::verifierdtc();
    MainWindow::verifierads();
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
        ui->cpteror_3->setText("La capacité doit être positive.");
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
    ui->nom_3->clear();
    ui->adresse_3->clear();
    ui->directeur_3->clear();
    ui->facilities_3->clear();
    ui->capacite_3->clear();
    ui->temp_2->clear();
}


void MainWindow::on_recuperer_clicked()
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
    ui->nom_3->setText(c.getNom());
    ui->adresse_3->setText(c.getAdresse());
    ui->directeur_3->setText(c.getDirecteur());
    ui->facilities_3->setText(c.getFacilities());
    ui->status_3->setCurrentIndex(c.getStatus());
    ui->capacite_3->setText(QString::number(c.getCapacite()));
    ui->temp_2->setText(QString::number(c.gettemp()));
}



void MainWindow::on_modifier_3_clicked()
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
    QString nom = ui->nom_3->text().trimmed();
    QString adresse = ui->adresse_3->text().trimmed();
    QString directeur = ui->directeur_3->text().trimmed();
    QString facilities = ui->facilities_3->text().trimmed();
    int status = ui->status_3->currentIndex();
    int capacite = ui->capacite_3->text().toInt();
    int temp = ui->temp_2->text().toInt();
    centre c;
    if (c.update(id, nom, adresse, directeur, facilities, status, capacite,temp)) {
        QMessageBox::information(this, "Succès", "Le centre a été modifié avec succès.");
        ui->aff->setModel(c.afficher());
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible de modifier le centre.");
    }
    ui->nom_3->clear();
    ui->adresse_3->clear();
    ui->directeur_3->clear();
    ui->facilities_3->clear();
    ui->capacite_3->clear();
    ui->temp_2->clear();
}


void MainWindow::on_sup_3_clicked()
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





void MainWindow::on_tri_3_clicked()
{
    centre c;
    QString critere = ui->trie_3->currentText().toLower();


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


void MainWindow::on_cherchebut_clicked()
{
    centre c;
    QString valeur = ui->cherche->text();

    QSqlQueryModel* model = c.rechercher(valeur);
    ui->aff->setModel(model);
}


void MainWindow::on_pdf_clicked()
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




void MainWindow::on_stat_clicked()
{
    centre c;
    QMap<QString, int> stats = c.obtenirStatistiques(); //rpatna rest requete bel affichage stat

    if (stats.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Impossible de récupérer les statistiques.");
        return;
    }

    // Créer une nouvelle fenêtre pour afficher le pie chart
    QMainWindow* statWindow = new QMainWindow(this);
    statWindow->setWindowTitle("Statistiques par poste");

    // Utiliser le PieChartWidget pour afficher les données
    PieChartWidget* chartWidget = new PieChartWidget(stats, statWindow);
    statWindow->setCentralWidget(chartWidget);

    // Afficher la fenêtre de statistiques
    statWindow->resize(600, 600);
    statWindow->show();
}



void MainWindow::on_next_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_back_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_chat_clicked()
{
    setupChatUI();
}




void MainWindow::on_ard_clicked()
{
    Dialog d;
    d.exec();

}


void MainWindow::on_pushButton_2_clicked()
{
    ui->groupBox_3->show();
    ui->groupBox_4->hide();
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_mexam_clicked()
{
    ui->groupBox_4->show();
    ui->groupBox_3->hide();

    // Initialize exam components
    ui->date_examen_2->setMinimumDate(QDate(2025, 1, 1));
    ui->date_examen_2->setMaximumDate(QDate(2030, 12, 31));
    mettreAJourCalendrier();

    // Load exam data
    QSqlQueryModel *modele = e.afficher();
    ui->aff_3->setModel(modele);

    // Ensure email button is connected
    if (!connect(ui->btn_ouvrirEmailDialog__2, &QPushButton::clicked,
                 this, &MainWindow::on_btn_ouvrirEmailDialog_clicked)) {
        qDebug() << "Failed to connect email button";
    }
}


void MainWindow::on_emp_clicked()
{

}


void MainWindow::on_etud_clicked()
{

}


void MainWindow::on_materl_clicked()
{

}


void MainWindow::on_formation_clicked()
{

}















void MainWindow::on_ajoute_4_clicked() {
    // Récupération des valeurs saisies
    QDate date_examen = ui->date_examen_2->date();
    QString heure_examen = ui->heure_examen_2->text().trimmed();
    QString matiere = ui->matiere_2->text().trimmed();
    QString type_examen = ui->type_examen_2->text().trimmed();
    QString centre_examen = ui->centre_examen_2->text().trimmed();
    QString email = ui->email_2->text().trimmed();

    // Vérification des champs obligatoires
    if (matiere.isEmpty() || type_examen.isEmpty() || centre_examen.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs obligatoires.");
        return;
    }

    // Vérification si un examen est déjà prévu pour cette date
    if (examen::existeExamenLeMemeJour(date_examen)) {
        QMessageBox::warning(this, "Date déjà réservée", "Un examen est déjà prévu à cette date. Veuillez choisir une autre date.");
        return;
    }

    // Création de l'objet examen
    examen newExamen(date_examen, heure_examen, matiere, type_examen, centre_examen, email);

    // Tentative d'ajout à la base de données
    if (newExamen.create()) {
        QMessageBox::information(this, "Succès", "L'examen a été ajouté avec succès !");
        ui->aff_3->setModel(newExamen.afficher());

        // Mise à jour du calendrier après ajout
        mettreAJourCalendrier();  // Appeler la fonction pour mettre à jour l'affichage
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout de l'examen.");
    }
}



void MainWindow::on_recuperer_3_clicked()
{
    QString idText = ui->idedit_3->text();

    bool ok;
    int id_examen = idText.toInt(&ok);

    if (!ok || id_examen <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide.");
        return;
    }

    if (!examen::exists(id_examen)) {
        QMessageBox::warning(this, "Erreur", "Examen non trouvé.");
        return;
    }

    examen e = examen::read(id_examen);
    ui->date_examen_2->setDate(e.getDateExamen());
    ui->heure_examen_2->setText(e.getHeureExamen());
    ui->matiere_2->setText(e.getMatiere());
    ui->type_examen_2->setText(e.getTypeExamen());
    ui->centre_examen_2->setText(e.getCentreExamen());
    ui->email_2->setText(e.getEmail());
}

void MainWindow::on_modifier_4_clicked()
{
    QString idText = ui->idedit_3->text();
    bool ok;
    int id_examen = idText.toInt(&ok);

    if (!ok || id_examen <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide.");
        return;
    }

    if (!examen::exists(id_examen)) {
        QMessageBox::warning(this, "Erreur", "Examen non trouvé.");
        return;
    }

    QDate date_examen = ui->date_examen_2->date();
    QString heure_examen = ui->heure_examen_2->text().trimmed();
    QString matiere = ui->matiere_2->text().trimmed();
    QString type_examen = ui->type_examen_2->text().trimmed();
    QString centre_examen = ui->centre_examen_2->text().trimmed();
    QString email = ui->email_2->text().trimmed();

    examen e;
    if (e.update(id_examen, date_examen, heure_examen, matiere, type_examen, centre_examen, email)) {
        QMessageBox::information(this, "Succès", "L'examen a été modifié avec succès.");
        ui->aff_3->setModel(e.afficher());
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible de modifier l'examen.");
    }
}

void MainWindow::on_sup_4_clicked()
{
    QString idText = ui->idedit_3->text();
    bool ok;
    int id_examen = idText.toInt(&ok);

    if (!ok || id_examen <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide.");
        return;
    }

    examen e;
    if (e.remove(id_examen)) {
        QMessageBox::information(this, "Succès", "Examen supprimé avec succès.");
        ui->aff_3->setModel(e.afficher());
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de la suppression de l'examen.");
    }
}

void MainWindow::on_tri_4_clicked()
{
    examen e;
    QString critere = ui->trie_4->currentText().toLower();

    if (critere == "id_examen") {
        critere = "id_examen";
    } else if (critere == "date_examen") {
        critere = "date_examen";
    }

    bool ascendant = true;
    QSqlQueryModel* model = e.trier(critere, ascendant);
    ui->aff_3->setModel(model);
}

void MainWindow::on_cherchebut_3_clicked()
{
    examen e;
    QString valeur = ui->cherche_3->text();

    QSqlQueryModel* model = e.rechercher(valeur);
    ui->aff_3->setModel(model);
}

void MainWindow::on_pdf_3_clicked()
{
    QString fichierPDF = QFileDialog::getSaveFileName(this, "Enregistrer le PDF", "", "*.pdf");

    if (!fichierPDF.isEmpty()) {
        if (!fichierPDF.endsWith(".pdf", Qt::CaseInsensitive)) {
            fichierPDF += ".pdf";
        }

        examen e;
        e.genererPDF(fichierPDF);
        QMessageBox::information(this, "Succès", "Le PDF a été généré avec succès.");
    } else {
        QMessageBox::warning(this, "Annulé", "La génération du PDF a été annulée.");
    }
}

void MainWindow::on_stat_3_clicked()
{
    examen e;
    QMap<QString, int> stats = e.obtenirStatistiques(); //rpatna rest requete bel affichage stat

    if (stats.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Impossible de récupérer les statistiques.");
        return;
    }

    // Créer une nouvelle fenêtre pour afficher le pie chart
    QMainWindow* statWindow = new QMainWindow(this);
    statWindow->setWindowTitle("Statistiques par poste");

    // Utiliser le PieChartWidget pour afficher les données
    PieChartWidget* chartWidget = new PieChartWidget(stats, statWindow);
    statWindow->setCentralWidget(chartWidget);

    // Afficher la fenêtre de statistiques
    statWindow->resize(600, 600);
    statWindow->show();

}

void MainWindow::on_btn_ouvrirEmailDialog_clicked()
{
    EmailDialog dialog(this);
    dialog.exec(); // Affiche la fenêtre modale
}
void MainWindow::mettreAJourCalendrier() {
    QSqlDatabase db = Connection::get_database();

    if (!db.isOpen()) {
        qDebug() << "❌ La base de données n'est pas ouverte.";
        return;
    }

    QSqlQuery query(db);
    if (!query.exec("SELECT date_examen FROM examen")) {
        qDebug() << "❌ Erreur dans la requête :" << query.lastError();
        return;
    }

    QTextCharFormat formatVert;
    formatVert.setBackground(QBrush(Qt::green));  // Fond vert pour la date
    formatVert.setForeground(QBrush(Qt::white));  // Texte blanc pour contraste

    bool hasDate = false;

    while (query.next()) {
        QDate date = query.value(0).toDate();  // Récupérer la date d'examen
        qDebug() << "✅ Date trouvée dans la base :" << date;
        ui->calendar_examen_2->setDateTextFormat(date, formatVert);  // Colorier la date en vert
        hasDate = true;
    }

    if (!hasDate) {
        qDebug() << "⚠️ Aucun examen trouvé dans la base.";
    }
}
void MainWindow::on_calendar_examen_2_clicked(const QDate &date) {
    // Vérifie si un examen est réservé pour la date sélectionnée
    if (examen::existeExamenLeMemeJour(date)) {
        QSqlDatabase db = Connection::get_database();

        if (!db.isOpen()) {
            qDebug() << "❌ La base de données n'est pas ouverte.";
            return;
        }

        // Récupérer les détails de l'examen pour cette date
        QSqlQuery query(db);
        query.prepare("SELECT matiere, centre_examen, heure_examen FROM examen WHERE date_examen = :date_examen");
        query.bindValue(":date_examen", date);

        if (!query.exec()) {
            qDebug() << "❌ Erreur lors de la requête pour récupérer les détails de l'examen :" << query.lastError();
            return;
        }

        if (query.next()) {
            QString matiere = query.value(0).toString();
            QString centre_examen = query.value(1).toString();
            QString heure_examen = query.value(2).toString();

            // Afficher un message avec les détails de l'examen
            QMessageBox::information(this, "Date réservée",
                                     "La date du " + date.toString("dd/MM/yyyy") + " est réservée pour l'examen de " + matiere +
                                         ".\nCentre: " + centre_examen + "\nHeure: " + heure_examen );
        }
    } else {
        // Si la date n'est pas réservée, afficher un message
        QMessageBox::information(this, "Date libre",
                                 "Aucun examen n'est réservé pour la date du " + date.toString("dd/MM/yyyy") + ".");
    }
}





