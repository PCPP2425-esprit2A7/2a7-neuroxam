/********************************************************************************
** Form generated from reading UI file 'fenetrestatsf.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FENETRESTATSF_H
#define UI_FENETRESTATSF_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FenetreStatsF
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelTitreStatistiques;
    QGraphicsView *graphicsViewCamembert;
    QPushButton *btnFermer;

    void setupUi(QDialog *FenetreStatsF)
    {
        if (FenetreStatsF->objectName().isEmpty())
            FenetreStatsF->setObjectName("FenetreStatsF");
        FenetreStatsF->setStyleSheet(QString::fromUtf8("\n"
"    FenetreStatsF {\n"
"        background-color: qlineargradient(x1:0, y1:0, x2:1, y2:1,\n"
"                                          stop:0 #e0f7fa, stop:1 #ffffff);\n"
"        border-radius: 10px;\n"
"    }\n"
"   "));
        verticalLayout = new QVBoxLayout(FenetreStatsF);
        verticalLayout->setObjectName("verticalLayout");
        labelTitreStatistiques = new QLabel(FenetreStatsF);
        labelTitreStatistiques->setObjectName("labelTitreStatistiques");
        labelTitreStatistiques->setAlignment(Qt::AlignCenter);
        labelTitreStatistiques->setStyleSheet(QString::fromUtf8("\n"
"       QLabel {\n"
"           color: #01579b;\n"
"           font-weight: bold;\n"
"           font-size: 18pt;\n"
"           padding: 10px;\n"
"       }\n"
"      "));

        verticalLayout->addWidget(labelTitreStatistiques);

        graphicsViewCamembert = new QGraphicsView(FenetreStatsF);
        graphicsViewCamembert->setObjectName("graphicsViewCamembert");
        graphicsViewCamembert->setMinimumSize(QSize(500, 400));
        graphicsViewCamembert->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsViewCamembert->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsViewCamembert->setStyleSheet(QString::fromUtf8("\n"
"       QGraphicsView {\n"
"           border: 2px solid #4dd0e1;\n"
"           border-radius: 8px;\n"
"           background: #ffffff;\n"
"       }\n"
"      "));

        verticalLayout->addWidget(graphicsViewCamembert);

        btnFermer = new QPushButton(FenetreStatsF);
        btnFermer->setObjectName("btnFermer");
        btnFermer->setMinimumHeight(40);
        btnFermer->setStyleSheet(QString::fromUtf8("\n"
"       QPushButton {\n"
"           background-color: #4dd0e1;\n"
"           color: white;\n"
"           font-weight: bold;\n"
"           font-size: 14px;\n"
"           border-radius: 10px;\n"
"       }\n"
"       QPushButton:hover {\n"
"           background-color: #26c6da;\n"
"       }\n"
"      "));

        verticalLayout->addWidget(btnFermer);


        retranslateUi(FenetreStatsF);

        QMetaObject::connectSlotsByName(FenetreStatsF);
    } // setupUi

    void retranslateUi(QDialog *FenetreStatsF)
    {
        FenetreStatsF->setWindowTitle(QCoreApplication::translate("FenetreStatsF", "\360\237\223\212 Statistiques Formations", nullptr));
        labelTitreStatistiques->setText(QCoreApplication::translate("FenetreStatsF", "\360\237\223\210 Statistiques selon le statut des formations", nullptr));
        btnFermer->setText(QCoreApplication::translate("FenetreStatsF", "\342\235\214 Fermer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FenetreStatsF: public Ui_FenetreStatsF {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FENETRESTATSF_H
