/********************************************************************************
** Form generated from reading UI file 'etudiant.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ETUDIANT_H
#define UI_ETUDIANT_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EtudiantDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *studentTab;
    QHBoxLayout *horizontalLayout;
    QFrame *sidebarFrame;
    QLabel *logoLabel;
    QPushButton *homeButton;
    QPushButton *employeeButton;
    QPushButton *centerButton;
    QPushButton *examButton;
    QPushButton *studentButton;
    QPushButton *materialButton;
    QPushButton *trainingButton;
    QPushButton *logoutButton;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *formGroupBox;
    QFormLayout *formLayout;
    QLabel *idLabel;
    QLineEdit *idLineEdit;
    QLabel *nameLabel;
    QLineEdit *nameLineEdit;
    QLabel *familyNameLabel;
    QLineEdit *familyNameLineEdit;
    QLabel *cinLabel;
    QLineEdit *cinLineEdit;
    QLabel *specialityLabel;
    QLineEdit *specialityLineEdit;
    QLabel *noteLabel;
    QDoubleSpinBox *noteSpinBox;
    QLabel *genderLabel;
    QComboBox *genderComboBox;
    QLabel *phoneLabel;
    QLineEdit *phoneLineEdit;
    QLabel *emailLabel;
    QLineEdit *emailLineEdit;
    QLabel *birthDateLabel;
    QDateEdit *birthDateEdit;
    QLabel *photoLabel;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *photoPathLineEdit;
    QPushButton *browseButton;
    QLabel *photoPreviewLabel;
    QPushButton *openChatBotButton;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *addButton;
    QPushButton *updateButton;
    QPushButton *deleteButton;
    QPushButton *clearButton;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *searchLabel;
    QLineEdit *searchLineEdit;
    QPushButton *searchButton;
    QHBoxLayout *horizontalLayout_5;
    QLabel *sortLabel;
    QPushButton *sortButton;
    QTableView *studentTableView;
    QWidget *statsTab;
    QHBoxLayout *horizontalLayout_stats;
    QFrame *sidebarFrameStats;
    QLabel *logoLabelStats;
    QPushButton *homeButtonStats;
    QPushButton *employeeButtonStats;
    QPushButton *centerButtonStats;
    QPushButton *examButtonStats;
    QPushButton *studentButtonStats;
    QPushButton *materialButtonStats;
    QPushButton *trainingButtonStats;
    QPushButton *logoutButtonStats;
    QVBoxLayout *verticalLayout_4;
    QLabel *statsLabel;
    QWidget *chartWidget;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer;
    QPushButton *refreshStatsButton;
    QPushButton *exportPdfButton;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *EtudiantDialog)
    {
        if (EtudiantDialog->objectName().isEmpty())
            EtudiantDialog->setObjectName("EtudiantDialog");
        EtudiantDialog->resize(900, 662);
        EtudiantDialog->setStyleSheet(QString::fromUtf8("background-image: url(:/resources/background.png);"));
        verticalLayout = new QVBoxLayout(EtudiantDialog);
        verticalLayout->setObjectName("verticalLayout");
        tabWidget = new QTabWidget(EtudiantDialog);
        tabWidget->setObjectName("tabWidget");
        studentTab = new QWidget();
        studentTab->setObjectName("studentTab");
        horizontalLayout = new QHBoxLayout(studentTab);
        horizontalLayout->setObjectName("horizontalLayout");
        sidebarFrame = new QFrame(studentTab);
        sidebarFrame->setObjectName("sidebarFrame");
        sidebarFrame->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        logoLabel = new QLabel(sidebarFrame);
        logoLabel->setObjectName("logoLabel");
        logoLabel->setGeometry(QRect(50, 90, 171, 111));
        logoLabel->setStyleSheet(QString::fromUtf8("image: url(:/resources/image_2025-01-29_201537391-removebg-preview.png);"));
        homeButton = new QPushButton(sidebarFrame);
        homeButton->setObjectName("homeButton");
        homeButton->setGeometry(QRect(30, 230, 201, 41));
        homeButton->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        employeeButton = new QPushButton(sidebarFrame);
        employeeButton->setObjectName("employeeButton");
        employeeButton->setGeometry(QRect(30, 290, 201, 41));
        employeeButton->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        centerButton = new QPushButton(sidebarFrame);
        centerButton->setObjectName("centerButton");
        centerButton->setGeometry(QRect(30, 350, 201, 41));
        centerButton->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        examButton = new QPushButton(sidebarFrame);
        examButton->setObjectName("examButton");
        examButton->setGeometry(QRect(30, 410, 201, 41));
        examButton->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        studentButton = new QPushButton(sidebarFrame);
        studentButton->setObjectName("studentButton");
        studentButton->setGeometry(QRect(30, 470, 201, 41));
        studentButton->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        materialButton = new QPushButton(sidebarFrame);
        materialButton->setObjectName("materialButton");
        materialButton->setGeometry(QRect(30, 530, 201, 41));
        materialButton->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        trainingButton = new QPushButton(sidebarFrame);
        trainingButton->setObjectName("trainingButton");
        trainingButton->setGeometry(QRect(30, 590, 201, 41));
        trainingButton->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        logoutButton = new QPushButton(sidebarFrame);
        logoutButton->setObjectName("logoutButton");
        logoutButton->setGeometry(QRect(30, 650, 201, 41));
        logoutButton->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));

        horizontalLayout->addWidget(sidebarFrame);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        formGroupBox = new QGroupBox(studentTab);
        formGroupBox->setObjectName("formGroupBox");
        formGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox{background-image: url(:/resources/background.png);}"));
        formLayout = new QFormLayout(formGroupBox);
        formLayout->setObjectName("formLayout");
        idLabel = new QLabel(formGroupBox);
        idLabel->setObjectName("idLabel");
        QFont font;
        font.setFamilies({QString::fromUtf8("Perpetua")});
        font.setPointSize(12);
        font.setBold(true);
        font.setItalic(true);
        idLabel->setFont(font);
        idLabel->setStyleSheet(QString::fromUtf8("color:#030C54;border:none;"));

        formLayout->setWidget(0, QFormLayout::LabelRole, idLabel);

        idLineEdit = new QLineEdit(formGroupBox);
        idLineEdit->setObjectName("idLineEdit");
        idLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        idLineEdit->setReadOnly(true);

        formLayout->setWidget(0, QFormLayout::FieldRole, idLineEdit);

        nameLabel = new QLabel(formGroupBox);
        nameLabel->setObjectName("nameLabel");
        nameLabel->setFont(font);
        nameLabel->setStyleSheet(QString::fromUtf8("color:#030C54;border:none;"));

        formLayout->setWidget(1, QFormLayout::LabelRole, nameLabel);

        nameLineEdit = new QLineEdit(formGroupBox);
        nameLineEdit->setObjectName("nameLineEdit");
        nameLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        formLayout->setWidget(1, QFormLayout::FieldRole, nameLineEdit);

        familyNameLabel = new QLabel(formGroupBox);
        familyNameLabel->setObjectName("familyNameLabel");
        familyNameLabel->setFont(font);
        familyNameLabel->setStyleSheet(QString::fromUtf8("color:#030C54;border:none;"));

        formLayout->setWidget(2, QFormLayout::LabelRole, familyNameLabel);

        familyNameLineEdit = new QLineEdit(formGroupBox);
        familyNameLineEdit->setObjectName("familyNameLineEdit");
        familyNameLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        formLayout->setWidget(2, QFormLayout::FieldRole, familyNameLineEdit);

        cinLabel = new QLabel(formGroupBox);
        cinLabel->setObjectName("cinLabel");
        cinLabel->setFont(font);
        cinLabel->setStyleSheet(QString::fromUtf8("color:#030C54;border:none;"));

        formLayout->setWidget(3, QFormLayout::LabelRole, cinLabel);

        cinLineEdit = new QLineEdit(formGroupBox);
        cinLineEdit->setObjectName("cinLineEdit");
        cinLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        formLayout->setWidget(3, QFormLayout::FieldRole, cinLineEdit);

        specialityLabel = new QLabel(formGroupBox);
        specialityLabel->setObjectName("specialityLabel");
        specialityLabel->setFont(font);
        specialityLabel->setStyleSheet(QString::fromUtf8("color:#030C54;border:none;"));

        formLayout->setWidget(4, QFormLayout::LabelRole, specialityLabel);

        specialityLineEdit = new QLineEdit(formGroupBox);
        specialityLineEdit->setObjectName("specialityLineEdit");
        specialityLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        formLayout->setWidget(4, QFormLayout::FieldRole, specialityLineEdit);

        noteLabel = new QLabel(formGroupBox);
        noteLabel->setObjectName("noteLabel");
        noteLabel->setFont(font);
        noteLabel->setStyleSheet(QString::fromUtf8("color:#030C54;border:none;"));

        formLayout->setWidget(5, QFormLayout::LabelRole, noteLabel);

        noteSpinBox = new QDoubleSpinBox(formGroupBox);
        noteSpinBox->setObjectName("noteSpinBox");
        noteSpinBox->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        noteSpinBox->setMaximum(20.000000000000000);

        formLayout->setWidget(5, QFormLayout::FieldRole, noteSpinBox);

        genderLabel = new QLabel(formGroupBox);
        genderLabel->setObjectName("genderLabel");
        genderLabel->setFont(font);
        genderLabel->setStyleSheet(QString::fromUtf8("color:#030C54;border:none;"));

        formLayout->setWidget(6, QFormLayout::LabelRole, genderLabel);

        genderComboBox = new QComboBox(formGroupBox);
        genderComboBox->addItem(QString());
        genderComboBox->addItem(QString());
        genderComboBox->setObjectName("genderComboBox");
        genderComboBox->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        formLayout->setWidget(6, QFormLayout::FieldRole, genderComboBox);

        phoneLabel = new QLabel(formGroupBox);
        phoneLabel->setObjectName("phoneLabel");
        phoneLabel->setFont(font);
        phoneLabel->setStyleSheet(QString::fromUtf8("color:#030C54;border:none;"));

        formLayout->setWidget(7, QFormLayout::LabelRole, phoneLabel);

        phoneLineEdit = new QLineEdit(formGroupBox);
        phoneLineEdit->setObjectName("phoneLineEdit");
        phoneLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        formLayout->setWidget(7, QFormLayout::FieldRole, phoneLineEdit);

        emailLabel = new QLabel(formGroupBox);
        emailLabel->setObjectName("emailLabel");
        emailLabel->setFont(font);
        emailLabel->setStyleSheet(QString::fromUtf8("color:#030C54;border:none;"));

        formLayout->setWidget(8, QFormLayout::LabelRole, emailLabel);

        emailLineEdit = new QLineEdit(formGroupBox);
        emailLineEdit->setObjectName("emailLineEdit");
        emailLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        formLayout->setWidget(8, QFormLayout::FieldRole, emailLineEdit);

        birthDateLabel = new QLabel(formGroupBox);
        birthDateLabel->setObjectName("birthDateLabel");
        birthDateLabel->setFont(font);
        birthDateLabel->setStyleSheet(QString::fromUtf8("color:#030C54;border:none;"));

        formLayout->setWidget(9, QFormLayout::LabelRole, birthDateLabel);

        birthDateEdit = new QDateEdit(formGroupBox);
        birthDateEdit->setObjectName("birthDateEdit");
        birthDateEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        birthDateEdit->setCalendarPopup(true);

        formLayout->setWidget(9, QFormLayout::FieldRole, birthDateEdit);

        photoLabel = new QLabel(formGroupBox);
        photoLabel->setObjectName("photoLabel");
        photoLabel->setFont(font);
        photoLabel->setStyleSheet(QString::fromUtf8("color:#030C54;border:none;"));

        formLayout->setWidget(10, QFormLayout::LabelRole, photoLabel);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        photoPathLineEdit = new QLineEdit(formGroupBox);
        photoPathLineEdit->setObjectName("photoPathLineEdit");
        photoPathLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        photoPathLineEdit->setReadOnly(true);

        horizontalLayout_2->addWidget(photoPathLineEdit);

        browseButton = new QPushButton(formGroupBox);
        browseButton->setObjectName("browseButton");
        browseButton->setStyleSheet(QString::fromUtf8("border:1px solid white;border-radius:20px;background-color:#030C54;color:white;background-image: url(:/resources/background.png);"));

        horizontalLayout_2->addWidget(browseButton);


        formLayout->setLayout(10, QFormLayout::FieldRole, horizontalLayout_2);

        photoPreviewLabel = new QLabel(formGroupBox);
        photoPreviewLabel->setObjectName("photoPreviewLabel");
        photoPreviewLabel->setMinimumSize(QSize(150, 150));
        photoPreviewLabel->setStyleSheet(QString::fromUtf8("color:#030C54;border:none;"));
        photoPreviewLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        formLayout->setWidget(11, QFormLayout::FieldRole, photoPreviewLabel);

        openChatBotButton = new QPushButton(formGroupBox);
        openChatBotButton->setObjectName("openChatBotButton");
        openChatBotButton->setStyleSheet(QString::fromUtf8("border:1px solid white;border-radius:20px;background-color:#030C54;color:white;background-image: url(:/resources/background.png);"));
        QIcon icon(QIcon::fromTheme(QString::fromUtf8("chat")));
        openChatBotButton->setIcon(icon);

        formLayout->setWidget(12, QFormLayout::FieldRole, openChatBotButton);


        verticalLayout_2->addWidget(formGroupBox);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        addButton = new QPushButton(studentTab);
        addButton->setObjectName("addButton");
        addButton->setStyleSheet(QString::fromUtf8("border:1px solid white;border-radius:20px;background-color:#030C54;color:white;background-image: url(:/resources/background.png);"));

        horizontalLayout_3->addWidget(addButton);

        updateButton = new QPushButton(studentTab);
        updateButton->setObjectName("updateButton");
        updateButton->setStyleSheet(QString::fromUtf8("border:1px solid white;border-radius:20px;background-color:#030C54;color:white;background-image: url(:/resources/background.png);"));

        horizontalLayout_3->addWidget(updateButton);

        deleteButton = new QPushButton(studentTab);
        deleteButton->setObjectName("deleteButton");
        deleteButton->setStyleSheet(QString::fromUtf8("border:1px solid white;border-radius:20px;background-color:#030C54;color:white;background-image: url(:/resources/background.png);"));

        horizontalLayout_3->addWidget(deleteButton);

        clearButton = new QPushButton(studentTab);
        clearButton->setObjectName("clearButton");
        clearButton->setStyleSheet(QString::fromUtf8("border:1px solid white;border-radius:20px;background-color:#030C54;color:white;background-image: url(:/resources/background.png);"));

        horizontalLayout_3->addWidget(clearButton);


        verticalLayout_2->addLayout(horizontalLayout_3);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        searchLabel = new QLabel(studentTab);
        searchLabel->setObjectName("searchLabel");
        searchLabel->setFont(font);
        searchLabel->setStyleSheet(QString::fromUtf8("color:#030C54;border:none;"));

        horizontalLayout_4->addWidget(searchLabel);

        searchLineEdit = new QLineEdit(studentTab);
        searchLineEdit->setObjectName("searchLineEdit");
        searchLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        horizontalLayout_4->addWidget(searchLineEdit);

        searchButton = new QPushButton(studentTab);
        searchButton->setObjectName("searchButton");
        searchButton->setStyleSheet(QString::fromUtf8("border:1px solid white;border-radius:20px;background-color:#030C54;color:white;background-image: url(:/resources/background.png);"));

        horizontalLayout_4->addWidget(searchButton);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        sortLabel = new QLabel(studentTab);
        sortLabel->setObjectName("sortLabel");
        sortLabel->setFont(font);
        sortLabel->setStyleSheet(QString::fromUtf8("color:#030C54;border:none;"));

        horizontalLayout_5->addWidget(sortLabel);

        sortButton = new QPushButton(studentTab);
        sortButton->setObjectName("sortButton");
        sortButton->setStyleSheet(QString::fromUtf8("border:1px solid white;border-radius:20px;background-color:#030C54;color:white;background-image: url(:/resources/background.png);"));

        horizontalLayout_5->addWidget(sortButton);


        verticalLayout_3->addLayout(horizontalLayout_5);

        studentTableView = new QTableView(studentTab);
        studentTableView->setObjectName("studentTableView");
        studentTableView->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        studentTableView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        verticalLayout_3->addWidget(studentTableView);


        horizontalLayout->addLayout(verticalLayout_3);

        tabWidget->addTab(studentTab, QString());
        statsTab = new QWidget();
        statsTab->setObjectName("statsTab");
        horizontalLayout_stats = new QHBoxLayout(statsTab);
        horizontalLayout_stats->setObjectName("horizontalLayout_stats");
        sidebarFrameStats = new QFrame(statsTab);
        sidebarFrameStats->setObjectName("sidebarFrameStats");
        sidebarFrameStats->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        logoLabelStats = new QLabel(sidebarFrameStats);
        logoLabelStats->setObjectName("logoLabelStats");
        logoLabelStats->setGeometry(QRect(50, 90, 171, 111));
        logoLabelStats->setStyleSheet(QString::fromUtf8("image: url(:/resources/image_2025-01-29_201537391-removebg-preview.png);"));
        homeButtonStats = new QPushButton(sidebarFrameStats);
        homeButtonStats->setObjectName("homeButtonStats");
        homeButtonStats->setGeometry(QRect(30, 230, 201, 41));
        homeButtonStats->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        employeeButtonStats = new QPushButton(sidebarFrameStats);
        employeeButtonStats->setObjectName("employeeButtonStats");
        employeeButtonStats->setGeometry(QRect(30, 290, 201, 41));
        employeeButtonStats->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        centerButtonStats = new QPushButton(sidebarFrameStats);
        centerButtonStats->setObjectName("centerButtonStats");
        centerButtonStats->setGeometry(QRect(30, 350, 201, 41));
        centerButtonStats->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        examButtonStats = new QPushButton(sidebarFrameStats);
        examButtonStats->setObjectName("examButtonStats");
        examButtonStats->setGeometry(QRect(30, 410, 201, 41));
        examButtonStats->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        studentButtonStats = new QPushButton(sidebarFrameStats);
        studentButtonStats->setObjectName("studentButtonStats");
        studentButtonStats->setGeometry(QRect(30, 470, 201, 41));
        studentButtonStats->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        materialButtonStats = new QPushButton(sidebarFrameStats);
        materialButtonStats->setObjectName("materialButtonStats");
        materialButtonStats->setGeometry(QRect(30, 530, 201, 41));
        materialButtonStats->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        trainingButtonStats = new QPushButton(sidebarFrameStats);
        trainingButtonStats->setObjectName("trainingButtonStats");
        trainingButtonStats->setGeometry(QRect(30, 590, 201, 41));
        trainingButtonStats->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        logoutButtonStats = new QPushButton(sidebarFrameStats);
        logoutButtonStats->setObjectName("logoutButtonStats");
        logoutButtonStats->setGeometry(QRect(30, 650, 201, 41));
        logoutButtonStats->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));

        horizontalLayout_stats->addWidget(sidebarFrameStats);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        statsLabel = new QLabel(statsTab);
        statsLabel->setObjectName("statsLabel");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Perpetua")});
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setItalic(true);
        statsLabel->setFont(font1);
        statsLabel->setStyleSheet(QString::fromUtf8("color:#030C54;border:none;"));
        statsLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_4->addWidget(statsLabel);

        chartWidget = new QWidget(statsTab);
        chartWidget->setObjectName("chartWidget");
        chartWidget->setMinimumSize(QSize(0, 400));
        chartWidget->setStyleSheet(QString::fromUtf8("background-image: url(:/resources/background.png);"));

        verticalLayout_4->addWidget(chartWidget);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);

        refreshStatsButton = new QPushButton(statsTab);
        refreshStatsButton->setObjectName("refreshStatsButton");
        refreshStatsButton->setStyleSheet(QString::fromUtf8("border:1px solid white;border-radius:20px;background-color:#030C54;color:white;background-image: url(:/resources/background.png);"));

        horizontalLayout_6->addWidget(refreshStatsButton);

        exportPdfButton = new QPushButton(statsTab);
        exportPdfButton->setObjectName("exportPdfButton");
        exportPdfButton->setStyleSheet(QString::fromUtf8("border:1px solid white;border-radius:20px;background-color:#030C54;color:white;background-image: url(:/resources/background.png);"));

        horizontalLayout_6->addWidget(exportPdfButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_2);


        verticalLayout_4->addLayout(horizontalLayout_6);


        horizontalLayout_stats->addLayout(verticalLayout_4);

        tabWidget->addTab(statsTab, QString());

        verticalLayout->addWidget(tabWidget);


        retranslateUi(EtudiantDialog);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(EtudiantDialog);
    } // setupUi

    void retranslateUi(QDialog *EtudiantDialog)
    {
        EtudiantDialog->setWindowTitle(QCoreApplication::translate("EtudiantDialog", "Gestion des \303\211tudiants", nullptr));
        logoLabel->setText(QString());
        homeButton->setText(QCoreApplication::translate("EtudiantDialog", "\360\237\217\240 Home", nullptr));
        employeeButton->setText(QCoreApplication::translate("EtudiantDialog", "\360\237\221\250\342\200\215\360\237\222\274 Employ\303\251", nullptr));
        centerButton->setText(QCoreApplication::translate("EtudiantDialog", "\360\237\217\253 Centre", nullptr));
        examButton->setText(QCoreApplication::translate("EtudiantDialog", "\360\237\223\235 Examen", nullptr));
        studentButton->setText(QCoreApplication::translate("EtudiantDialog", "\360\237\216\223 Etudiant", nullptr));
        materialButton->setText(QCoreApplication::translate("EtudiantDialog", "\360\237\247\260 Mat\303\251riel", nullptr));
        trainingButton->setText(QCoreApplication::translate("EtudiantDialog", "\360\237\223\232 Formation", nullptr));
        logoutButton->setText(QCoreApplication::translate("EtudiantDialog", "\360\237\224\223 Deconnexion", nullptr));
        formGroupBox->setTitle(QCoreApplication::translate("EtudiantDialog", "Informations \303\211tudiant", nullptr));
        idLabel->setText(QCoreApplication::translate("EtudiantDialog", "ID:", nullptr));
        nameLabel->setText(QCoreApplication::translate("EtudiantDialog", "Nom:", nullptr));
        familyNameLabel->setText(QCoreApplication::translate("EtudiantDialog", "Pr\303\251nom:", nullptr));
        cinLabel->setText(QCoreApplication::translate("EtudiantDialog", "CIN:", nullptr));
        specialityLabel->setText(QCoreApplication::translate("EtudiantDialog", "Sp\303\251cialit\303\251:", nullptr));
        noteLabel->setText(QCoreApplication::translate("EtudiantDialog", "Note:", nullptr));
        genderLabel->setText(QCoreApplication::translate("EtudiantDialog", "Genre:", nullptr));
        genderComboBox->setItemText(0, QCoreApplication::translate("EtudiantDialog", "Homme", nullptr));
        genderComboBox->setItemText(1, QCoreApplication::translate("EtudiantDialog", "Femme", nullptr));

        phoneLabel->setText(QCoreApplication::translate("EtudiantDialog", "T\303\251l\303\251phone:", nullptr));
        emailLabel->setText(QCoreApplication::translate("EtudiantDialog", "Email:", nullptr));
        birthDateLabel->setText(QCoreApplication::translate("EtudiantDialog", "Date de naissance:", nullptr));
        photoLabel->setText(QCoreApplication::translate("EtudiantDialog", "Photo:", nullptr));
        browseButton->setText(QCoreApplication::translate("EtudiantDialog", "Parcourir...", nullptr));
        photoPreviewLabel->setText(QCoreApplication::translate("EtudiantDialog", "Aucune photo", nullptr));
        openChatBotButton->setText(QCoreApplication::translate("EtudiantDialog", "Chat with AI Assistant", nullptr));
        addButton->setText(QCoreApplication::translate("EtudiantDialog", "Ajouter", nullptr));
        updateButton->setText(QCoreApplication::translate("EtudiantDialog", "Modifier", nullptr));
        deleteButton->setText(QCoreApplication::translate("EtudiantDialog", "Supprimer", nullptr));
        clearButton->setText(QCoreApplication::translate("EtudiantDialog", "Effacer", nullptr));
        searchLabel->setText(QCoreApplication::translate("EtudiantDialog", "Rechercher:", nullptr));
        searchButton->setText(QCoreApplication::translate("EtudiantDialog", "Chercher", nullptr));
        sortLabel->setText(QCoreApplication::translate("EtudiantDialog", "Trier par nom:", nullptr));
        sortButton->setText(QCoreApplication::translate("EtudiantDialog", "Trier", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(studentTab), QCoreApplication::translate("EtudiantDialog", "\303\211tudiants", nullptr));
        logoLabelStats->setText(QString());
        homeButtonStats->setText(QCoreApplication::translate("EtudiantDialog", "\360\237\217\240 Home", nullptr));
        employeeButtonStats->setText(QCoreApplication::translate("EtudiantDialog", "\360\237\221\250\342\200\215\360\237\222\274 Employ\303\251", nullptr));
        centerButtonStats->setText(QCoreApplication::translate("EtudiantDialog", "\360\237\217\253 Centre", nullptr));
        examButtonStats->setText(QCoreApplication::translate("EtudiantDialog", "\360\237\223\235 Examen", nullptr));
        studentButtonStats->setText(QCoreApplication::translate("EtudiantDialog", "\360\237\216\223 Etudiant", nullptr));
        materialButtonStats->setText(QCoreApplication::translate("EtudiantDialog", "\360\237\247\260 Mat\303\251riel", nullptr));
        trainingButtonStats->setText(QCoreApplication::translate("EtudiantDialog", "\360\237\223\232 Formation", nullptr));
        logoutButtonStats->setText(QCoreApplication::translate("EtudiantDialog", "\360\237\224\223 Deconnexion", nullptr));
        statsLabel->setText(QCoreApplication::translate("EtudiantDialog", "Statistiques par Genre", nullptr));
        refreshStatsButton->setText(QCoreApplication::translate("EtudiantDialog", "Actualiser", nullptr));
        exportPdfButton->setText(QCoreApplication::translate("EtudiantDialog", "Exporter PDF", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(statsTab), QCoreApplication::translate("EtudiantDialog", "Statistiques", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EtudiantDialog: public Ui_EtudiantDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ETUDIANT_H
