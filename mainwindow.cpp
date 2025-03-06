#include "mainwindow.h"
#include "ajouter.h"
#include <QHeaderView>
#include <QPixmap>
#include <QPalette>
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Gestion des Sessions de Formation");


    // Définition du fond d'écran
    QPixmap background(":/resources/background.png");
    if (background.isNull()) {
        qDebug() << "⚠️ Erreur: Impossible de charger l'image de fond!";
    }
    QPalette palette;
    palette.setBrush(QPalette::Window, background);
    this->setPalette(palette);

    // Chargement du logo (centré en haut)
    QLabel *logoLabel = new QLabel(this);
    QPixmap logo(":/resources/logo.png");
    if (logo.isNull()) {
        qDebug() << "⚠️ Erreur: Impossible de charger le logo!";
    } else {
        logoLabel->setPixmap(logo.scaled(180, 180, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        logoLabel->setAlignment(Qt::AlignCenter);
    }



    // Titre principal
    QLabel *titleLabel = new QLabel("<h4>📖 Répartition des Centre</h4>", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 32px; font-weight: bold; color: darkblue;");

    // Tableau des sessions (centré sans toucher la zone bleue)
    QTableWidget *tableWidget = new QTableWidget(10, 7, this);
    tableWidget->setHorizontalHeaderLabels({"ID", "Name", "Address", "Capacity", "Facilities", "Status", "Director"});
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->setStyleSheet("border: 2px solid #005bb5; font-size: 29px; background-color: white;");
    tableWidget->setMaximumWidth(2000);
    tableWidget->setMinimumWidth(1200);

    QHBoxLayout *tableLayout = new QHBoxLayout;
    tableLayout->addStretch();
    tableLayout->addWidget(tableWidget, 0, Qt::AlignCenter);
    tableLayout->addStretch();

    // Style des boutons
    QString btnStyle = "QPushButton {"
                       "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1E90FF, stop:1 #0073e6);"
                       "border-radius: 20px; color: white; padding: 12px 24px;"
                       "font-size: 16px; font-weight: bold; border: 2px solid #005bb5;"
                       "} QPushButton:hover { background-color: #005bb5; }";

    QString btnStyleDanger = "QPushButton {"
                             "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #FF6347, stop:1 #D32F2F);"
                             "border-radius: 20px; color: white; padding: 12px 24px;"
                             "font-size: 16px; font-weight: bold; border: 2px solid #b71c1c;"
                             "} QPushButton:hover { background-color: #b71c1c; }";

    // Création des boutons
    QPushButton *btnAjouter = new QPushButton("➕ Ajouter", this);
    QPushButton *btnModifier = new QPushButton("✏️ Modifier", this);
    QPushButton *btnSupprimer = new QPushButton("🗑️ Supprimer", this);
    QPushButton *btnGenererCertificat = new QPushButton("📜 map", this);
    QPushButton *btnRechercher = new QPushButton("🔍 Rechercher", this);
    QPushButton *btnSuiviFormations = new QPushButton("📄AI Recomandation ", this);
    QPushButton *btnDeconnexion = new QPushButton("🔓 Déconnexion", this);
    QPushButton *btnstat =new QPushButton ("statistique", this);
    // Application des styles
    btnAjouter->setStyleSheet(btnStyle);
    btnModifier->setStyleSheet(btnStyle);
    btnSupprimer->setStyleSheet(btnStyle);
    btnGenererCertificat->setStyleSheet(btnStyle);
    btnRechercher->setStyleSheet(btnStyle);
    btnSuiviFormations->setStyleSheet(btnStyle);
    btnDeconnexion->setStyleSheet(btnStyleDanger);
    btnstat->setStyleSheet(btnStyle);

    // Cadre contenant les boutons
    QWidget *buttonFrame = new QWidget(this);
    buttonFrame->setStyleSheet("background-color: #D6E6FF;" // Bleu clair
                               "border-radius: 20px;"
                               "border: 2px solid #005bb5;"
                               "padding: 15px;"
                               );

    QVBoxLayout *frameLayout = new QVBoxLayout(buttonFrame);

    QHBoxLayout *buttonRow1 = new QHBoxLayout;
    buttonRow1->addWidget(btnAjouter);
    buttonRow1->addWidget(btnModifier);
    buttonRow1->addWidget(btnSupprimer);

    QHBoxLayout *buttonRow2 = new QHBoxLayout;
    buttonRow2->addWidget(btnGenererCertificat);
    buttonRow2->addWidget(btnRechercher);
    buttonRow2->addWidget(btnSuiviFormations);

    buttonRow2->addWidget(btnstat);

    frameLayout->addLayout(buttonRow1);
    frameLayout->addLayout(buttonRow2);
    frameLayout->setAlignment(Qt::AlignCenter);

    // Widget du graphique (dimension corrigée)
    //chartWidget = new PieChartWidget(this);
    //chartWidget->setFixedSize(250, 250);
 //   QLabel *chartTitle = new QLabel("📊 Statistiques sur l'Engagement et Présence", this);
  //  chartTitle->setAlignment(Qt::AlignCenter);
  //  chartTitle->setStyleSheet("font-size: 18px; color: darkblue; font-weight: bold;");

    // Layout principal
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(logoLabel);
    layout->addWidget(titleLabel);
    layout->addLayout(tableLayout);
    layout->addWidget(buttonFrame, 0, Qt::AlignCenter);
  //  layout->addWidget(chartTitle);
 //   layout->addWidget(chartWidget, 0, Qt::AlignCenter);

    // Bouton Déconnexion en haut à gauche
    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(btnDeconnexion);
    topLayout->addStretch();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(layout);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow() {

}

