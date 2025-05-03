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
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
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
        EtudiantDialog->resize(900, 650);
        verticalLayout = new QVBoxLayout(EtudiantDialog);
        verticalLayout->setObjectName("verticalLayout");
        tabWidget = new QTabWidget(EtudiantDialog);
        tabWidget->setObjectName("tabWidget");
        studentTab = new QWidget();
        studentTab->setObjectName("studentTab");
        horizontalLayout = new QHBoxLayout(studentTab);
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        formGroupBox = new QGroupBox(studentTab);
        formGroupBox->setObjectName("formGroupBox");
        formLayout = new QFormLayout(formGroupBox);
        formLayout->setObjectName("formLayout");
        idLabel = new QLabel(formGroupBox);
        idLabel->setObjectName("idLabel");

        formLayout->setWidget(0, QFormLayout::LabelRole, idLabel);

        idLineEdit = new QLineEdit(formGroupBox);
        idLineEdit->setObjectName("idLineEdit");
        idLineEdit->setReadOnly(true);

        formLayout->setWidget(0, QFormLayout::FieldRole, idLineEdit);

        nameLabel = new QLabel(formGroupBox);
        nameLabel->setObjectName("nameLabel");

        formLayout->setWidget(1, QFormLayout::LabelRole, nameLabel);

        nameLineEdit = new QLineEdit(formGroupBox);
        nameLineEdit->setObjectName("nameLineEdit");

        formLayout->setWidget(1, QFormLayout::FieldRole, nameLineEdit);

        familyNameLabel = new QLabel(formGroupBox);
        familyNameLabel->setObjectName("familyNameLabel");

        formLayout->setWidget(2, QFormLayout::LabelRole, familyNameLabel);

        familyNameLineEdit = new QLineEdit(formGroupBox);
        familyNameLineEdit->setObjectName("familyNameLineEdit");

        formLayout->setWidget(2, QFormLayout::FieldRole, familyNameLineEdit);

        cinLabel = new QLabel(formGroupBox);
        cinLabel->setObjectName("cinLabel");

        formLayout->setWidget(3, QFormLayout::LabelRole, cinLabel);

        cinLineEdit = new QLineEdit(formGroupBox);
        cinLineEdit->setObjectName("cinLineEdit");

        formLayout->setWidget(3, QFormLayout::FieldRole, cinLineEdit);

        specialityLabel = new QLabel(formGroupBox);
        specialityLabel->setObjectName("specialityLabel");

        formLayout->setWidget(4, QFormLayout::LabelRole, specialityLabel);

        specialityLineEdit = new QLineEdit(formGroupBox);
        specialityLineEdit->setObjectName("specialityLineEdit");

        formLayout->setWidget(4, QFormLayout::FieldRole, specialityLineEdit);

        noteLabel = new QLabel(formGroupBox);
        noteLabel->setObjectName("noteLabel");

        formLayout->setWidget(5, QFormLayout::LabelRole, noteLabel);

        noteSpinBox = new QDoubleSpinBox(formGroupBox);
        noteSpinBox->setObjectName("noteSpinBox");
        noteSpinBox->setMaximum(20.000000000000000);

        formLayout->setWidget(5, QFormLayout::FieldRole, noteSpinBox);

        genderLabel = new QLabel(formGroupBox);
        genderLabel->setObjectName("genderLabel");

        formLayout->setWidget(6, QFormLayout::LabelRole, genderLabel);

        genderComboBox = new QComboBox(formGroupBox);
        genderComboBox->addItem(QString());
        genderComboBox->addItem(QString());
        genderComboBox->setObjectName("genderComboBox");

        formLayout->setWidget(6, QFormLayout::FieldRole, genderComboBox);

        phoneLabel = new QLabel(formGroupBox);
        phoneLabel->setObjectName("phoneLabel");

        formLayout->setWidget(7, QFormLayout::LabelRole, phoneLabel);

        phoneLineEdit = new QLineEdit(formGroupBox);
        phoneLineEdit->setObjectName("phoneLineEdit");

        formLayout->setWidget(7, QFormLayout::FieldRole, phoneLineEdit);

        emailLabel = new QLabel(formGroupBox);
        emailLabel->setObjectName("emailLabel");

        formLayout->setWidget(8, QFormLayout::LabelRole, emailLabel);

        emailLineEdit = new QLineEdit(formGroupBox);
        emailLineEdit->setObjectName("emailLineEdit");

        formLayout->setWidget(8, QFormLayout::FieldRole, emailLineEdit);

        birthDateLabel = new QLabel(formGroupBox);
        birthDateLabel->setObjectName("birthDateLabel");

        formLayout->setWidget(9, QFormLayout::LabelRole, birthDateLabel);

        birthDateEdit = new QDateEdit(formGroupBox);
        birthDateEdit->setObjectName("birthDateEdit");
        birthDateEdit->setCalendarPopup(true);

        formLayout->setWidget(9, QFormLayout::FieldRole, birthDateEdit);

        photoLabel = new QLabel(formGroupBox);
        photoLabel->setObjectName("photoLabel");

        formLayout->setWidget(10, QFormLayout::LabelRole, photoLabel);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        photoPathLineEdit = new QLineEdit(formGroupBox);
        photoPathLineEdit->setObjectName("photoPathLineEdit");
        photoPathLineEdit->setReadOnly(true);

        horizontalLayout_2->addWidget(photoPathLineEdit);

        browseButton = new QPushButton(formGroupBox);
        browseButton->setObjectName("browseButton");

        horizontalLayout_2->addWidget(browseButton);


        formLayout->setLayout(10, QFormLayout::FieldRole, horizontalLayout_2);

        photoPreviewLabel = new QLabel(formGroupBox);
        photoPreviewLabel->setObjectName("photoPreviewLabel");
        photoPreviewLabel->setMinimumSize(QSize(150, 150));
        photoPreviewLabel->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(11, QFormLayout::FieldRole, photoPreviewLabel);


        verticalLayout_2->addWidget(formGroupBox);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        addButton = new QPushButton(studentTab);
        addButton->setObjectName("addButton");

        horizontalLayout_3->addWidget(addButton);

        updateButton = new QPushButton(studentTab);
        updateButton->setObjectName("updateButton");

        horizontalLayout_3->addWidget(updateButton);

        deleteButton = new QPushButton(studentTab);
        deleteButton->setObjectName("deleteButton");

        horizontalLayout_3->addWidget(deleteButton);

        clearButton = new QPushButton(studentTab);
        clearButton->setObjectName("clearButton");

        horizontalLayout_3->addWidget(clearButton);


        verticalLayout_2->addLayout(horizontalLayout_3);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        searchLabel = new QLabel(studentTab);
        searchLabel->setObjectName("searchLabel");

        horizontalLayout_4->addWidget(searchLabel);

        searchLineEdit = new QLineEdit(studentTab);
        searchLineEdit->setObjectName("searchLineEdit");

        horizontalLayout_4->addWidget(searchLineEdit);

        searchButton = new QPushButton(studentTab);
        searchButton->setObjectName("searchButton");

        horizontalLayout_4->addWidget(searchButton);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        sortLabel = new QLabel(studentTab);
        sortLabel->setObjectName("sortLabel");

        horizontalLayout_5->addWidget(sortLabel);

        sortButton = new QPushButton(studentTab);
        sortButton->setObjectName("sortButton");

        horizontalLayout_5->addWidget(sortButton);


        verticalLayout_3->addLayout(horizontalLayout_5);

        studentTableView = new QTableView(studentTab);
        studentTableView->setObjectName("studentTableView");
        studentTableView->setSelectionMode(QAbstractItemView::SingleSelection);
        studentTableView->setSelectionBehavior(QAbstractItemView::SelectRows);

        verticalLayout_3->addWidget(studentTableView);


        horizontalLayout->addLayout(verticalLayout_3);

        tabWidget->addTab(studentTab, QString());
        statsTab = new QWidget();
        statsTab->setObjectName("statsTab");
        verticalLayout_4 = new QVBoxLayout(statsTab);
        verticalLayout_4->setObjectName("verticalLayout_4");
        statsLabel = new QLabel(statsTab);
        statsLabel->setObjectName("statsLabel");
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        statsLabel->setFont(font);
        statsLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(statsLabel);

        chartWidget = new QWidget(statsTab);
        chartWidget->setObjectName("chartWidget");
        chartWidget->setMinimumSize(QSize(0, 400));

        verticalLayout_4->addWidget(chartWidget);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);

        refreshStatsButton = new QPushButton(statsTab);
        refreshStatsButton->setObjectName("refreshStatsButton");

        horizontalLayout_6->addWidget(refreshStatsButton);

        exportPdfButton = new QPushButton(statsTab);
        exportPdfButton->setObjectName("exportPdfButton");

        horizontalLayout_6->addWidget(exportPdfButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_2);


        verticalLayout_4->addLayout(horizontalLayout_6);

        tabWidget->addTab(statsTab, QString());

        verticalLayout->addWidget(tabWidget);


        retranslateUi(EtudiantDialog);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(EtudiantDialog);
    } // setupUi

    void retranslateUi(QDialog *EtudiantDialog)
    {
        EtudiantDialog->setWindowTitle(QCoreApplication::translate("EtudiantDialog", "Gestion des \303\211tudiants", nullptr));
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
        addButton->setText(QCoreApplication::translate("EtudiantDialog", "Ajouter", nullptr));
        updateButton->setText(QCoreApplication::translate("EtudiantDialog", "Modifier", nullptr));
        deleteButton->setText(QCoreApplication::translate("EtudiantDialog", "Supprimer", nullptr));
        clearButton->setText(QCoreApplication::translate("EtudiantDialog", "Effacer", nullptr));
        searchLabel->setText(QCoreApplication::translate("EtudiantDialog", "Rechercher:", nullptr));
        searchButton->setText(QCoreApplication::translate("EtudiantDialog", "Chercher", nullptr));
        sortLabel->setText(QCoreApplication::translate("EtudiantDialog", "Trier par nom:", nullptr));
        sortButton->setText(QCoreApplication::translate("EtudiantDialog", "Trier", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(studentTab), QCoreApplication::translate("EtudiantDialog", "\303\211tudiants", nullptr));
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
