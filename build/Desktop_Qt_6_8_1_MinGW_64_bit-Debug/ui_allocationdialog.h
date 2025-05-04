/********************************************************************************
** Form generated from reading UI file 'allocationdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALLOCATIONDIALOG_H
#define UI_ALLOCATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_allocationdialog
{
public:
    QComboBox *centerComboBox;
    QLabel *label_7;
    QPushButton *confirmerButton;
    QStackedWidget *stackedWidget;
    QWidget *page1;
    QLabel *ordinateurLabel;
    QLineEdit *ordinateurLineEdit;
    QComboBox *ordinateurEtat;
    QLabel *casqueLabel;
    QLineEdit *casqueLineEdit;
    QLabel *cameraLabel;
    QLineEdit *cameraLineEdit;
    QLabel *scannerLabel;
    QLineEdit *scannerLineEdit;
    QLabel *imprimanteLabel;
    QLineEdit *imprimanteLineEdit;
    QComboBox *cameraDispo;
    QComboBox *casqueaudioDispo;
    QComboBox *ordinateurDispo;
    QComboBox *scannerDispo;
    QComboBox *imprimanteDispo;
    QComboBox *casqueaudioEtat;
    QComboBox *cameraEtat;
    QComboBox *imprimanteEtat;
    QComboBox *scannerEtat;
    QWidget *page2;
    QLabel *clavierLabel;
    QLineEdit *clavierLineEdit;
    QLabel *sourisLabel;
    QLineEdit *sourisLineEdit;
    QLabel *ecranLabel;
    QLineEdit *ecranLineEdit;
    QLabel *routeurLabel;
    QLineEdit *routeurLineEdit;
    QLabel *climatiseurLabel;
    QLineEdit *climatiseurLineEdit;
    QComboBox *climatiseurEtat;
    QComboBox *climatiseurDispo;
    QComboBox *routeurEtat;
    QComboBox *ecranEtat;
    QComboBox *clavierEtat;
    QComboBox *sourisEtat;
    QComboBox *clavierDispo;
    QComboBox *ecranDispo;
    QComboBox *sourisDispo;
    QComboBox *routeurDispo;
    QPushButton *nextButton;
    QPushButton *prevButton;
    QCheckBox *checkIndisponible;
    QCheckBox *checkReparation;
    QPushButton *resetButton;

    void setupUi(QDialog *allocationdialog)
    {
        if (allocationdialog->objectName().isEmpty())
            allocationdialog->setObjectName("allocationdialog");
        allocationdialog->resize(715, 460);
        allocationdialog->setStyleSheet(QString::fromUtf8("background-color: #2f6ab3;"));
        centerComboBox = new QComboBox(allocationdialog);
        centerComboBox->setObjectName("centerComboBox");
        centerComboBox->setGeometry(QRect(270, 30, 211, 28));
        centerComboBox->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        label_7 = new QLabel(allocationdialog);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(200, 30, 63, 20));
        confirmerButton = new QPushButton(allocationdialog);
        confirmerButton->setObjectName("confirmerButton");
        confirmerButton->setGeometry(QRect(300, 410, 131, 29));
        confirmerButton->setStyleSheet(QString::fromUtf8("background-color: #226597;\n"
"color: white;"));
        stackedWidget = new QStackedWidget(allocationdialog);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(60, 110, 571, 211));
        page1 = new QWidget();
        page1->setObjectName("page1");
        ordinateurLabel = new QLabel(page1);
        ordinateurLabel->setObjectName("ordinateurLabel");
        ordinateurLabel->setGeometry(QRect(0, 0, 101, 20));
        ordinateurLineEdit = new QLineEdit(page1);
        ordinateurLineEdit->setObjectName("ordinateurLineEdit");
        ordinateurLineEdit->setGeometry(QRect(130, 0, 100, 28));
        ordinateurEtat = new QComboBox(page1);
        ordinateurEtat->setObjectName("ordinateurEtat");
        ordinateurEtat->setGeometry(QRect(240, 0, 151, 28));
        casqueLabel = new QLabel(page1);
        casqueLabel->setObjectName("casqueLabel");
        casqueLabel->setGeometry(QRect(0, 45, 101, 20));
        casqueLineEdit = new QLineEdit(page1);
        casqueLineEdit->setObjectName("casqueLineEdit");
        casqueLineEdit->setGeometry(QRect(130, 45, 100, 28));
        cameraLabel = new QLabel(page1);
        cameraLabel->setObjectName("cameraLabel");
        cameraLabel->setGeometry(QRect(0, 90, 101, 20));
        cameraLineEdit = new QLineEdit(page1);
        cameraLineEdit->setObjectName("cameraLineEdit");
        cameraLineEdit->setGeometry(QRect(130, 90, 100, 28));
        scannerLabel = new QLabel(page1);
        scannerLabel->setObjectName("scannerLabel");
        scannerLabel->setGeometry(QRect(0, 135, 101, 20));
        scannerLineEdit = new QLineEdit(page1);
        scannerLineEdit->setObjectName("scannerLineEdit");
        scannerLineEdit->setGeometry(QRect(130, 135, 100, 28));
        imprimanteLabel = new QLabel(page1);
        imprimanteLabel->setObjectName("imprimanteLabel");
        imprimanteLabel->setGeometry(QRect(0, 180, 101, 20));
        imprimanteLineEdit = new QLineEdit(page1);
        imprimanteLineEdit->setObjectName("imprimanteLineEdit");
        imprimanteLineEdit->setGeometry(QRect(130, 180, 100, 28));
        cameraDispo = new QComboBox(page1);
        cameraDispo->setObjectName("cameraDispo");
        cameraDispo->setGeometry(QRect(400, 90, 151, 28));
        casqueaudioDispo = new QComboBox(page1);
        casqueaudioDispo->setObjectName("casqueaudioDispo");
        casqueaudioDispo->setGeometry(QRect(400, 45, 151, 28));
        ordinateurDispo = new QComboBox(page1);
        ordinateurDispo->setObjectName("ordinateurDispo");
        ordinateurDispo->setGeometry(QRect(400, 0, 151, 28));
        scannerDispo = new QComboBox(page1);
        scannerDispo->setObjectName("scannerDispo");
        scannerDispo->setGeometry(QRect(400, 135, 151, 28));
        imprimanteDispo = new QComboBox(page1);
        imprimanteDispo->setObjectName("imprimanteDispo");
        imprimanteDispo->setGeometry(QRect(400, 180, 151, 28));
        casqueaudioEtat = new QComboBox(page1);
        casqueaudioEtat->setObjectName("casqueaudioEtat");
        casqueaudioEtat->setGeometry(QRect(240, 45, 151, 28));
        cameraEtat = new QComboBox(page1);
        cameraEtat->setObjectName("cameraEtat");
        cameraEtat->setGeometry(QRect(240, 90, 151, 28));
        imprimanteEtat = new QComboBox(page1);
        imprimanteEtat->setObjectName("imprimanteEtat");
        imprimanteEtat->setGeometry(QRect(240, 180, 151, 28));
        scannerEtat = new QComboBox(page1);
        scannerEtat->setObjectName("scannerEtat");
        scannerEtat->setGeometry(QRect(240, 135, 151, 28));
        stackedWidget->addWidget(page1);
        page2 = new QWidget();
        page2->setObjectName("page2");
        clavierLabel = new QLabel(page2);
        clavierLabel->setObjectName("clavierLabel");
        clavierLabel->setGeometry(QRect(0, 0, 101, 20));
        clavierLineEdit = new QLineEdit(page2);
        clavierLineEdit->setObjectName("clavierLineEdit");
        clavierLineEdit->setGeometry(QRect(130, 0, 100, 28));
        sourisLabel = new QLabel(page2);
        sourisLabel->setObjectName("sourisLabel");
        sourisLabel->setGeometry(QRect(0, 45, 101, 20));
        sourisLineEdit = new QLineEdit(page2);
        sourisLineEdit->setObjectName("sourisLineEdit");
        sourisLineEdit->setGeometry(QRect(130, 45, 100, 28));
        ecranLabel = new QLabel(page2);
        ecranLabel->setObjectName("ecranLabel");
        ecranLabel->setGeometry(QRect(0, 90, 101, 20));
        ecranLineEdit = new QLineEdit(page2);
        ecranLineEdit->setObjectName("ecranLineEdit");
        ecranLineEdit->setGeometry(QRect(130, 90, 100, 28));
        routeurLabel = new QLabel(page2);
        routeurLabel->setObjectName("routeurLabel");
        routeurLabel->setGeometry(QRect(0, 135, 101, 20));
        routeurLineEdit = new QLineEdit(page2);
        routeurLineEdit->setObjectName("routeurLineEdit");
        routeurLineEdit->setGeometry(QRect(130, 135, 100, 28));
        climatiseurLabel = new QLabel(page2);
        climatiseurLabel->setObjectName("climatiseurLabel");
        climatiseurLabel->setGeometry(QRect(0, 180, 101, 20));
        climatiseurLineEdit = new QLineEdit(page2);
        climatiseurLineEdit->setObjectName("climatiseurLineEdit");
        climatiseurLineEdit->setGeometry(QRect(130, 180, 100, 28));
        climatiseurEtat = new QComboBox(page2);
        climatiseurEtat->setObjectName("climatiseurEtat");
        climatiseurEtat->setGeometry(QRect(240, 180, 151, 28));
        climatiseurDispo = new QComboBox(page2);
        climatiseurDispo->setObjectName("climatiseurDispo");
        climatiseurDispo->setGeometry(QRect(400, 180, 151, 28));
        routeurEtat = new QComboBox(page2);
        routeurEtat->setObjectName("routeurEtat");
        routeurEtat->setGeometry(QRect(240, 135, 151, 28));
        ecranEtat = new QComboBox(page2);
        ecranEtat->setObjectName("ecranEtat");
        ecranEtat->setGeometry(QRect(240, 90, 151, 28));
        clavierEtat = new QComboBox(page2);
        clavierEtat->setObjectName("clavierEtat");
        clavierEtat->setGeometry(QRect(240, 0, 151, 28));
        sourisEtat = new QComboBox(page2);
        sourisEtat->setObjectName("sourisEtat");
        sourisEtat->setGeometry(QRect(240, 45, 151, 28));
        clavierDispo = new QComboBox(page2);
        clavierDispo->setObjectName("clavierDispo");
        clavierDispo->setGeometry(QRect(400, 0, 151, 28));
        ecranDispo = new QComboBox(page2);
        ecranDispo->setObjectName("ecranDispo");
        ecranDispo->setGeometry(QRect(400, 90, 151, 28));
        sourisDispo = new QComboBox(page2);
        sourisDispo->setObjectName("sourisDispo");
        sourisDispo->setGeometry(QRect(400, 45, 151, 28));
        routeurDispo = new QComboBox(page2);
        routeurDispo->setObjectName("routeurDispo");
        routeurDispo->setGeometry(QRect(400, 135, 151, 28));
        stackedWidget->addWidget(page2);
        nextButton = new QPushButton(allocationdialog);
        nextButton->setObjectName("nextButton");
        nextButton->setGeometry(QRect(630, 60, 61, 29));
        nextButton->setStyleSheet(QString::fromUtf8("background-color: #226597;\n"
"color: white;"));
        prevButton = new QPushButton(allocationdialog);
        prevButton->setObjectName("prevButton");
        prevButton->setGeometry(QRect(560, 60, 61, 29));
        prevButton->setStyleSheet(QString::fromUtf8("background-color: #226597;\n"
"color: white;"));
        checkIndisponible = new QCheckBox(allocationdialog);
        checkIndisponible->setObjectName("checkIndisponible");
        checkIndisponible->setGeometry(QRect(220, 370, 311, 26));
        checkReparation = new QCheckBox(allocationdialog);
        checkReparation->setObjectName("checkReparation");
        checkReparation->setGeometry(QRect(220, 340, 321, 26));
        resetButton = new QPushButton(allocationdialog);
        resetButton->setObjectName("resetButton");
        resetButton->setGeometry(QRect(60, 60, 83, 29));
        resetButton->setStyleSheet(QString::fromUtf8("background-color: #226597;\n"
"color: white;"));

        retranslateUi(allocationdialog);
        QObject::connect(nextButton, &QPushButton::clicked, stackedWidget, &QStackedWidget::setCurrentIndex);
        QObject::connect(prevButton, &QPushButton::clicked, stackedWidget, &QStackedWidget::setCurrentIndex);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(allocationdialog);
    } // setupUi

    void retranslateUi(QDialog *allocationdialog)
    {
        allocationdialog->setWindowTitle(QCoreApplication::translate("allocationdialog", "Inventory Allocation", nullptr));
        label_7->setText(QCoreApplication::translate("allocationdialog", "Centre :", nullptr));
        confirmerButton->setText(QCoreApplication::translate("allocationdialog", "Confirmer", nullptr));
        ordinateurLabel->setText(QCoreApplication::translate("allocationdialog", "Ordinateur", nullptr));
        ordinateurLineEdit->setPlaceholderText(QCoreApplication::translate("allocationdialog", "Quantit\303\251", nullptr));
        casqueLabel->setText(QCoreApplication::translate("allocationdialog", "Casque Audio", nullptr));
        casqueLineEdit->setPlaceholderText(QCoreApplication::translate("allocationdialog", "Quantit\303\251", nullptr));
        cameraLabel->setText(QCoreApplication::translate("allocationdialog", "Camera", nullptr));
        cameraLineEdit->setPlaceholderText(QCoreApplication::translate("allocationdialog", "Quantit\303\251", nullptr));
        scannerLabel->setText(QCoreApplication::translate("allocationdialog", "Scanner", nullptr));
        scannerLineEdit->setPlaceholderText(QCoreApplication::translate("allocationdialog", "Quantit\303\251", nullptr));
        imprimanteLabel->setText(QCoreApplication::translate("allocationdialog", "Imprimante", nullptr));
        imprimanteLineEdit->setPlaceholderText(QCoreApplication::translate("allocationdialog", "Quantit\303\251", nullptr));
        clavierLabel->setText(QCoreApplication::translate("allocationdialog", "Clavier", nullptr));
        clavierLineEdit->setPlaceholderText(QCoreApplication::translate("allocationdialog", "Quantit\303\251", nullptr));
        sourisLabel->setText(QCoreApplication::translate("allocationdialog", "Souris", nullptr));
        sourisLineEdit->setPlaceholderText(QCoreApplication::translate("allocationdialog", "Quantit\303\251", nullptr));
        ecranLabel->setText(QCoreApplication::translate("allocationdialog", "Ecran", nullptr));
        ecranLineEdit->setPlaceholderText(QCoreApplication::translate("allocationdialog", "Quantit\303\251", nullptr));
        routeurLabel->setText(QCoreApplication::translate("allocationdialog", "Routeur", nullptr));
        routeurLineEdit->setPlaceholderText(QCoreApplication::translate("allocationdialog", "Quantit\303\251", nullptr));
        climatiseurLabel->setText(QCoreApplication::translate("allocationdialog", "Climatiseur", nullptr));
        climatiseurLineEdit->setPlaceholderText(QCoreApplication::translate("allocationdialog", "Quantit\303\251", nullptr));
        nextButton->setText(QCoreApplication::translate("allocationdialog", "\342\206\222", nullptr));
        prevButton->setText(QCoreApplication::translate("allocationdialog", "\342\206\220", nullptr));
        checkIndisponible->setText(QCoreApplication::translate("allocationdialog", "Ne pas inclure les mat\303\251riaux \"Indisponibles\"", nullptr));
        checkReparation->setText(QCoreApplication::translate("allocationdialog", "Ne pas inclure les mat\303\251riaux \"En R\303\251paration\"", nullptr));
        resetButton->setText(QCoreApplication::translate("allocationdialog", "Reset", nullptr));
    } // retranslateUi

};

namespace Ui {
    class allocationdialog: public Ui_allocationdialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALLOCATIONDIALOG_H
