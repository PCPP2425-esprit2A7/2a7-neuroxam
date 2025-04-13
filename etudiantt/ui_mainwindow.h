/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuitter;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QSplitter *splitter;
    QWidget *formLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QGroupBox *photoGroup;
    QVBoxLayout *verticalLayout_2;
    QLabel *photoLabel;
    QPushButton *browseButton;
    QFormLayout *formLayout;
    QLabel *labelName;
    QLineEdit *nameEdit;
    QLabel *labelFamilyName;
    QLineEdit *familyNameEdit;
    QLabel *labelCin;
    QLineEdit *cinEdit;
    QLabel *labelSpeciality;
    QLineEdit *specialityEdit;
    QLabel *labelNote;
    QLineEdit *noteEdit;
    QLabel *labelPhone;
    QLineEdit *phoneEdit;
    QLabel *labelEmail;
    QLineEdit *emailEdit;
    QLabel *labelBirthDate;
    QDateEdit *birthDateEdit;
    QLabel *labelGender;
    QComboBox *genderCombo;
    QHBoxLayout *buttonLayout;
    QPushButton *addButton;
    QPushButton *updateButton;
    QPushButton *deleteButton;
    QPushButton *clearButton;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_3;
    QLabel *titleListLabel;
    QHBoxLayout *searchLayout;
    QLabel *labelSearch;
    QComboBox *searchFieldCombo;
    QLineEdit *searchValueEdit;
    QPushButton *searchButton;
    QHBoxLayout *sortLayout;
    QLabel *labelSort;
    QComboBox *sortCombo;
    QTableView *tableView;
    QHBoxLayout *actionLayout;
    QPushButton *statsButton;
    QPushButton *pdfButton;
    QPushButton *studentPdfButton;
    QMenuBar *menubar;
    QMenu *menuFichier;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1305, 881);
        actionQuitter = new QAction(MainWindow);
        actionQuitter->setObjectName("actionQuitter");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Horizontal);
        formLayoutWidget = new QWidget(splitter);
        formLayoutWidget->setObjectName("formLayoutWidget");
        verticalLayout = new QVBoxLayout(formLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        titleLabel = new QLabel(formLayoutWidget);
        titleLabel->setObjectName("titleLabel");
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        titleLabel->setFont(font);
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        photoGroup = new QGroupBox(formLayoutWidget);
        photoGroup->setObjectName("photoGroup");
        verticalLayout_2 = new QVBoxLayout(photoGroup);
        verticalLayout_2->setObjectName("verticalLayout_2");
        photoLabel = new QLabel(photoGroup);
        photoLabel->setObjectName("photoLabel");
        photoLabel->setMinimumSize(QSize(150, 150));
        photoLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(photoLabel);

        browseButton = new QPushButton(photoGroup);
        browseButton->setObjectName("browseButton");

        verticalLayout_2->addWidget(browseButton);


        verticalLayout->addWidget(photoGroup);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        labelName = new QLabel(formLayoutWidget);
        labelName->setObjectName("labelName");

        formLayout->setWidget(0, QFormLayout::LabelRole, labelName);

        nameEdit = new QLineEdit(formLayoutWidget);
        nameEdit->setObjectName("nameEdit");

        formLayout->setWidget(0, QFormLayout::FieldRole, nameEdit);

        labelFamilyName = new QLabel(formLayoutWidget);
        labelFamilyName->setObjectName("labelFamilyName");

        formLayout->setWidget(1, QFormLayout::LabelRole, labelFamilyName);

        familyNameEdit = new QLineEdit(formLayoutWidget);
        familyNameEdit->setObjectName("familyNameEdit");

        formLayout->setWidget(1, QFormLayout::FieldRole, familyNameEdit);

        labelCin = new QLabel(formLayoutWidget);
        labelCin->setObjectName("labelCin");

        formLayout->setWidget(2, QFormLayout::LabelRole, labelCin);

        cinEdit = new QLineEdit(formLayoutWidget);
        cinEdit->setObjectName("cinEdit");

        formLayout->setWidget(2, QFormLayout::FieldRole, cinEdit);

        labelSpeciality = new QLabel(formLayoutWidget);
        labelSpeciality->setObjectName("labelSpeciality");

        formLayout->setWidget(3, QFormLayout::LabelRole, labelSpeciality);

        specialityEdit = new QLineEdit(formLayoutWidget);
        specialityEdit->setObjectName("specialityEdit");

        formLayout->setWidget(3, QFormLayout::FieldRole, specialityEdit);

        labelNote = new QLabel(formLayoutWidget);
        labelNote->setObjectName("labelNote");

        formLayout->setWidget(4, QFormLayout::LabelRole, labelNote);

        noteEdit = new QLineEdit(formLayoutWidget);
        noteEdit->setObjectName("noteEdit");

        formLayout->setWidget(4, QFormLayout::FieldRole, noteEdit);

        labelPhone = new QLabel(formLayoutWidget);
        labelPhone->setObjectName("labelPhone");

        formLayout->setWidget(5, QFormLayout::LabelRole, labelPhone);

        phoneEdit = new QLineEdit(formLayoutWidget);
        phoneEdit->setObjectName("phoneEdit");

        formLayout->setWidget(5, QFormLayout::FieldRole, phoneEdit);

        labelEmail = new QLabel(formLayoutWidget);
        labelEmail->setObjectName("labelEmail");

        formLayout->setWidget(6, QFormLayout::LabelRole, labelEmail);

        emailEdit = new QLineEdit(formLayoutWidget);
        emailEdit->setObjectName("emailEdit");

        formLayout->setWidget(6, QFormLayout::FieldRole, emailEdit);

        labelBirthDate = new QLabel(formLayoutWidget);
        labelBirthDate->setObjectName("labelBirthDate");

        formLayout->setWidget(7, QFormLayout::LabelRole, labelBirthDate);

        birthDateEdit = new QDateEdit(formLayoutWidget);
        birthDateEdit->setObjectName("birthDateEdit");

        formLayout->setWidget(7, QFormLayout::FieldRole, birthDateEdit);

        labelGender = new QLabel(formLayoutWidget);
        labelGender->setObjectName("labelGender");

        formLayout->setWidget(8, QFormLayout::LabelRole, labelGender);

        genderCombo = new QComboBox(formLayoutWidget);
        genderCombo->setObjectName("genderCombo");

        formLayout->setWidget(8, QFormLayout::FieldRole, genderCombo);


        verticalLayout->addLayout(formLayout);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName("buttonLayout");
        addButton = new QPushButton(formLayoutWidget);
        addButton->setObjectName("addButton");

        buttonLayout->addWidget(addButton);

        updateButton = new QPushButton(formLayoutWidget);
        updateButton->setObjectName("updateButton");

        buttonLayout->addWidget(updateButton);

        deleteButton = new QPushButton(formLayoutWidget);
        deleteButton->setObjectName("deleteButton");

        buttonLayout->addWidget(deleteButton);

        clearButton = new QPushButton(formLayoutWidget);
        clearButton->setObjectName("clearButton");

        buttonLayout->addWidget(clearButton);


        verticalLayout->addLayout(buttonLayout);

        splitter->addWidget(formLayoutWidget);
        verticalLayoutWidget = new QWidget(splitter);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        titleListLabel = new QLabel(verticalLayoutWidget);
        titleListLabel->setObjectName("titleListLabel");
        titleListLabel->setFont(font);
        titleListLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(titleListLabel);

        searchLayout = new QHBoxLayout();
        searchLayout->setObjectName("searchLayout");
        labelSearch = new QLabel(verticalLayoutWidget);
        labelSearch->setObjectName("labelSearch");

        searchLayout->addWidget(labelSearch);

        searchFieldCombo = new QComboBox(verticalLayoutWidget);
        searchFieldCombo->addItem(QString());
        searchFieldCombo->addItem(QString());
        searchFieldCombo->addItem(QString());
        searchFieldCombo->addItem(QString());
        searchFieldCombo->setObjectName("searchFieldCombo");

        searchLayout->addWidget(searchFieldCombo);

        searchValueEdit = new QLineEdit(verticalLayoutWidget);
        searchValueEdit->setObjectName("searchValueEdit");

        searchLayout->addWidget(searchValueEdit);

        searchButton = new QPushButton(verticalLayoutWidget);
        searchButton->setObjectName("searchButton");

        searchLayout->addWidget(searchButton);


        verticalLayout_3->addLayout(searchLayout);

        sortLayout = new QHBoxLayout();
        sortLayout->setObjectName("sortLayout");
        labelSort = new QLabel(verticalLayoutWidget);
        labelSort->setObjectName("labelSort");

        sortLayout->addWidget(labelSort);

        sortCombo = new QComboBox(verticalLayoutWidget);
        sortCombo->setObjectName("sortCombo");

        sortLayout->addWidget(sortCombo);


        verticalLayout_3->addLayout(sortLayout);

        tableView = new QTableView(verticalLayoutWidget);
        tableView->setObjectName("tableView");

        verticalLayout_3->addWidget(tableView);

        actionLayout = new QHBoxLayout();
        actionLayout->setObjectName("actionLayout");
        statsButton = new QPushButton(verticalLayoutWidget);
        statsButton->setObjectName("statsButton");

        actionLayout->addWidget(statsButton);

        pdfButton = new QPushButton(verticalLayoutWidget);
        pdfButton->setObjectName("pdfButton");

        actionLayout->addWidget(pdfButton);

        studentPdfButton = new QPushButton(verticalLayoutWidget);
        studentPdfButton->setObjectName("studentPdfButton");

        actionLayout->addWidget(studentPdfButton);


        verticalLayout_3->addLayout(actionLayout);

        splitter->addWidget(verticalLayoutWidget);

        horizontalLayout->addWidget(splitter);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1305, 21));
        menuFichier = new QMenu(menubar);
        menuFichier->setObjectName("menuFichier");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFichier->menuAction());
        menuFichier->addAction(actionQuitter);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Gestion des \303\211tudiants", nullptr));
        actionQuitter->setText(QCoreApplication::translate("MainWindow", "Quitter", nullptr));
        titleLabel->setText(QCoreApplication::translate("MainWindow", "Formulaire \303\211tudiant", nullptr));
        photoGroup->setTitle(QCoreApplication::translate("MainWindow", "Photo", nullptr));
        photoLabel->setText(QCoreApplication::translate("MainWindow", "Aucune photo", nullptr));
        browseButton->setText(QCoreApplication::translate("MainWindow", "Parcourir...", nullptr));
        labelName->setText(QCoreApplication::translate("MainWindow", "Nom:", nullptr));
        labelFamilyName->setText(QCoreApplication::translate("MainWindow", "Pr\303\251nom:", nullptr));
        labelCin->setText(QCoreApplication::translate("MainWindow", "CIN:", nullptr));
        labelSpeciality->setText(QCoreApplication::translate("MainWindow", "Sp\303\251cialit\303\251:", nullptr));
        labelNote->setText(QCoreApplication::translate("MainWindow", "Note:", nullptr));
        labelPhone->setText(QCoreApplication::translate("MainWindow", "T\303\251l\303\251phone:", nullptr));
        labelEmail->setText(QCoreApplication::translate("MainWindow", "Email:", nullptr));
        labelBirthDate->setText(QCoreApplication::translate("MainWindow", "Date de naissance:", nullptr));
        labelGender->setText(QCoreApplication::translate("MainWindow", "Genre:", nullptr));
        addButton->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        updateButton->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        deleteButton->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        clearButton->setText(QCoreApplication::translate("MainWindow", "Effacer", nullptr));
        titleListLabel->setText(QCoreApplication::translate("MainWindow", "Liste des \303\211tudiants", nullptr));
        labelSearch->setText(QCoreApplication::translate("MainWindow", "Recherche:", nullptr));
        searchFieldCombo->setItemText(0, QCoreApplication::translate("MainWindow", "name", nullptr));
        searchFieldCombo->setItemText(1, QCoreApplication::translate("MainWindow", "family_name", nullptr));
        searchFieldCombo->setItemText(2, QCoreApplication::translate("MainWindow", "cin", nullptr));
        searchFieldCombo->setItemText(3, QCoreApplication::translate("MainWindow", "speciality", nullptr));

        searchButton->setText(QCoreApplication::translate("MainWindow", "Rechercher", nullptr));
        labelSort->setText(QCoreApplication::translate("MainWindow", "Trier par:", nullptr));
        statsButton->setText(QCoreApplication::translate("MainWindow", "Statistiques", nullptr));
        pdfButton->setText(QCoreApplication::translate("MainWindow", "Exporter PDF", nullptr));
        studentPdfButton->setText(QCoreApplication::translate("MainWindow", "Fiche \303\211tudiant PDF", nullptr));
        menuFichier->setTitle(QCoreApplication::translate("MainWindow", "Fichier", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
