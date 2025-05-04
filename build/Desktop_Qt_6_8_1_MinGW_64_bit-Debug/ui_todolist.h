/********************************************************************************
** Form generated from reading UI file 'todolist.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TODOLIST_H
#define UI_TODOLIST_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TodoList
{
public:
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEditTache;
    QDateEdit *dateEditLimite;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnAjouterTache;
    QPushButton *btnTerminerTache;
    QPushButton *btnSupprimerTache;
    QCheckBox *checkBoxActives;
    QTableView *tableViewTaches;
    QLabel *labelStatsTaches;

    void setupUi(QDialog *TodoList)
    {
        if (TodoList->objectName().isEmpty())
            TodoList->setObjectName("TodoList");
        TodoList->setStyleSheet(QString::fromUtf8("\n"
"    QWidget {\n"
"        background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"            stop:0 #DCEEFF, stop:1 #ffffff);\n"
"        font-family: \"Segoe UI\";\n"
"        font-size: 12pt;\n"
"    }\n"
"\n"
"    QLineEdit, QDateEdit {\n"
"        padding: 8px;\n"
"        border: 1px solid #cccccc;\n"
"        border-radius: 8px;\n"
"        background-color: #f8f9fa;\n"
"    }\n"
"\n"
"    QPushButton {\n"
"        background-color: #4A90E2;\n"
"        color: white;\n"
"        font-weight: bold;\n"
"        padding: 8px 16px;\n"
"        border-radius: 10px;\n"
"    }\n"
"\n"
"    QPushButton:hover {\n"
"        background-color: #357ABD;\n"
"    }\n"
"\n"
"    QTableView {\n"
"        border: 1px solid #CCCCCC;\n"
"        border-radius: 8px;\n"
"        background-color: #ffffff;\n"
"        gridline-color: #E0E0E0;\n"
"        selection-background-color: #D6EAF8;\n"
"        alternate-background-color: #F7FBFF;\n"
"    }\n"
"\n"
"    QCheckBox {\n"
"        font-weight: bold;\n"
"       "
                        " padding: 4px;\n"
"    }\n"
"\n"
"    QLabel {\n"
"        font-size: 11pt;\n"
"        font-weight: bold;\n"
"        color: #333;\n"
"        padding: 4px;\n"
"    }\n"
"   "));
        verticalLayout = new QVBoxLayout(TodoList);
        verticalLayout->setObjectName("verticalLayout");
        lineEditTache = new QLineEdit(TodoList);
        lineEditTache->setObjectName("lineEditTache");

        verticalLayout->addWidget(lineEditTache);

        dateEditLimite = new QDateEdit(TodoList);
        dateEditLimite->setObjectName("dateEditLimite");
        dateEditLimite->setCalendarPopup(true);
        dateEditLimite->setDate(QDate(0, 0, 0));

        verticalLayout->addWidget(dateEditLimite);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        btnAjouterTache = new QPushButton(TodoList);
        btnAjouterTache->setObjectName("btnAjouterTache");

        horizontalLayout->addWidget(btnAjouterTache);

        btnTerminerTache = new QPushButton(TodoList);
        btnTerminerTache->setObjectName("btnTerminerTache");

        horizontalLayout->addWidget(btnTerminerTache);

        btnSupprimerTache = new QPushButton(TodoList);
        btnSupprimerTache->setObjectName("btnSupprimerTache");

        horizontalLayout->addWidget(btnSupprimerTache);


        verticalLayout->addLayout(horizontalLayout);

        checkBoxActives = new QCheckBox(TodoList);
        checkBoxActives->setObjectName("checkBoxActives");

        verticalLayout->addWidget(checkBoxActives);

        tableViewTaches = new QTableView(TodoList);
        tableViewTaches->setObjectName("tableViewTaches");
        tableViewTaches->setAlternatingRowColors(true);
        tableViewTaches->setSelectionBehavior(QAbstractItemView::SelectRows);

        verticalLayout->addWidget(tableViewTaches);

        labelStatsTaches = new QLabel(TodoList);
        labelStatsTaches->setObjectName("labelStatsTaches");

        verticalLayout->addWidget(labelStatsTaches);


        retranslateUi(TodoList);

        QMetaObject::connectSlotsByName(TodoList);
    } // setupUi

    void retranslateUi(QDialog *TodoList)
    {
        TodoList->setWindowTitle(QCoreApplication::translate("TodoList", "\360\237\223\235 Liste des T\303\242ches", nullptr));
        lineEditTache->setPlaceholderText(QCoreApplication::translate("TodoList", "Entrez une nouvelle t\303\242che...", nullptr));
        dateEditLimite->setDisplayFormat(QCoreApplication::translate("TodoList", "dd/MM/yyyy", nullptr));
        btnAjouterTache->setText(QCoreApplication::translate("TodoList", "\342\236\225 Ajouter", nullptr));
        btnTerminerTache->setText(QCoreApplication::translate("TodoList", "\342\234\224\357\270\217 Terminer", nullptr));
        btnSupprimerTache->setText(QCoreApplication::translate("TodoList", "\360\237\227\221\357\270\217 Supprimer", nullptr));
        checkBoxActives->setText(QCoreApplication::translate("TodoList", "\360\237\224\216 Afficher uniquement les t\303\242ches actives", nullptr));
        labelStatsTaches->setText(QCoreApplication::translate("TodoList", "\360\237\223\212 Actives: 0 | \342\234\205 Termin\303\251es: 0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TodoList: public Ui_TodoList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TODOLIST_H
