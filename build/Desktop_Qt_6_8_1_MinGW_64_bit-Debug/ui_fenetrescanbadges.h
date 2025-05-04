/********************************************************************************
** Form generated from reading UI file 'fenetrescanbadges.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FENETRESCANBADGES_H
#define UI_FENETRESCANBADGES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FenetreScanBadges
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelTitre;
    QLabel *labelInstruction;
    QListWidget *listWidgetBadges;
    QPushButton *btnTerminer;

    void setupUi(QDialog *FenetreScanBadges)
    {
        if (FenetreScanBadges->objectName().isEmpty())
            FenetreScanBadges->setObjectName("FenetreScanBadges");
        FenetreScanBadges->resize(550, 480);
        FenetreScanBadges->setStyleSheet(QString::fromUtf8("\n"
"    FenetreScanBadges {\n"
"        background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1,\n"
"            stop:0 rgba(255, 255, 255, 255),\n"
"            stop:1 rgba(173, 216, 230, 255));\n"
"        border-radius: 15px;\n"
"        border: 2px solid #0C3C78;\n"
"    }\n"
"    QLabel#labelTitre {\n"
"        font-size: 24pt;\n"
"        font-weight: bold;\n"
"        color: #1E3C72;\n"
"        text-shadow: 1px 1px #aaa;\n"
"    }\n"
"    QLabel#labelInstruction {\n"
"        font-size: 14pt;\n"
"        color: #2A5CAA;\n"
"        font-style: italic;\n"
"    }\n"
"    QListWidget {\n"
"        background: rgba(255, 255, 255, 220);\n"
"        border: 2px solid #1E3C72;\n"
"        font-size: 12pt;\n"
"        padding: 6px;\n"
"        border-radius: 8px;\n"
"    }\n"
"    QPushButton {\n"
"        font-size: 14pt;\n"
"        font-weight: bold;\n"
"        background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1,\n"
"            stop:0 rgba(0, 123, 255, 200),\n"
"            "
                        "stop:1 rgba(0, 102, 204, 200));\n"
"        color: white;\n"
"        border-radius: 10px;\n"
"        padding: 8px 16px;\n"
"        border: 1px solid #0055AA;\n"
"    }\n"
"    QPushButton:hover {\n"
"        background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1,\n"
"            stop:0 rgba(0, 153, 255, 220),\n"
"            stop:1 rgba(0, 123, 255, 220));\n"
"    }\n"
"   "));
        verticalLayout = new QVBoxLayout(FenetreScanBadges);
        verticalLayout->setObjectName("verticalLayout");
        labelTitre = new QLabel(FenetreScanBadges);
        labelTitre->setObjectName("labelTitre");
        labelTitre->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelTitre);

        labelInstruction = new QLabel(FenetreScanBadges);
        labelInstruction->setObjectName("labelInstruction");
        labelInstruction->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelInstruction);

        listWidgetBadges = new QListWidget(FenetreScanBadges);
        listWidgetBadges->setObjectName("listWidgetBadges");

        verticalLayout->addWidget(listWidgetBadges);

        btnTerminer = new QPushButton(FenetreScanBadges);
        btnTerminer->setObjectName("btnTerminer");

        verticalLayout->addWidget(btnTerminer);


        retranslateUi(FenetreScanBadges);

        QMetaObject::connectSlotsByName(FenetreScanBadges);
    } // setupUi

    void retranslateUi(QDialog *FenetreScanBadges)
    {
        FenetreScanBadges->setWindowTitle(QCoreApplication::translate("FenetreScanBadges", "\360\237\214\237 Enregistrement des Badges RFID \360\237\214\237", nullptr));
        labelTitre->setText(QCoreApplication::translate("FenetreScanBadges", "\342\234\250 Badges RFID \342\234\250", nullptr));
        labelInstruction->setText(QCoreApplication::translate("FenetreScanBadges", "Scannez un badge pour l\342\200\231ajouter", nullptr));
        btnTerminer->setText(QCoreApplication::translate("FenetreScanBadges", "\342\234\205 Terminer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FenetreScanBadges: public Ui_FenetreScanBadges {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FENETRESCANBADGES_H
