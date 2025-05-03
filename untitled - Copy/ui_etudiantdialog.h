/********************************************************************************
** Form generated from reading UI file 'etudiantdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ETUDIANTDIALOG_H
#define UI_ETUDIANTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EduSmartDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *mainTab;
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
    QPushButton *documentationButton;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *infoGroupBox;
    QFormLayout *formLayout;
    QLabel *nameLabel;
    QLabel *nameValueLabel;
    QLabel *firstNameLabel;
    QLabel *firstNameValueLabel;
    QLabel *noteLabel;
    QLabel *noteValueLabel;
    QLabel *cinLabel;
    QLabel *cinValueLabel;
    QLabel *specialityLabel;
    QLabel *specialityValueLabel;
    QLabel *genderLabel;
    QLabel *genderValueLabel;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *addButton;
    QPushButton *updateButton;
    QPushButton *deleteButton;
    QPushButton *browseButton;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *idGroupBox;
    QFormLayout *formLayout_2;
    QLabel *idLabel;
    QLabel *idValueLabel;
    QLabel *tierLabel;
    QLabel *tierValueLabel;
    QLabel *expertifLabel;
    QLabel *expertifValueLabel;
    QLabel *recoverLabel;
    QLabel *recoverValueLabel;
    QHBoxLayout *horizontalLayout_4;
    QLabel *searchLabel;
    QLineEdit *searchLineEdit;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *checkletButton;
    QPushButton *exportPdfButton;
    QPushButton *statsButton;

    void setupUi(QDialog *EduSmartDialog)
    {
        if (EduSmartDialog->objectName().isEmpty())
            EduSmartDialog->setObjectName("EduSmartDialog");
        EduSmartDialog->resize(900, 662);
        EduSmartDialog->setStyleSheet(QString::fromUtf8("background-image: url(:/resources/background.png);"));
        verticalLayout = new QVBoxLayout(EduSmartDialog);
        verticalLayout->setObjectName("verticalLayout");
        tabWidget = new QTabWidget(EduSmartDialog);
        tabWidget->setObjectName("tabWidget");
        mainTab = new QWidget();
        mainTab->setObjectName("mainTab");
        horizontalLayout = new QHBoxLayout(mainTab);
        horizontalLayout->setObjectName("horizontalLayout");
        sidebarFrame = new QFrame(mainTab);
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
        homeButton->setCheckable(true);
        homeButton->setChecked(false);
        employeeButton = new QPushButton(sidebarFrame);
        employeeButton->setObjectName("employeeButton");
        employeeButton->setGeometry(QRect(30, 290, 201, 41));
        employeeButton->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        employeeButton->setCheckable(true);
        employeeButton->setChecked(true);
        centerButton = new QPushButton(sidebarFrame);
        centerButton->setObjectName("centerButton");
        centerButton->setGeometry(QRect(30, 350, 201, 41));
        centerButton->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        centerButton->setCheckable(true);
        centerButton->setChecked(false);
        examButton = new QPushButton(sidebarFrame);
        examButton->setObjectName("examButton");
        examButton->setGeometry(QRect(30, 410, 201, 41));
        examButton->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        examButton->setCheckable(true);
        examButton->setChecked(false);
        studentButton = new QPushButton(sidebarFrame);
        studentButton->setObjectName("studentButton");
        studentButton->setGeometry(QRect(30, 470, 201, 41));
        studentButton->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        studentButton->setCheckable(true);
        studentButton->setChecked(false);
        materialButton = new QPushButton(sidebarFrame);
        materialButton->setObjectName("materialButton");
        materialButton->setGeometry(QRect(30, 530, 201, 41));
        materialButton->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        materialButton->setCheckable(true);
        materialButton->setChecked(false);
        trainingButton = new QPushButton(sidebarFrame);
        trainingButton->setObjectName("trainingButton");
        trainingButton->setGeometry(QRect(30, 590, 201, 41));
        trainingButton->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        trainingButton->setCheckable(true);
        trainingButton->setChecked(false);
        documentationButton = new QPushButton(sidebarFrame);
        documentationButton->setObjectName("documentationButton");
        documentationButton->setGeometry(QRect(30, 650, 201, 41));
        documentationButton->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        documentationButton->setCheckable(true);
        documentationButton->setChecked(false);

        horizontalLayout->addWidget(sidebarFrame);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        infoGroupBox = new QGroupBox(mainTab);
        infoGroupBox->setObjectName("infoGroupBox");
        infoGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox{background-image: url(:/resources/background.png);}"));
        formLayout = new QFormLayout(infoGroupBox);
        formLayout->setObjectName("formLayout");
        nameLabel = new QLabel(infoGroupBox);
        nameLabel->setObjectName("nameLabel");
        QFont font;
        font.setFamilies({QString::fromUtf8("Perpetua")});
        font.setPointSize(12);
        font.setBold(true);
        font.setItalic(true);
        nameLabel->setFont(font);
        nameLabel->setStyleSheet(QString::fromUtf8("color:#030C54;border:none;"));

        formLayout->setWidget(0, QFormLayout::LabelRole, nameLabel);

        nameValueLabel = new QLabel(infoGroupBox);
        nameValueLabel->setObjectName("nameValueLabel");
        nameValueLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        formLayout->setWidget(0, QFormLayout::FieldRole, nameValueLabel);

        firstNameLabel = new QLabel(infoGroupBox);
        firstNameLabel->setObjectName("firstNameLabel");
        firstNameLabel->setFont(font);
        firstNameLabel->setStyleSheet(QString::fromUtf8("color:#030C54;border:none;"));

        formLayout->setWidget(1, QFormLayout::LabelRole, firstNameLabel);

        firstNameValueLabel = new QLabel(infoGroupBox);
        firstNameValueLabel->setObjectName("firstNameValueLabel");
        firstNameValueLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        formLayout->setWidget(1, QFormLayout::FieldRole, firstNameValueLabel);

        noteLabel = new QLabel(infoGroupBox);
        noteLabel->setObjectName("noteLabel");
        noteLabel->setFont(font);
        noteLabel->setStyleSheet(QString::fromUtf8("color:#030C54;border:none;"));

        formLayout->setWidget(2, QFormLayout::LabelRole, noteLabel);

        noteValueLabel = new QLabel(infoGroupBox);
        noteValueLabel->setObjectName("noteValueLabel");
        noteValueLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        formLayout->setWidget(2, QFormLayout::FieldRole, noteValueLabel);

        cinLabel = new QLabel(infoGroupBox);
        cinLabel->setObjectName("cinLabel");
        cinLabel->setFont(font);
        cinLabel->setStyleSheet(QString::fromUtf8("color:#030C54;border:none;"));

        formLayout->setWidget(3, QFormLayout::LabelRole, cinLabel);

        cinValueLabel = new QLabel(infoGroupBox);
        cinValueLabel->setObjectName("cinValueLabel");
        cinValueLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        formLayout->setWidget(3, QFormLayout::FieldRole, cinValueLabel);

        specialityLabel = new QLabel(infoGroupBox);
        specialityLabel->setObjectName("specialityLabel");
        specialityLabel->setFont(font);
        specialityLabel->setStyleSheet(QString::fromUtf8("color:#030C54;border:none;"));

        formLayout->setWidget(4, QFormLayout::LabelRole, specialityLabel);

        specialityValueLabel = new QLabel(infoGroupBox);
        specialityValueLabel->setObjectName("specialityValueLabel");
        specialityValueLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        formLayout->setWidget(4, QFormLayout::FieldRole, specialityValueLabel);

        genderLabel = new QLabel(infoGroupBox);
        genderLabel->setObjectName("genderLabel");
        genderLabel->setFont(font);
        genderLabel->setStyleSheet(QString::fromUtf8("color:#030C54;border:none;"));

        formLayout->setWidget(5, QFormLayout::LabelRole, genderLabel);

        genderValueLabel = new QLabel(infoGroupBox);
        genderValueLabel->setObjectName("genderValueLabel");
        genderValueLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        formLayout->setWidget(5, QFormLayout::FieldRole, genderValueLabel);


        verticalLayout_2->addWidget(infoGroupBox);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        addButton = new QPushButton(mainTab);
        addButton->setObjectName("addButton");
        addButton->setStyleSheet(QString::fromUtf8("border:1px solid white;border-radius:20px;background-color:#030C54;color:white;background-image: url(:/resources/background.png);"));

        horizontalLayout_3->addWidget(addButton);

        updateButton = new QPushButton(mainTab);
        updateButton->setObjectName("updateButton");
        updateButton->setStyleSheet(QString::fromUtf8("border:1px solid white;border-radius:20px;background-color:#030C54;color:white;background-image: url(:/resources/background.png);"));

        horizontalLayout_3->addWidget(updateButton);

        deleteButton = new QPushButton(mainTab);
        deleteButton->setObjectName("deleteButton");
        deleteButton->setStyleSheet(QString::fromUtf8("border:1px solid white;border-radius:20px;background-color:#030C54;color:white;background-image: url(:/resources/background.png);"));

        horizontalLayout_3->addWidget(deleteButton);

        browseButton = new QPushButton(mainTab);
        browseButton->setObjectName("browseButton");
        browseButton->setStyleSheet(QString::fromUtf8("border:1px solid white;border-radius:20px;background-color:#030C54;color:white;background-image: url(:/resources/background.png);"));

        horizontalLayout_3->addWidget(browseButton);


        verticalLayout_2->addLayout(horizontalLayout_3);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        idGroupBox = new QGroupBox(mainTab);
        idGroupBox->setObjectName("idGroupBox");
        idGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox{background-image: url(:/resources/background.png);}"));
        formLayout_2 = new QFormLayout(idGroupBox);
        formLayout_2->setObjectName("formLayout_2");
        idLabel = new QLabel(idGroupBox);
        idLabel->setObjectName("idLabel");
        idLabel->setFont(font);
        idLabel->setStyleSheet(QString::fromUtf8("color:#030C54;border:none;"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, idLabel);

        idValueLabel = new QLabel(idGroupBox);
        idValueLabel->setObjectName("idValueLabel");
        idValueLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, idValueLabel);

        tierLabel = new QLabel(idGroupBox);
        tierLabel->setObjectName("tierLabel");
        tierLabel->setFont(font);
        tierLabel->setStyleSheet(QString::fromUtf8("color:#030C54;border:none;"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, tierLabel);

        tierValueLabel = new QLabel(idGroupBox);
        tierValueLabel->setObjectName("tierValueLabel");
        tierValueLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, tierValueLabel);

        expertifLabel = new QLabel(idGroupBox);
        expertifLabel->setObjectName("expertifLabel");
        expertifLabel->setFont(font);
        expertifLabel->setStyleSheet(QString::fromUtf8("color:#030C54;border:none;"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, expertifLabel);

        expertifValueLabel = new QLabel(idGroupBox);
        expertifValueLabel->setObjectName("expertifValueLabel");
        expertifValueLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, expertifValueLabel);

        recoverLabel = new QLabel(idGroupBox);
        recoverLabel->setObjectName("recoverLabel");
        recoverLabel->setFont(font);
        recoverLabel->setStyleSheet(QString::fromUtf8("color:#030C54;border:none;"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, recoverLabel);

        recoverValueLabel = new QLabel(idGroupBox);
        recoverValueLabel->setObjectName("recoverValueLabel");
        recoverValueLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        formLayout_2->setWidget(3, QFormLayout::FieldRole, recoverValueLabel);


        verticalLayout_3->addWidget(idGroupBox);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        searchLabel = new QLabel(mainTab);
        searchLabel->setObjectName("searchLabel");
        searchLabel->setFont(font);
        searchLabel->setStyleSheet(QString::fromUtf8("color:#030C54;border:none;"));

        horizontalLayout_4->addWidget(searchLabel);

        searchLineEdit = new QLineEdit(mainTab);
        searchLineEdit->setObjectName("searchLineEdit");
        searchLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        horizontalLayout_4->addWidget(searchLineEdit);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        checkletButton = new QPushButton(mainTab);
        checkletButton->setObjectName("checkletButton");
        checkletButton->setStyleSheet(QString::fromUtf8("border:1px solid white;border-radius:20px;background-color:#030C54;color:white;background-image: url(:/resources/background.png);"));

        horizontalLayout_5->addWidget(checkletButton);

        exportPdfButton = new QPushButton(mainTab);
        exportPdfButton->setObjectName("exportPdfButton");
        exportPdfButton->setStyleSheet(QString::fromUtf8("border:1px solid white;border-radius:20px;background-color:#030C54;color:white;background-image: url(:/resources/background.png);"));

        horizontalLayout_5->addWidget(exportPdfButton);

        statsButton = new QPushButton(mainTab);
        statsButton->setObjectName("statsButton");
        statsButton->setStyleSheet(QString::fromUtf8("border:1px solid white;border-radius:20px;background-color:#030C54;color:white;background-image: url(:/resources/background.png);"));

        horizontalLayout_5->addWidget(statsButton);


        verticalLayout_3->addLayout(horizontalLayout_5);


        horizontalLayout->addLayout(verticalLayout_3);

        tabWidget->addTab(mainTab, QString());

        verticalLayout->addWidget(tabWidget);


        retranslateUi(EduSmartDialog);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(EduSmartDialog);
    } // setupUi

    void retranslateUi(QDialog *EduSmartDialog)
    {
        EduSmartDialog->setWindowTitle(QCoreApplication::translate("EduSmartDialog", "EduSmart", nullptr));
        logoLabel->setText(QString());
        homeButton->setText(QCoreApplication::translate("EduSmartDialog", "\360\237\217\240 Home", nullptr));
        employeeButton->setText(QCoreApplication::translate("EduSmartDialog", "\360\237\221\250\342\200\215\360\237\222\274 Employ\303\251", nullptr));
        centerButton->setText(QCoreApplication::translate("EduSmartDialog", "\360\237\217\253 Centre", nullptr));
        examButton->setText(QCoreApplication::translate("EduSmartDialog", "\360\237\223\235 Examen", nullptr));
        studentButton->setText(QCoreApplication::translate("EduSmartDialog", "\360\237\216\223 Dualiant", nullptr));
        materialButton->setText(QCoreApplication::translate("EduSmartDialog", "\360\237\247\260 Material", nullptr));
        trainingButton->setText(QCoreApplication::translate("EduSmartDialog", "\360\237\223\232 Formation", nullptr));
        documentationButton->setText(QCoreApplication::translate("EduSmartDialog", "\360\237\223\204 Documentation", nullptr));
        infoGroupBox->setTitle(QCoreApplication::translate("EduSmartDialog", "Informations", nullptr));
        nameLabel->setText(QCoreApplication::translate("EduSmartDialog", "Nom:", nullptr));
        firstNameLabel->setText(QCoreApplication::translate("EduSmartDialog", "Pr\303\251nom:", nullptr));
        noteLabel->setText(QCoreApplication::translate("EduSmartDialog", "Note:", nullptr));
        cinLabel->setText(QCoreApplication::translate("EduSmartDialog", "CIN:", nullptr));
        specialityLabel->setText(QCoreApplication::translate("EduSmartDialog", "Sp\303\251cialit\303\251:", nullptr));
        genderLabel->setText(QCoreApplication::translate("EduSmartDialog", "Genre:", nullptr));
        genderValueLabel->setText(QCoreApplication::translate("EduSmartDialog", "Homme", nullptr));
        addButton->setText(QCoreApplication::translate("EduSmartDialog", "Ajouter", nullptr));
        updateButton->setText(QCoreApplication::translate("EduSmartDialog", "Modifier", nullptr));
        deleteButton->setText(QCoreApplication::translate("EduSmartDialog", "Supprimer", nullptr));
        browseButton->setText(QCoreApplication::translate("EduSmartDialog", "Parcourir...", nullptr));
        idGroupBox->setTitle(QCoreApplication::translate("EduSmartDialog", "Identification", nullptr));
        idLabel->setText(QCoreApplication::translate("EduSmartDialog", "Id:", nullptr));
        tierLabel->setText(QCoreApplication::translate("EduSmartDialog", "Tier:", nullptr));
        expertifLabel->setText(QCoreApplication::translate("EduSmartDialog", "Expertif:", nullptr));
        recoverLabel->setText(QCoreApplication::translate("EduSmartDialog", "R\303\251cup\303\251rer:", nullptr));
        searchLabel->setText(QCoreApplication::translate("EduSmartDialog", "Rechercher :", nullptr));
        checkletButton->setText(QCoreApplication::translate("EduSmartDialog", "Checklet", nullptr));
        exportPdfButton->setText(QCoreApplication::translate("EduSmartDialog", "Exporter PDF", nullptr));
        statsButton->setText(QCoreApplication::translate("EduSmartDialog", "Statistique", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(mainTab), QCoreApplication::translate("EduSmartDialog", "Menu Principal", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EduSmartDialog: public Ui_EduSmartDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ETUDIANTDIALOG_H
