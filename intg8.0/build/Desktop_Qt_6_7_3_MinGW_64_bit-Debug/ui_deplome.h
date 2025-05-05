/********************************************************************************
** Form generated from reading UI file 'deplome.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEPLOME_H
#define UI_DEPLOME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Deplome
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelTitre;
    QLineEdit *lineEditIdFormation;
    QPushButton *btnRechercherFormation;
    QLabel *labelSujet;
    QLabel *labelDate;
    QLabel *labelHeure;
    QLabel *labelDuree;
    QLabel *labelNomEmploye;
    QComboBox *comboBoxEmploye;
    QPushButton *btnChoisirImage;
    QLabel *labelImage;
    QPushButton *btnValider;
    QPushButton *btnOuvrirHistorique;

    void setupUi(QDialog *Deplome)
    {
        if (Deplome->objectName().isEmpty())
            Deplome->setObjectName("Deplome");
        Deplome->setStyleSheet(QString::fromUtf8("\n"
"    QWidget {\n"
"        background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"            stop:0 #DCEEFF, stop:1 #ffffff);\n"
"        font-family: \"Segoe UI\";\n"
"        font-size: 12pt;\n"
"    }\n"
"\n"
"    QLineEdit, QLabel {\n"
"        padding: 6px;\n"
"    }\n"
"\n"
"    QPushButton {\n"
"        background-color: #4A90E2;\n"
"        color: white;\n"
"        font-weight: bold;\n"
"        padding: 10px 20px;\n"
"        border-radius: 10px;\n"
"    }\n"
"\n"
"    QPushButton:hover {\n"
"        background-color: #357ABD;\n"
"    }\n"
"\n"
"    QLabel {\n"
"        font-weight: bold;\n"
"        color: #333333;\n"
"    }\n"
"   "));
        verticalLayout = new QVBoxLayout(Deplome);
        verticalLayout->setObjectName("verticalLayout");
        labelTitre = new QLabel(Deplome);
        labelTitre->setObjectName("labelTitre");

        verticalLayout->addWidget(labelTitre);

        lineEditIdFormation = new QLineEdit(Deplome);
        lineEditIdFormation->setObjectName("lineEditIdFormation");

        verticalLayout->addWidget(lineEditIdFormation);

        btnRechercherFormation = new QPushButton(Deplome);
        btnRechercherFormation->setObjectName("btnRechercherFormation");

        verticalLayout->addWidget(btnRechercherFormation);

        labelSujet = new QLabel(Deplome);
        labelSujet->setObjectName("labelSujet");

        verticalLayout->addWidget(labelSujet);

        labelDate = new QLabel(Deplome);
        labelDate->setObjectName("labelDate");

        verticalLayout->addWidget(labelDate);

        labelHeure = new QLabel(Deplome);
        labelHeure->setObjectName("labelHeure");

        verticalLayout->addWidget(labelHeure);

        labelDuree = new QLabel(Deplome);
        labelDuree->setObjectName("labelDuree");

        verticalLayout->addWidget(labelDuree);

        labelNomEmploye = new QLabel(Deplome);
        labelNomEmploye->setObjectName("labelNomEmploye");

        verticalLayout->addWidget(labelNomEmploye);

        comboBoxEmploye = new QComboBox(Deplome);
        comboBoxEmploye->setObjectName("comboBoxEmploye");

        verticalLayout->addWidget(comboBoxEmploye);

        btnChoisirImage = new QPushButton(Deplome);
        btnChoisirImage->setObjectName("btnChoisirImage");

        verticalLayout->addWidget(btnChoisirImage);

        labelImage = new QLabel(Deplome);
        labelImage->setObjectName("labelImage");
        labelImage->setStyleSheet(QString::fromUtf8("color: gray;"));

        verticalLayout->addWidget(labelImage);

        btnValider = new QPushButton(Deplome);
        btnValider->setObjectName("btnValider");

        verticalLayout->addWidget(btnValider);

        btnOuvrirHistorique = new QPushButton(Deplome);
        btnOuvrirHistorique->setObjectName("btnOuvrirHistorique");

        verticalLayout->addWidget(btnOuvrirHistorique);


        retranslateUi(Deplome);

        QMetaObject::connectSlotsByName(Deplome);
    } // setupUi

    void retranslateUi(QDialog *Deplome)
    {
        Deplome->setWindowTitle(QCoreApplication::translate("Deplome", "\360\237\216\223 G\303\251n\303\251ration de Certificat", nullptr));
        labelTitre->setText(QCoreApplication::translate("Deplome", "\360\237\223\235 Entrer l'ID de formation :", nullptr));
        btnRechercherFormation->setText(QCoreApplication::translate("Deplome", "\360\237\224\215 Rechercher la formation", nullptr));
        labelSujet->setText(QCoreApplication::translate("Deplome", "Sujet : ---", nullptr));
        labelDate->setText(QCoreApplication::translate("Deplome", "Date  : ---", nullptr));
        labelHeure->setText(QCoreApplication::translate("Deplome", "Heure : ---", nullptr));
        labelDuree->setText(QCoreApplication::translate("Deplome", "Dur\303\251e : ---", nullptr));
        labelNomEmploye->setText(QCoreApplication::translate("Deplome", "\360\237\221\244 Nom de l'employ\303\251 :", nullptr));
        btnChoisirImage->setText(QCoreApplication::translate("Deplome", "\360\237\226\274\357\270\217 Choisir une image d'en-t\303\252te", nullptr));
        labelImage->setText(QCoreApplication::translate("Deplome", "\360\237\223\201 Aucune image s\303\251lectionn\303\251e", nullptr));
        btnValider->setText(QCoreApplication::translate("Deplome", "\342\234\205 Valider et g\303\251n\303\251rer le certificat", nullptr));
        btnOuvrirHistorique->setText(QCoreApplication::translate("Deplome", "\360\237\223\204 Historique des signatures", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Deplome: public Ui_Deplome {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEPLOME_H
