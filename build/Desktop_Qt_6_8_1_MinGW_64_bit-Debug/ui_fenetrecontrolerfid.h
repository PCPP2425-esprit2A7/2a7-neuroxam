/********************************************************************************
** Form generated from reading UI file 'fenetrecontrolerfid.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FENETRECONTROLERFID_H
#define UI_FENETRECONTROLERFID_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FenetreControleRFID
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelTitre;
    QLabel *labelUID;
    QLabel *labelStatut;
    QListWidget *listWidgetUIDs;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnOuvrir;
    QPushButton *btnFermer;

    void setupUi(QDialog *FenetreControleRFID)
    {
        if (FenetreControleRFID->objectName().isEmpty())
            FenetreControleRFID->setObjectName("FenetreControleRFID");
        FenetreControleRFID->resize(600, 500);
        FenetreControleRFID->setStyleSheet(QString::fromUtf8("\n"
"    QDialog {\n"
"        background-color: qlineargradient(x1:0, y1:0, x2:1, y2:1,\n"
"            stop:0 #f0f8ff, stop:1 #cce7ff);\n"
"    }\n"
"    QLabel#labelTitre {\n"
"        font-size: 20pt;\n"
"        font-weight: bold;\n"
"        color: #003366;\n"
"    }\n"
"    QLabel#labelUID, QLabel#labelStatut {\n"
"        font-size: 14pt;\n"
"        font-weight: bold;\n"
"    }\n"
"    QListWidget {\n"
"        background: #ffffff;\n"
"        border: 2px solid #cccccc;\n"
"        font-size: 12pt;\n"
"        padding: 6px;\n"
"    }\n"
"    QPushButton {\n"
"        font-size: 14pt;\n"
"        font-weight: bold;\n"
"        padding: 8px 16px;\n"
"        border-radius: 10px;\n"
"    }\n"
"    QPushButton#btnOuvrir {\n"
"        background-color: #00ccff;\n"
"        color: white;\n"
"    }\n"
"    QPushButton#btnFermer {\n"
"        background-color: #ff3333;\n"
"        color: white;\n"
"    }\n"
"    QPushButton:hover {\n"
"        background-color: #3399ff;\n"
"    }\n"
"   "));
        verticalLayout = new QVBoxLayout(FenetreControleRFID);
        verticalLayout->setObjectName("verticalLayout");
        labelTitre = new QLabel(FenetreControleRFID);
        labelTitre->setObjectName("labelTitre");
        labelTitre->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelTitre);

        labelUID = new QLabel(FenetreControleRFID);
        labelUID->setObjectName("labelUID");
        labelUID->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelUID);

        labelStatut = new QLabel(FenetreControleRFID);
        labelStatut->setObjectName("labelStatut");
        labelStatut->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelStatut);

        listWidgetUIDs = new QListWidget(FenetreControleRFID);
        listWidgetUIDs->setObjectName("listWidgetUIDs");

        verticalLayout->addWidget(listWidgetUIDs);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        btnOuvrir = new QPushButton(FenetreControleRFID);
        btnOuvrir->setObjectName("btnOuvrir");

        horizontalLayout->addWidget(btnOuvrir);

        btnFermer = new QPushButton(FenetreControleRFID);
        btnFermer->setObjectName("btnFermer");

        horizontalLayout->addWidget(btnFermer);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(FenetreControleRFID);

        QMetaObject::connectSlotsByName(FenetreControleRFID);
    } // setupUi

    void retranslateUi(QDialog *FenetreControleRFID)
    {
        FenetreControleRFID->setWindowTitle(QCoreApplication::translate("FenetreControleRFID", "\360\237\224\222 Contr\303\264le RFID et Porte", nullptr));
        labelTitre->setText(QCoreApplication::translate("FenetreControleRFID", "\360\237\224\220 Lecture RFID et Ouverture Porte", nullptr));
        labelUID->setText(QCoreApplication::translate("FenetreControleRFID", "UID Scann\303\251 : ---", nullptr));
        labelStatut->setText(QCoreApplication::translate("FenetreControleRFID", "Statut Porte : ---", nullptr));
        btnOuvrir->setText(QCoreApplication::translate("FenetreControleRFID", "\360\237\224\223 Ouvrir Manuellement", nullptr));
        btnFermer->setText(QCoreApplication::translate("FenetreControleRFID", "\360\237\224\222 Fermer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FenetreControleRFID: public Ui_FenetreControleRFID {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FENETRECONTROLERFID_H
