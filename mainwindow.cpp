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
#include "tmpdialog.h"
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
#include <QDate>
#include <QRegularExpression>
#include "employe.h"
#include <QFileDialog>
#include <QVBoxLayout>

#include "dialogid.h"
#include "qrcodegen.hpp"
#include "chatbotia.h"
#include "fenetrecontrolerfid.h"
#include "fenetrestatsf.h"




#include "formation.h"
#include "dialogid.h"
#include <QMessageBox>
#include <QPainter>
#include <QDate>
#include <QDir>
#include <QPixmap>
#include <QFileDialog>
#include <QMetaType>
#include <QHeaderView>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "chatbotia.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrlQuery>
#include "qrcodegen.hpp"
#include <QFile>
#include <QCryptographicHash>
#include <QDateTime>
#include <QPdfDocument>
#include <QPdfPageRenderer>
#include <QImage>
#include <QPdfWriter>
#include <QTextDocument>
#include <QDesktopServices>
#include <QRegularExpression>
#include <QSqlQuery>
#include <QSqlError>  // (Optionnel : pour afficher l'erreur SQL en cas d'échec)
#include "fenetresignatures.h"
#include "todolist.h"
#include "ui_dialogrecherche.h"
#include "fenetrescanbadges.h"
#include "fenetrecontrolerfid.h"
#include "historiquebadges.h"

#include "deplome.h"

//

#include "qrcodegen.hpp"
using qrcodegen::QrCode;
using qrcodegen::QrSegment;

class DateDelegate : public QStyledItemDelegate {
public:
    DateDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    QString displayText(const QVariant &value, const QLocale &locale) const override {
        if (value.canConvert<QDateTime>()) {
            return value.toDateTime().date().toString("dd/MM/yyyy");
        } else if (value.canConvert<QDate>()) {
            return value.toDate().toString("dd/MM/yyyy");
        }
        return QStyledItemDelegate::displayText(value, locale);
    }
};



class TimeDelegate : public QStyledItemDelegate {
public:
    TimeDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    QString displayText(const QVariant &value, const QLocale &locale) const override {
        // Si c'est un QTime, on affiche au format HH:mm
        if (value.canConvert<QTime>()) {
            return value.toTime().toString("HH:mm");
        }

        // Si c'est une chaîne de type "09/04/2025 03:05", on coupe pour ne garder que l'heure
        QString str = value.toString();
        if (str.contains(" ")) {
            return str.split(" ").value(1); // Garde "03:05"
        }

        return str;
    }
};
//







MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btnCertificat, &QPushButton::clicked, this, &MainWindow::on_btnCertificat_clicked);

    setupMap();

    // Initialize RecommendationSystem
    recommender = new RecommendationSystem(this);
    recommender->trainModel();  // Load and train the recommendation model

    centre c;  // Assuming centre is correctly set up
    QSqlQueryModel *model = c.afficher();
    qDebug() << "Nombre de centre :" << model->rowCount();
    ui->aff->setModel(model);
    loadCentresToMap();
    ui->groupBox_3->show();
    ui->groupBox_4->hide();
    ui->groupBox_5->hide();
    ui->groupBox_6->hide();
    ui->comboBoxValeur->hide();
     ui->btnVerifier->hide();
    ui->stackedWidget->setCurrentIndex(0);
    ui->graphicsViewStats->hide();
    ui->tabAffichage->tabBar()->setTabVisible(ui->tabAffichage->indexOf(ui->tabStats), false);

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
    TDialog d;
    d.exec();

}


void MainWindow::on_pushButton_2_clicked()
{
    ui->groupBox_3->show();
    ui->groupBox_4->hide();
    ui->groupBox_5->hide();
    ui->groupBox_6->hide();
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_mexam_clicked()
{
    ui->groupBox_4->show();
    ui->groupBox_3->hide();
    ui->groupBox_5->hide();
    ui->groupBox_6->hide();

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
    ui->groupBox_5->show();
    ui->groupBox_3->hide();
    ui->groupBox_4->hide();
    ui->groupBox_6->hide();
    employe ep;
    QSqlQueryModel *model =ep.afficher(); // Ensure to create a new instance of employe
    qDebug() << "Nombre d'employés :" << model->rowCount();
    ui->aff_5->setModel(model);
}


void MainWindow::on_etud_clicked()
{

}


void MainWindow::on_materl_clicked()
{

}


void MainWindow::on_formation_clicked()
{
    ui->groupBox_5->hide();
    ui->groupBox_3->hide();
    ui->groupBox_4->hide();
    ui->groupBox_6->show();

    // 🔹 Configuration TableView
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 🔹 Charger les formations existantes
    refreshTable();

    // 🔹 Initialisation de l'ordre de tri
    ui->comboBoxOrdre->setCurrentIndex(0);  // Croissant par défaut
    dessinerStatistiques();

    // 🔹 Gestion du tri (exemple simple basé sur DATE_FORMATION)
    connect(ui->comboBoxTri, &QComboBox::currentTextChanged, this, [=](const QString &text){
        ui->comboBoxValeur->clear();
        ui->comboBoxValeur->setEnabled(false);
        ui->comboBoxOrdre->setEnabled(text == "DATE_FORMATION");
    });

    // 🔹 Rafraîchir la table à chaque retour sur l'onglet principal
    connect(ui->tabAffichage, &QTabWidget::currentChanged, this, [=](int index) {
        if (ui->tabAffichage->widget(index)->objectName() == "tabAff") {
            refreshTable();
            dessinerStatistiques();
        }
    });

    // 🔹 Connexions pour les fonctionnalités additionnelles
    connect(ui->btnVerifier, &QPushButton::clicked, this, &MainWindow::on_btnVerifier_clicked);
    connect(ui->btnVerifier, &QPushButton::clicked, this, &MainWindow::on_btnVerifier1_clicked);
    connect(ui->btnViderBase, &QPushButton::clicked, this, &MainWindow::viderBaseFormations);
    connect(ui->btnOngletSignatures, &QPushButton::clicked, this, &MainWindow::on_btnOngletSignatures_clicked);
    connect(ui->btnTodo, &QPushButton::clicked, this, &MainWindow::on_btnTodo_clicked);
    connect(ui->btnHistoriqueBadges, &QPushButton::clicked, this, &MainWindow::on_btnVoirHistorique_clicked);
    connect(ui->btnstat, &QPushButton::clicked, this, &MainWindow::on_btnStat_clicked);



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











void MainWindow::verifierNomp()
{
    QString nom = ui->nom->text();
    QRegularExpression regex("^[A-Za-zÀ-ÖØ-öø-ÿ]+$");
    if (nom.isEmpty()) {
        ui->lineEdit->clear();
    } else if (!regex.match(nom).hasMatch()) {
        ui->lineEdit->setText("Le nom doit contenir uniquement des lettres.");
    } else {
        ui->lineEdit->clear();
    }
}

void MainWindow::verifierNumeroTelephone()
{
    QString telephone = ui->numero_telephone1->text();
    if (telephone.isEmpty()) {
        ui->telephoneError->clear();
    } else if (!telephone.startsWith('+') && telephone.length() < 10) {
        ui->telephoneError->setText("Le numéro de téléphone est invalide.");
    } else {
        ui->telephoneError->clear();
    }
}

void MainWindow::on_ajoute_clicked()
{
    QString nom = ui->nom->text().trimmed();
    QString prenom = ui->prenom->text().trimmed();
    QString numero_telephone = ui->numero_telephone->text().trimmed();
    QString email = ui->email->text().trimmed();
    QString password = ui->password->text().trimmed();
    QDate date_dembauche = ui->date_dembauche->date();

    verifierNomp();
    verifierNumeroTelephone();

    if (nom.isEmpty() || prenom.isEmpty() || numero_telephone.isEmpty() || email.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs obligatoires.");
        return;
    }

    employe newEmploye(nom, prenom, numero_telephone, email, password, date_dembauche);

    if (newEmploye.create()) {
        QMessageBox::information(this, "Succès", "L'employé a été ajouté avec succès !");
        ui->aff_5->setModel(newEmploye.afficher());
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout de l'employé.");
    }
}

void MainWindow::on_recuperer_5_clicked()
{
    QString idText = ui->idedit_5->text();
    bool ok;
    int id = idText.toInt(&ok);

    if (!ok || id <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide.");
        return;
    }

    if (!employe::exists(id)) {
        QMessageBox::warning(this, "Erreur", "Employé non trouvé.");
        return;
    }

    employe e = employe::read(id);
    ui->nom->setText(e.getNom());
    ui->prenom->setText(e.getPrenom());
    ui->numero_telephone->setText(e.getNumeroTelephone());
    ui->email->setText(e.getEmail());
    ui->password->setText(e.getPassword());
    ui->date_dembauche->setDate(e.getDateDembauche());
}

void MainWindow::on_modifier_clicked()
{
    QString idText = ui->idedit_5->text();
    bool ok;
    int id = idText.toInt(&ok);
    if (!ok || id <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide.");
        return;
    }
    if (!employe::exists(id)) {
        QMessageBox::warning(this, "Erreur", "Employé non trouvé.");
        return;
    }

    QString nom = ui->nom->text().trimmed();
    QString prenom = ui->prenom->text().trimmed();
    QString numero_telephone = ui->numero_telephone->text().trimmed();
    QString email = ui->email->text().trimmed();
    QString password = ui->password->text().trimmed();
    QDate date_dembauche = ui->date_dembauche->date();

    employe e;
    if (e.update(id, nom, prenom, numero_telephone, email, password, date_dembauche)) {
        QMessageBox::information(this, "Succès", "L'employé a été modifié avec succès.");
        ui->aff_5->setModel(e.afficher());
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible de modifier l'employé.");
    }
}

void MainWindow::on_supprimer_clicked()
{
    QString idText = ui->idedit_5->text();
    bool ok;
    int id = idText.toInt(&ok);

    if (!ok || id <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide.");
        return;
    }

    employe e;

    if (employe::remove(id))
    {
        QMessageBox::information(this, "Succès", "Employé supprimé avec succès.");
        ui->aff_5->setModel(e.afficher());
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de la suppression de l'employé.");
    }
}
void MainWindow::on_tri_clicked()
{
    employe e;
    QString critere = ui->trie->currentText().toLower();

    if (critere == "id") {
        critere = "id";
    } else if (critere == "date_deambauche") {
        critere = "date_deambauche";
    }

    bool ascendant = true;
    QSqlQueryModel* model = e.trier(critere, ascendant);
    ui->aff_5->setModel(model);
}

void MainWindow::on_cherchebut_5_clicked()
{
    employe e;
    QString valeur = ui->cherche_5->text();

    QSqlQueryModel* model = e.rechercher(valeur);
    ui->aff_5->setModel(model);
}

void MainWindow::on_pdf_5_clicked()
{
    QString fichierPDF = QFileDialog::getSaveFileName(this, "Enregistrer le PDF", "", "*.pdf");

    if (!fichierPDF.isEmpty()) {
        if (!fichierPDF.endsWith(".pdf", Qt::CaseInsensitive)) {
            fichierPDF += ".pdf";
        }

        employe e;
        e.genererPDF(fichierPDF);
        QMessageBox::information(this, "Succès", "Le PDF a été généré avec succès.");
    } else {
        QMessageBox::warning(this, "Annulé", "La génération du PDF a été annulée.");
    }
}
void MainWindow::on_stat_5_clicked()
{
    employe e;
    QMap<QString, int> stats = e.obtenirStatistiques();

    if (stats.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Aucune donnée statistique disponible.");
        return;
    }

    QDialog statDialog(this);
    statDialog.setWindowTitle("Statistiques des ressources");
    statDialog.resize(600, 600);

    PieChartWidget* chartWidget = new PieChartWidget(stats, &statDialog);
    QVBoxLayout layout(&statDialog);
    layout.addWidget(chartWidget);

    statDialog.exec();
}












//formation
void MainWindow::on_btnAjouter_clicked()
{
    QString sujet = ui->lineEditSujet->text().trimmed();
    QDate date = ui->dateEdit->date();
    QTime heure = ui->timeEdit->time();
    int duree = ui->spinBoxDuree->value();
    QString statut = ui->comboStatut->currentText();
    QString nom_formateur = ui->lineEditFormateur->text().trimmed();
    QString nom_centre = ui->lineEditCentre->text().trimmed();
    int nbreInvites = ui->spinBoxNbreInvites->value();
    QString codes_rfid = ""; // laissé vide pour le moment

    // ✅ Validation des champs
    QStringList erreurs;
    if (sujet.isEmpty() || sujet.length() < 3) erreurs << "🔹 Le *Sujet* doit contenir au moins 3 caractères.";
    if (date < QDate::currentDate()) erreurs << "🔹 La *date* ne peut pas être dans le passé.";
    if (!heure.isValid()) erreurs << "🔹 L'heure saisie est invalide.";
    if (duree <= 0) erreurs << "🔹 La *durée* doit être supérieure à zéro.";
    if (nom_formateur.isEmpty()) erreurs << "🔹 Le *Nom du formateur* est requis.";
    if (nom_centre.isEmpty()) erreurs << "🔹 Le *Nom du centre* est requis.";
    if (nbreInvites <= 0) erreurs << "🔹 Le *nombre d'invités* doit être supérieur à zéro.";

    if (!erreurs.isEmpty()) {
        QMessageBox::warning(this, "Champs invalides", erreurs.join("\n"));
        return;
    }

    // ✅ Création et insertion dans la base
    Formation f(sujet, date, heure, duree, statut, nom_formateur, nom_centre, nbreInvites, codes_rfid);
    if (f.ajouter()) {
        QMessageBox::information(this, "Succès", "📨 Formation ajoutée avec succès.");
        refreshTable();
        dessinerStatistiques();
        ui->tabAffichage->setCurrentWidget(ui->tabAff);

        envoyerSMS_Twilio(sujet, date, heure, statut, "✅ Ajout");
        envoyerNotifDiscord(sujet, date, "✅ Formation ajoutée");

        // ✅ Génération des tâches automatiquement dans la table TACHES
        QStringList taches = {
            QString("📘 %1 — Préparer salle").arg(sujet),
            QString("📘 %1 — Envoyer convocations").arg(sujet),
            QString("📘 %1 — Imprimer documents").arg(sujet),
            QString("📘 %1 — Vérifier participants").arg(sujet),
            QString("📘 %1 — Créer QR code accès").arg(sujet)
        };

        for (const QString &tache : taches) {
            QSqlQuery check;
            check.prepare("SELECT COUNT(*) FROM TACHES WHERE TEXTE = :t");
            check.bindValue(":t", tache);
            check.exec(); check.next();
            if (check.value(0).toInt() == 0) {
                QSqlQuery ins;
                ins.prepare("INSERT INTO TACHES (TEXTE, DATE_LIMITE, TERMINE) VALUES (:t, TO_DATE(:d, 'DD/MM/YYYY'), 0)");
                ins.bindValue(":t", tache);
                ins.bindValue(":d", date.toString("dd/MM/yyyy"));
                ins.exec();
            }
        }

        // ✅ Ouvrir la fenêtre de scan RFID avec ID nouvellement inséré
        int idNouvelleFormation = obtenirDernierIDFormation();
        FenetreScanBadges *fenetre = new FenetreScanBadges(idNouvelleFormation, this);
        fenetre->exec();

    } else {
        QMessageBox::critical(this, "Erreur", "❌ Échec de l'ajout.");
    }
}



void MainWindow::on_btnCharger_clicked()
{
    DialogID dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        int id = dialog.getID();
        Formation f;
        if (!f.existe(id)) {
            QMessageBox::warning(this, "Erreur", "Formation non trouvée.");
            return;
        }

        Formation data = f.getById(id);

        // 🎯 Remplir le formulaire
        ui->lineEditSujet->setText(data.getSujet());
        ui->dateEdit->setDate(data.getDate());
        ui->timeEdit->setTime(data.getHeure());
        ui->spinBoxDuree->setValue(data.getDuree());
        ui->comboStatut->setCurrentText(data.getStatut());
        ui->lineEditFormateur->setText(data.getNomFormateur());
        ui->lineEditCentre->setText(data.getNomCentre());
        ui->spinBoxNbreInvites->setValue(data.getNbreInvites());

        idFormationCourante = id;  // ✅ Sauvegarde l’ID chargé
        QMessageBox::information(this, "Formation chargée", QString("📥 Formation ID %1 chargée.").arg(id));
    }
}




void MainWindow::on_btnModifier_clicked()
{
    if (idFormationCourante == -1) {
        QMessageBox::warning(this, "Erreur", "❗ Aucune formation chargée à modifier.");
        return;
    }

    // 🧠 Vérifie que l'ID est encore valide
    Formation f;
    if (!f.existe(idFormationCourante)) {
        QMessageBox::warning(this, "Erreur", "❌ La formation n'existe plus.");
        return;
    }

    // 🔄 Lecture des champs du formulaire
    QString sujet = ui->lineEditSujet->text().trimmed();
    QDate date = ui->dateEdit->date();
    QTime heure = ui->timeEdit->time();
    int duree = ui->spinBoxDuree->value();
    QString statut = ui->comboStatut->currentText();
    QString nom_formateur = ui->lineEditFormateur->text().trimmed();
    QString nom_centre = ui->lineEditCentre->text().trimmed();
    int nbreInvites = ui->spinBoxNbreInvites->value();
    QString codes_rfid = "";  // champ laissé vide

    // 🔧 Mise à jour
    Formation update(idFormationCourante, sujet, date, heure, duree, statut, nom_formateur, nom_centre, nbreInvites, codes_rfid);
    if (update.modifier(idFormationCourante)) {
        QMessageBox::information(this, "Succès", QString("✅ Formation ID %1 modifiée avec succès.").arg(idFormationCourante));
        refreshTable();
        dessinerStatistiques();
        envoyerNotifDiscord(sujet, date, "✏️ Formation modifiée");

        envoyerSMS_Twilio(sujet, date, heure, statut, "✏️ Modification");
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification.");
    }
}




void MainWindow::on_btnSupprimer_clicked()
{
    DialogID dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        int id = dialog.getID();
        Formation f;
        if (!f.existe(id)) {
            QMessageBox::warning(this, "Erreur", "Formation non trouvée.");
            return;
        }

        Formation formationASupprimer = f.getById(id);
        if (f.supprimer(id)) {
            QMessageBox::information(this, "Succès", "Formation supprimée.");
            refreshTable();
            envoyerSMS_Twilio(formationASupprimer.getSujet(),
                              formationASupprimer.getDate(),
                              formationASupprimer.getHeure(),
                              formationASupprimer.getStatut(),
                              "🗑️ Suppression");
            envoyerNotifDiscord(formationASupprimer.getSujet(),
                                formationASupprimer.getDate(),
                                "🗑️ Formation supprimée");

        } else {
            QMessageBox::critical(this, "Erreur", "Échec de la suppression.");
        }
        dessinerStatistiques();
    }
}

void MainWindow::dessinerStatistiques()
{
    // 📐 Image plus grande pour une meilleure lisibilité
    int largeur = 1000;
    int hauteur = 800;
    QPixmap pixmap(largeur, hauteur);
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);

    // 🎯 Rectangle pour dessiner le camembert au centre
    QRect rect((largeur - 300) / 2, 50, 300, 300);

    // 📊 Récupérer les données depuis la base Oracle
    int nbPrevue = Formation().compterParStatut("Prévue");
    int nbEncours = Formation().compterParStatut("En cours");
    int nbTerminee = Formation().compterParStatut("Terminée");
    int total = nbPrevue + nbEncours + nbTerminee;
    if (total == 0) return;  // Aucun graphique si aucune donnée

    // 🎂 Calcul des angles pour chaque part
    int anglePrevue = static_cast<int>(360.0 * nbPrevue / total);
    int angleEncours = static_cast<int>(360.0 * nbEncours / total);
    int angleTerminee = 360 - anglePrevue - angleEncours;

    // 🍰 Dessin des parts colorées
    int startAngle = 0;
    painter.setBrush(Qt::blue);
    painter.drawPie(rect, startAngle * 16, anglePrevue * 16);
    startAngle += anglePrevue;

    painter.setBrush(Qt::green);
    painter.drawPie(rect, startAngle * 16, angleEncours * 16);
    startAngle += angleEncours;

    painter.setBrush(Qt::red);
    painter.drawPie(rect, startAngle * 16, angleTerminee * 16);

    // 🧾 Légende
    QFont font = painter.font();
    font.setPointSize(14);
    painter.setFont(font);

    painter.setPen(Qt::blue);
    painter.drawText(50, 400, QString("🔵 Prévue : %1").arg(nbPrevue));

    painter.setPen(Qt::green);
    painter.drawText(50, 440, QString("🟢 En cours : %1").arg(nbEncours));

    painter.setPen(Qt::red);
    painter.drawText(50, 480, QString("🔴 Terminée : %1").arg(nbTerminee));

    // 🖼️ Création et affectation de la scène dans le bon widget (lié à btnStat)
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addPixmap(pixmap);

    ui->graphicsViewStats->setScene(scene);
    ui->graphicsViewStats->setSceneRect(pixmap.rect());
}


void MainWindow::on_btnOuvrirChatbotIA_clicked()
{
    if (!chatbot) {
        chatbot = new ChatbotIA(this);
    }
    chatbot->show();
}

void MainWindow::envoyerSMS_Twilio(const QString &message)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QUrl url("https://textbelt.com/text");

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["phone"] = "+21620924006";  // Ton numéro
    json["message"] = message;
    json["key"] = "textbelt"; // ou ta clé API si personnalisée

    QJsonDocument doc(json);
    QByteArray data = doc.toJson();

    QNetworkReply *reply = manager->post(request, data);

    connect(reply, &QNetworkReply::finished, this, [reply]() {
        QByteArray response = reply->readAll();
        qDebug() << "Réponse : " << response;

        if (reply->error() == QNetworkReply::NoError)
            QMessageBox::information(nullptr, "SMS", "✅ SMS envoyé !");
        else
            QMessageBox::critical(nullptr, "Erreur SMS", "❌ " + reply->errorString());

        reply->deleteLater();
    });
}

void MainWindow::envoyerSMS_Twilio(const QString &sujet, const QDate &date, const QTime &heure, const QString &statut, const QString &operation)
{
    if (ui->checkBoxSMS && !ui->checkBoxSMS->isChecked()) {
        qDebug() << "[SMS] Envoi désactivé par l'utilisateur.";
        return;
    }

    // 🔧 Infos Twilio
    QString accountSid = "AC0daf2fa0fa9976480be094e0ebc780d3";
    QString authToken  = "474045aa03cd60ac1cd4bea35e1813e6";
    QString fromNumber = "+14136000186"; // ✅ Ton numéro Twilio
    QString toNumber   = "+21620924006"; // ✅ Le numéro du destinataire

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QUrl url("https://api.twilio.com/2010-04-01/Accounts/" + accountSid + "/Messages.json");
    QNetworkRequest request(url);

    // 🔐 Authentification en Base64
    QString credentials = accountSid + ":" + authToken;
    QByteArray encodedAuth = credentials.toUtf8().toBase64();
    request.setRawHeader("Authorization", "Basic " + encodedAuth);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    // ✉️ Corps du message
    QUrlQuery query;
    query.addQueryItem("From", fromNumber);
    query.addQueryItem("To", toNumber);
    query.addQueryItem("Body",
                       operation + " Formation :\n"
                                   "📘 Sujet: " + sujet +
                           "\n📅 Date: " + date.toString("dd/MM/yyyy") +
                           "\n🕒 Heure: " + heure.toString("HH:mm") +
                           "\n📌 Statut: " + statut);

    // 🚀 Envoi POST
    QNetworkReply *reply = manager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    // 📬 Traitement de la réponse
    connect(reply, &QNetworkReply::finished, this, [reply]() {
        QByteArray response = reply->readAll();
        qDebug() << "[SMS] Réponse Twilio :" << response;

        if (reply->error() == QNetworkReply::NoError) {
            QMessageBox::information(nullptr, "SMS", "✅ SMS envoyé avec succès !");
        } else {
            QMessageBox::critical(nullptr, "Erreur SMS", "❌ Erreur : " + reply->errorString());
        }

        reply->deleteLater();
    });
}


void MainWindow::on_btnVerifier_clicked()  // bouton "🔁 certif"
{
    QString fileName = QFileDialog::getOpenFileName(this, "Choisir un PDF à signer", "", "PDF Files (*.pdf)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir le PDF.");
        return;
    }

    QByteArray content = file.readAll();
    file.close();

    QByteArray hash = QCryptographicHash::hash(content, QCryptographicHash::Sha256).toHex();
    QString signatureHex = QString(hash);
    QString dateStr = QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm:ss");
    QString fileNameOnly = QFileInfo(fileName).fileName();

    QString outputFile = QFileInfo(fileName).absolutePath() + "/signed_" + fileNameOnly;
    QPdfWriter writer(outputFile);
    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setResolution(300);

    QPainter painter(&writer);
    QString responsable = "Khalil Khouaja – Directeur\nGestion de Formation";
    QString signatureText = QString(
                                "Fichier signé : %1\nDate : %2\nResponsable : %3\nCode :\n%4")
                                .arg(fileNameOnly)
                                .arg(dateStr)
                                .arg(responsable)
                                .arg(signatureHex);

    painter.setPen(Qt::red);
    painter.setFont(QFont("Arial", 10, QFont::Bold));
    painter.drawText(QRect(50, 50, writer.width() - 100, 400), Qt::AlignLeft | Qt::TextWordWrap, signatureText);
    painter.end();

    // 🔒 Enregistrement dans la base de données Oracle
    QSqlQuery query;
    query.prepare("INSERT INTO PDF_SIGNATURES (NOM_FICHIER, HASH_SHA256, DATE_SIGNATURE) "
                  "VALUES (:nom, :hash, TO_DATE(:date_signature, 'DD/MM/YYYY HH24:MI:SS'))");

    query.bindValue(":nom", fileNameOnly);
    query.bindValue(":hash", signatureHex);
    query.bindValue(":date_signature", QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm:ss"));

    if (!query.exec()) {
        qDebug() << "❌ Erreur d'insertion dans PDF_SIGNATURES:" << query.lastError().text();
    } else {
        qDebug() << "✅ Signature insérée dans la base de données.";
    }

    QMessageBox::information(this, "Succès", "PDF signé et code enregistré dans la base !");
    QDesktopServices::openUrl(QUrl::fromLocalFile(outputFile));
}

void MainWindow::on_btnVerifier1_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Choisir un PDF à vérifier", "", "PDF Files (*.pdf)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir le fichier.");
        return;
    }

    QByteArray content = file.readAll();
    file.close();

    QByteArray hash = QCryptographicHash::hash(content, QCryptographicHash::Sha256).toHex();
    QString signatureHex = QString(hash);

    // 🔍 Ouvrir le fichier texte des signatures
    QFile txtFile("signatures_certificats.txt");
    if (!txtFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir signatures_certificats.txt");
        return;
    }

    QTextStream in(&txtFile);
    QString ligneTrouvee;
    bool trouve = false;

    while (!in.atEnd()) {
        QString ligne = in.readLine().trimmed();
        if (ligne.contains(signatureHex)) {
            ligneTrouvee = ligne;
            trouve = true;
            break;
        }
    }
    txtFile.close();

    if (trouve) {
        QMessageBox::information(this, "Vérification réussie",
                                 "✅ Ce fichier est reconnu comme signé.\n\nHash :\n" + signatureHex + "\n\nLigne trouvée :\n" + ligneTrouvee);
    } else {
        QMessageBox::critical(this, "Fichier inconnu",
                              "❌ Ce fichier n’a pas été signé ou n’est pas reconnu.\n\nHash :\n" + signatureHex);
    }
}

void MainWindow::viderBaseFormations()
{
    QSqlQuery query;
    if (query.exec("DELETE FROM FORMATION")) {
        QMessageBox::information(this, "Nettoyage", "✅ Toutes les formations ont été supprimées !");
        refreshTable();  // Recharge la tableView
    } else {
        QMessageBox::critical(this, "Erreur", "❌ Échec lors de la suppression : " + query.lastError().text());
    }
}
void MainWindow::envoyerNotifDiscord(const QString &sujet, const QDate &date, const QString &action)
{
    // 🔗 Webhook Discord
    QUrl url("https://discord.com/api/webhooks/1363238138021150740/oDnAD9uYAhLcd66kqEJNmkxcxRNBHEZlvxZlZaNIguzHdBvccBH2KQhGtiq3PGkNoTvq");

    // 📦 Préparer la requête HTTP POST
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // 🧠 Créer le message Discord en JSON
    QJsonObject json;
    json["content"] = QString(
                          "**📢 Notification Formation**\n"
                          "**📘 Sujet :** %1\n"
                          "**📅 Date :** %2\n"
                          "**🔔 Action :** %3")
                          .arg(sujet)
                          .arg(date.toString("dd/MM/yyyy"))
                          .arg(action);

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkReply *reply = manager->post(request, QJsonDocument(json).toJson());

    connect(reply, &QNetworkReply::finished, this, [=]() {
        QByteArray response = reply->readAll();
        qDebug() << "[Discord Notif] Réponse : " << response;
        reply->deleteLater();
    });

    // 📁 🔐 Enregistrement local dans dossier ./logs/
    QDir logDir(QCoreApplication::applicationDirPath() + "/logs");
    if (!logDir.exists()) {
        logDir.mkpath(".");  // Crée le dossier logs s’il n’existe pas
    }

    QString logFilePath = logDir.filePath("logs_notifications.txt");

    QString logLine = QString("[%1] %2 | Sujet: %3 | Date: %4")
                          .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"))
                          .arg(action)
                          .arg(sujet)
                          .arg(date.toString("dd/MM/yyyy"));

    QFile logFile(logFilePath);
    if (logFile.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&logFile);
        out << logLine << "\n";
        logFile.close();
    } else {
        qDebug() << "❌ Impossible d'ouvrir le fichier de logs.";
    }
}
void MainWindow::on_btnOngletSignatures_clicked()
{
    if (!fenetreSignatures) {
        fenetreSignatures = new FenetreSignatures(this);
    } else {
        fenetreSignatures->actualiserTable();  // ✅ Refresh si elle existe déjà
    }

    fenetreSignatures->show();
    fenetreSignatures->raise();
    fenetreSignatures->activateWindow();
}


void MainWindow::on_btnTodo_clicked()
{
    qDebug() << "🟢 Ouverture fenêtre TodoList";

    if (!todoList) {
        todoList = new TodoList(this);
        todoList->setAttribute(Qt::WA_DeleteOnClose, false);

        connect(todoList, &QObject::destroyed, this, [=]() {
            todoList = nullptr;
        });
    }

    todoList->move(300, 200); // ✅ Position visible garantie
    todoList->show();
    todoList->raise();
    todoList->activateWindow();
}

int MainWindow::obtenirDernierIDFormation() {
    QSqlQuery query;
    query.prepare("SELECT MAX(ID_FORMATION) FROM FORMATION");
    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}


// 🔄 Rafraîchir la table avec les données actuelles
void MainWindow::refreshTable() {
    Formation f;
    QSqlQueryModel *model = f.afficher();
    ui->tableView->setModel(model);

    // 🔥 RÉAPPLIQUER les Delegates après chaque setModel()
    ui->tableView->setItemDelegateForColumn(2, new DateDelegate(this));  // Date
    ui->tableView->setItemDelegateForColumn(3, new TimeDelegate(this));  // Heure

    int total = model->rowCount();
    ui->labelCompeur->setText("Nombre de formations : " + QString::number(total));
    dessinerStatistiques();
}

void MainWindow::on_btnRechercher_clicked() {
    QString critere = ui->chercher->text().trimmed();  // récupère le texte saisi

    if (critere.isEmpty()) {
        QMessageBox::information(this, "Champ vide", "Veuillez entrer un critère de recherche.");
        return;
    }

    Formation f;
    QSqlQueryModel *model = f.rechercherMulticritere(critere);

    if (model && model->rowCount() > 0) {
        ui->tableView->setModel(model);
    } else {
        QMessageBox::information(this, "Aucun résultat", "Aucune formation trouvée.");
    }
}

// 🔃 Trier bouton
void MainWindow::on_btnTrier_clicked() {
    QString critere = ui->comboBoxTri->currentText();
    QString ordre = ui->comboBoxOrdre->currentText();
    Formation f;

    if (critere == "DATE_FORMATION") {
        QString ordre_sql = (ordre == "Croissant") ? "ASC" : "DESC";
        ui->tableView->setModel(f.trierPar("DATE_FORMATION", ordre_sql));
    } else {
        refreshTable();
    }
}

// 📂 Afficher tout bouton
void MainWindow::on_btnAfficherTout_clicked() {
    refreshTable();
    dessinerStatistiques();
}

// 🧾 Générer PDF bouton
void MainWindow::on_btnGenererPDF_clicked()
{
    QString defaultName = "Liste_Formations_" + QDate::currentDate().toString("dd-MM-yyyy") + ".pdf";
    QString filename = QFileDialog::getSaveFileName(this, "Enregistrer le PDF", QDir::homePath() + "/" + defaultName, "Fichiers PDF (*.pdf)");
    if (filename.isEmpty()) return;

    QPdfWriter pdf(filename);
    pdf.setPageSize(QPageSize::A4);
    pdf.setResolution(300);

    QPainter painter(&pdf);

    // === 1. Logo centré ===
    QPixmap logo(":/resources/logo.png");
    int logoWidth = 220;
    int logoHeight = 80;
    painter.drawPixmap((pdf.width() - logoWidth) / 2, 20, logoWidth, logoHeight, logo);

    // === 2. Titre principal ===
    painter.setFont(QFont("Arial", 20, QFont::Bold));
    painter.setPen(Qt::black);
    painter.drawText(QRect(0, logoHeight + 30, pdf.width(), 50), Qt::AlignCenter, "📋 Liste des Formations");

    // === 3. Récupérer le modèle de la table ===
    QAbstractItemModel *model = ui->tableView->model();
    if (!model) return;

    int cols = model->columnCount();
    int rows = model->rowCount();

    QFont headerFont("Arial", 11, QFont::Bold);
    QFont cellFont("Arial", 10);
    QFontMetrics headerFM(headerFont);
    QFontMetrics cellFM(cellFont);

    painter.setFont(cellFont);
    QVector<int> colWidths(cols, 0);

    for (int col = 0; col < cols; ++col) {
        int max = headerFM.horizontalAdvance(model->headerData(col, Qt::Horizontal).toString()) + 30;
        for (int row = 0; row < rows; ++row) {
            QString data = model->data(model->index(row, col)).toString();
            max = std::max(max, cellFM.horizontalAdvance(data) + 30);
        }
        colWidths[col] = max;
    }

    // === 4. Ajuster largeur des colonnes à la page
    int margin = 50;
    int availableWidth = pdf.width() - 2 * margin;
    int totalWidth = std::accumulate(colWidths.begin(), colWidths.end(), 0);
    double scaleW = double(availableWidth) / totalWidth;
    for (int &w : colWidths) w = int(w * scaleW);

    // === 5. Ajuster hauteur des lignes selon place dispo
    int top = logoHeight + 100;
    int bottomSpace = 200;  // espace QR
    int availableHeight = pdf.height() - top - bottomSpace;
    int rowHeight = availableHeight / (rows + 1);  // +1 pour l'en-tête

    int startX = margin;
    int startY = top;

    // === 6. En-tête
    painter.setFont(headerFont);
    painter.setPen(Qt::white);
    painter.setBrush(QColor("#444444"));
    int x = startX;
    for (int col = 0; col < cols; ++col) {
        QRect rect(x, startY, colWidths[col], rowHeight);
        painter.fillRect(rect, QColor("#444444"));
        painter.drawRect(rect);
        painter.drawText(rect, Qt::AlignCenter, model->headerData(col, Qt::Horizontal).toString());
        x += colWidths[col];
    }

    // === 7. Lignes de données
    painter.setFont(cellFont);
    painter.setPen(Qt::black);
    startY += rowHeight;

    for (int row = 0; row < rows; ++row) {
        int x = startX;
        for (int col = 0; col < cols; ++col) {
            QRect rect(x, startY, colWidths[col], rowHeight);
            painter.drawRect(rect);

            QString data = model->data(model->index(row, col)).toString();
            if (col == 2 && data.contains("T")) data = QDate::fromString(data.left(10), "yyyy-MM-dd").toString("dd/MM/yyyy");
            if (col == 3 && data.contains("T")) data = QTime::fromString(data.mid(11, 5), "HH:mm").toString("HH:mm");

            painter.drawText(rect, Qt::AlignCenter | Qt::TextWordWrap, data);
            x += colWidths[col];
        }
        startY += rowHeight;
    }






    painter.end();
    QMessageBox::information(this, "✅ Succès", "PDF généré avec succès !");
}


void MainWindow::on_btnScanRFID_clicked()
{
    FenetreControleRFID *fenetreControle = new FenetreControleRFID(this);
    fenetreControle->exec();  // Affiche la fenêtre modale
}
void MainWindow::on_btnVoirHistorique_clicked()
{
    HistoriqueBadges historique(this);
    historique.exec();
}

void MainWindow::on_chercher_textChanged(const QString &text) {
    QString critere = text.trimmed();
    Formation f;
    QSqlQueryModel *model = f.rechercher(critere);  // utilise ta fonction déjà définie

    if (model && model->rowCount() > 0) {
        ui->tableView->setModel(model);
    } else {
        ui->tableView->setModel(nullptr);  // vide la table si aucun résultat
    }
}


void MainWindow::on_btnStat_clicked()
{
    if (!fenetreStats) {
        fenetreStats = new FenetreStatsF(this);
    }
    fenetreStats->exec();  // Ouvre la fenêtre modale
}

void MainWindow::on_btnCertificat_clicked()
{
    Deplome *dlg = new Deplome(this);
    dlg->exec();
}
