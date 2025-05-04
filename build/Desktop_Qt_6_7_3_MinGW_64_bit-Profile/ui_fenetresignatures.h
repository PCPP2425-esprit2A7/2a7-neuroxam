/********************************************************************************
** Form generated from reading UI file 'fenetresignatures.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FENETRESIGNATURES_H
#define UI_FENETRESIGNATURES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FenetreSignatures
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelTitre;
    QTableView *tableViewSignatures;

    void setupUi(QDialog *FenetreSignatures)
    {
        if (FenetreSignatures->objectName().isEmpty())
            FenetreSignatures->setObjectName("FenetreSignatures");
        FenetreSignatures->resize(1000, 700);
        FenetreSignatures->setStyleSheet(QString::fromUtf8("\n"
"    QDialog {\n"
"        background-color: #E3F2FD;\n"
"    }\n"
"    QLabel {\n"
"        font-size: 22px;\n"
"        font-weight: bold;\n"
"        color: #0D47A1;\n"
"        margin-bottom: 12px;\n"
"    }\n"
"    QTableView {\n"
"        alternate-background-color: #E1F5FE;\n"
"        background-color: #FFFFFF;\n"
"        gridline-color: #90CAF9;\n"
"        font-size: 14px;\n"
"    }\n"
"   "));
        verticalLayout = new QVBoxLayout(FenetreSignatures);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(30, 30, 30, 30);
        labelTitre = new QLabel(FenetreSignatures);
        labelTitre->setObjectName("labelTitre");
        labelTitre->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelTitre);

        tableViewSignatures = new QTableView(FenetreSignatures);
        tableViewSignatures->setObjectName("tableViewSignatures");
        tableViewSignatures->setAlternatingRowColors(true);

        verticalLayout->addWidget(tableViewSignatures);


        retranslateUi(FenetreSignatures);

        QMetaObject::connectSlotsByName(FenetreSignatures);
    } // setupUi

    void retranslateUi(QDialog *FenetreSignatures)
    {
        FenetreSignatures->setWindowTitle(QCoreApplication::translate("FenetreSignatures", "\360\237\247\276 Historique des signatures PDF", nullptr));
        labelTitre->setText(QCoreApplication::translate("FenetreSignatures", "\360\237\223\204 Liste des certificats PDF sign\303\251s", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FenetreSignatures: public Ui_FenetreSignatures {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FENETRESIGNATURES_H
