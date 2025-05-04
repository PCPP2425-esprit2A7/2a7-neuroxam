/********************************************************************************
** Form generated from reading UI file 'dialogrecherche.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGRECHERCHE_H
#define UI_DIALOGRECHERCHE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogRecherche
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelTitre;
    QLineEdit *lineEditSujet;
    QListWidget *listWidgetSuggestions;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnReset;
    QPushButton *btnFermer;

    void setupUi(QDialog *DialogRecherche)
    {
        if (DialogRecherche->objectName().isEmpty())
            DialogRecherche->setObjectName("DialogRecherche");
        DialogRecherche->resize(600, 460);
        DialogRecherche->setStyleSheet(QString::fromUtf8("\n"
"    QDialog {\n"
"        background-color: #e3f2fd;\n"
"        border-radius: 12px;\n"
"    }\n"
"\n"
"    QLabel#labelTitre {\n"
"        font-size: 20px;\n"
"        font-weight: bold;\n"
"        color: #2c3e50;\n"
"        padding: 8px;\n"
"        qproperty-alignment: AlignCenter;\n"
"        border-bottom: 2px solid #64b5f6;\n"
"    }\n"
"\n"
"    QLineEdit {\n"
"        font-size: 14px;\n"
"        padding: 10px;\n"
"        border: 2px solid #90caf9;\n"
"        border-radius: 8px;\n"
"        background-color: #ffffff;\n"
"    }\n"
"\n"
"    QListWidget {\n"
"        background-color: #ffffff;\n"
"        border: 1px solid #ccc;\n"
"        border-radius: 8px;\n"
"        font-size: 13px;\n"
"        padding: 6px;\n"
"    }\n"
"\n"
"    QListWidget::item {\n"
"        padding: 6px;\n"
"        margin-bottom: 4px;\n"
"        border-radius: 6px;\n"
"        background-color: #f2f2f2;\n"
"    }\n"
"\n"
"    QListWidget::item:hover {\n"
"        background-color: #d0e8ff;\n"
"    }\n"
"\n"
"    QL"
                        "istWidget::item:selected {\n"
"        background-color: #42a5f5;\n"
"        color: white;\n"
"        font-weight: bold;\n"
"    }\n"
"\n"
"    QPushButton {\n"
"        font-size: 14px;\n"
"        padding: 8px 14px;\n"
"        border: none;\n"
"        border-radius: 8px;\n"
"        background-color: #64b5f6;\n"
"        color: white;\n"
"    }\n"
"\n"
"    QPushButton:hover {\n"
"        background-color: #42a5f5;\n"
"    }\n"
"\n"
"    QPushButton#btnFermer {\n"
"        background-color: #ef5350;\n"
"    }\n"
"\n"
"    QPushButton#btnFermer:hover {\n"
"        background-color: #d32f2f;\n"
"    }\n"
"\n"
"    QPushButton#btnReset {\n"
"        background-color: #81c784;\n"
"    }\n"
"\n"
"    QPushButton#btnReset:hover {\n"
"        background-color: #66bb6a;\n"
"    }\n"
"   "));
        verticalLayout = new QVBoxLayout(DialogRecherche);
        verticalLayout->setObjectName("verticalLayout");
        labelTitre = new QLabel(DialogRecherche);
        labelTitre->setObjectName("labelTitre");

        verticalLayout->addWidget(labelTitre);

        lineEditSujet = new QLineEdit(DialogRecherche);
        lineEditSujet->setObjectName("lineEditSujet");
        lineEditSujet->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));

        verticalLayout->addWidget(lineEditSujet);

        listWidgetSuggestions = new QListWidget(DialogRecherche);
        listWidgetSuggestions->setObjectName("listWidgetSuggestions");
        listWidgetSuggestions->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));

        verticalLayout->addWidget(listWidgetSuggestions);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        btnReset = new QPushButton(DialogRecherche);
        btnReset->setObjectName("btnReset");

        horizontalLayout->addWidget(btnReset);

        btnFermer = new QPushButton(DialogRecherche);
        btnFermer->setObjectName("btnFermer");

        horizontalLayout->addWidget(btnFermer);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(DialogRecherche);

        QMetaObject::connectSlotsByName(DialogRecherche);
    } // setupUi

    void retranslateUi(QDialog *DialogRecherche)
    {
        DialogRecherche->setWindowTitle(QCoreApplication::translate("DialogRecherche", "\360\237\224\216 Recherche de formation", nullptr));
        labelTitre->setText(QCoreApplication::translate("DialogRecherche", "\360\237\224\215 Rechercher par crit\303\250re", nullptr));
#if QT_CONFIG(tooltip)
        lineEditSujet->setToolTip(QCoreApplication::translate("DialogRecherche", "Tapez un mot-cl\303\251 ou un crit\303\250re de recherche", nullptr));
#endif // QT_CONFIG(tooltip)
        lineEditSujet->setPlaceholderText(QCoreApplication::translate("DialogRecherche", "\360\237\224\216 Sujet, ID, date (dd/MM/yyyy) ou statut (Pr\303\251vue, En cours...)", nullptr));
        btnReset->setText(QCoreApplication::translate("DialogRecherche", "\360\237\224\201 R\303\251initialiser", nullptr));
        btnFermer->setText(QCoreApplication::translate("DialogRecherche", "\342\235\214 Fermer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogRecherche: public Ui_DialogRecherche {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGRECHERCHE_H
