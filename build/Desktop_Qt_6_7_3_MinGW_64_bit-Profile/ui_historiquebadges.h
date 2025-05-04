/********************************************************************************
** Form generated from reading UI file 'historiquebadges.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HISTORIQUEBADGES_H
#define UI_HISTORIQUEBADGES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_HistoriqueBadges
{
public:
    QVBoxLayout *verticalLayoutMain;
    QLabel *labelTitre;
    QHBoxLayout *filterLayout;
    QLabel *labelFiltre;
    QLineEdit *lineEditFiltre;
    QPushButton *btnFiltrer;
    QPushButton *btnSupprimer;
    QTableView *tableViewHistorique;
    QLabel *labelStats;
    QVBoxLayout *verticalLayoutGraph;
    QPushButton *btnFermer;

    void setupUi(QDialog *HistoriqueBadges)
    {
        if (HistoriqueBadges->objectName().isEmpty())
            HistoriqueBadges->setObjectName("HistoriqueBadges");
        HistoriqueBadges->resize(900, 700);
        HistoriqueBadges->setStyleSheet(QString::fromUtf8("\n"
"    QDialog {\n"
"        background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #f0f8ff, stop:1 #cce7ff);\n"
"    }\n"
"    QLabel#labelTitre {\n"
"        font-size: 26pt;\n"
"        font-weight: bold;\n"
"        color: #003366;\n"
"    }\n"
"    QLabel#labelStats {\n"
"        font-size: 13pt;\n"
"        font-weight: bold;\n"
"        color: #004d80;\n"
"    }\n"
"    QPushButton {\n"
"        background-color: #007acc;\n"
"        color: white;\n"
"        border-radius: 10px;\n"
"        padding: 8px 16px;\n"
"        font-size: 12pt;\n"
"        font-weight: bold;\n"
"    }\n"
"    QPushButton:hover {\n"
"        background-color: #005f99;\n"
"    }\n"
"    QLineEdit {\n"
"        border: 1px solid #5aa6d9;\n"
"        border-radius: 6px;\n"
"        padding: 5px;\n"
"        font-size: 11pt;\n"
"    }\n"
"    QTableView {\n"
"        border: 1px solid #5aa6d9;\n"
"        gridline-color: #5aa6d9;\n"
"        background-color: #ffffff;\n"
"        alternate-background-color: #e6f2ff;\n"
"    "
                        "    font-size: 12pt;\n"
"    }\n"
"   "));
        verticalLayoutMain = new QVBoxLayout(HistoriqueBadges);
        verticalLayoutMain->setObjectName("verticalLayoutMain");
        labelTitre = new QLabel(HistoriqueBadges);
        labelTitre->setObjectName("labelTitre");
        labelTitre->setAlignment(Qt::AlignCenter);

        verticalLayoutMain->addWidget(labelTitre);

        filterLayout = new QHBoxLayout();
        filterLayout->setObjectName("filterLayout");
        labelFiltre = new QLabel(HistoriqueBadges);
        labelFiltre->setObjectName("labelFiltre");

        filterLayout->addWidget(labelFiltre);

        lineEditFiltre = new QLineEdit(HistoriqueBadges);
        lineEditFiltre->setObjectName("lineEditFiltre");

        filterLayout->addWidget(lineEditFiltre);

        btnFiltrer = new QPushButton(HistoriqueBadges);
        btnFiltrer->setObjectName("btnFiltrer");

        filterLayout->addWidget(btnFiltrer);

        btnSupprimer = new QPushButton(HistoriqueBadges);
        btnSupprimer->setObjectName("btnSupprimer");

        filterLayout->addWidget(btnSupprimer);


        verticalLayoutMain->addLayout(filterLayout);

        tableViewHistorique = new QTableView(HistoriqueBadges);
        tableViewHistorique->setObjectName("tableViewHistorique");

        verticalLayoutMain->addWidget(tableViewHistorique);

        labelStats = new QLabel(HistoriqueBadges);
        labelStats->setObjectName("labelStats");
        labelStats->setAlignment(Qt::AlignLeft);

        verticalLayoutMain->addWidget(labelStats);

        verticalLayoutGraph = new QVBoxLayout();
        verticalLayoutGraph->setObjectName("verticalLayoutGraph");

        verticalLayoutMain->addLayout(verticalLayoutGraph);

        btnFermer = new QPushButton(HistoriqueBadges);
        btnFermer->setObjectName("btnFermer");

        verticalLayoutMain->addWidget(btnFermer, 0, Qt::AlignRight);


        retranslateUi(HistoriqueBadges);

        QMetaObject::connectSlotsByName(HistoriqueBadges);
    } // setupUi

    void retranslateUi(QDialog *HistoriqueBadges)
    {
        HistoriqueBadges->setWindowTitle(QCoreApplication::translate("HistoriqueBadges", "Historique des Badges", nullptr));
        labelTitre->setText(QCoreApplication::translate("HistoriqueBadges", "\360\237\223\212 Historique des Badges", nullptr));
        labelFiltre->setText(QCoreApplication::translate("HistoriqueBadges", "\360\237\224\216 Filtrer :", nullptr));
        lineEditFiltre->setPlaceholderText(QCoreApplication::translate("HistoriqueBadges", "Saisir un badge, formateur ou date...", nullptr));
        btnFiltrer->setText(QCoreApplication::translate("HistoriqueBadges", "Filtrer", nullptr));
        btnSupprimer->setText(QCoreApplication::translate("HistoriqueBadges", "\360\237\227\221\357\270\217 Supprimer", nullptr));
        labelStats->setText(QCoreApplication::translate("HistoriqueBadges", "\360\237\223\210 Total : 0 entr\303\251es | 0 sorties", nullptr));
        btnFermer->setText(QCoreApplication::translate("HistoriqueBadges", "\360\237\232\252 Fermer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HistoriqueBadges: public Ui_HistoriqueBadges {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HISTORIQUEBADGES_H
