/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_9;
    QPushButton *pushButton_add;
    QPushButton *pushButton_modif;
    QPushButton *pushButton_delete;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLineEdit *lineEdit_matiere;
    QLineEdit *lineEdit_type;
    QLabel *label_14;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QLineEdit *lineEdit_centre;
    QPushButton *pushButton_8;
    QDateEdit *dateEdit_examen;
    QTimeEdit *timeEdit_examen;
    QTableView *tableView_examen;
    QLineEdit *id_examen;
    QLabel *label_15;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1732, 1277);
        MainWindow->setMouseTracking(true);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(0, -50, 1731, 1031));
        label->setStyleSheet(QString::fromUtf8("background-image: url(:/res1/image 1.jpg);"));
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(310, 0, 241, 91));
        label_9->setStyleSheet(QString::fromUtf8("image: url(:/res8/logo.png);"));
        pushButton_add = new QPushButton(centralwidget);
        pushButton_add->setObjectName("pushButton_add");
        pushButton_add->setGeometry(QRect(140, 420, 121, 31));
        pushButton_add->setStyleSheet(QString::fromUtf8("background-color: rgb(29, 16, 200);\n"
"font: 600 12pt \"Yu Gothic UI\";\n"
"color: rgb(0, 0, 0);"));
        pushButton_modif = new QPushButton(centralwidget);
        pushButton_modif->setObjectName("pushButton_modif");
        pushButton_modif->setGeometry(QRect(290, 420, 121, 31));
        pushButton_modif->setStyleSheet(QString::fromUtf8("background-color: rgb(29, 16, 200);\n"
"font: 600 12pt \"Yu Gothic UI\";\n"
"color: rgb(0, 0, 0);"));
        pushButton_delete = new QPushButton(centralwidget);
        pushButton_delete->setObjectName("pushButton_delete");
        pushButton_delete->setGeometry(QRect(230, 480, 121, 31));
        pushButton_delete->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 600 12pt \"Yu Gothic UI\";\n"
"background-color: rgb(29, 16, 200);"));
        label_10 = new QLabel(centralwidget);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(150, 140, 81, 20));
        label_10->setStyleSheet(QString::fromUtf8("font: 600 12pt \"Yu Gothic UI\";\n"
"color: rgb(0, 0, 127);"));
        label_11 = new QLabel(centralwidget);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(150, 290, 91, 20));
        label_11->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 127);\n"
"font: 600 12pt \"Yu Gothic UI\";"));
        label_12 = new QLabel(centralwidget);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(150, 190, 71, 20));
        label_12->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 127);\n"
"font: 600 12pt \"Yu Gothic UI\";"));
        label_13 = new QLabel(centralwidget);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(150, 240, 71, 21));
        label_13->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 127);\n"
"font: 600 12pt \"Yu Gothic UI\";"));
        lineEdit_matiere = new QLineEdit(centralwidget);
        lineEdit_matiere->setObjectName("lineEdit_matiere");
        lineEdit_matiere->setGeometry(QRect(260, 140, 113, 28));
        lineEdit_matiere->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(250, 250, 250);"));
        lineEdit_type = new QLineEdit(centralwidget);
        lineEdit_type->setObjectName("lineEdit_type");
        lineEdit_type->setGeometry(QRect(260, 240, 113, 28));
        lineEdit_type->setStyleSheet(QString::fromUtf8("background-color: rgb(250, 250, 250);\n"
"color: rgb(0, 0, 0);"));
        label_14 = new QLabel(centralwidget);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(150, 350, 63, 20));
        label_14->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 127);\n"
"font: 600 12pt \"Yu Gothic UI\";"));
        pushButton_5 = new QPushButton(centralwidget);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(0, 270, 71, 61));
        pushButton_5->setStyleSheet(QString::fromUtf8("image: url(:/res2/image 3.png);\n"
"background-color: rgb(255, 255, 255);"));
        pushButton_6 = new QPushButton(centralwidget);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(0, 180, 71, 71));
        pushButton_6->setStyleSheet(QString::fromUtf8("image: url(:/res3/image 4.png);\n"
"background-color: rgb(255, 255, 255);"));
        pushButton_7 = new QPushButton(centralwidget);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(0, 350, 71, 71));
        pushButton_7->setStyleSheet(QString::fromUtf8("image: url(:/res5/image 6.png);\n"
"background-color: rgb(255, 255, 255);"));
        pushButton_9 = new QPushButton(centralwidget);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setGeometry(QRect(0, 40, 71, 61));
        pushButton_9->setStyleSheet(QString::fromUtf8("image: url(:/res6/image 7.png);\n"
"background-color: rgb(255, 255, 255);"));
        pushButton_10 = new QPushButton(centralwidget);
        pushButton_10->setObjectName("pushButton_10");
        pushButton_10->setGeometry(QRect(0, 110, 71, 61));
        pushButton_10->setStyleSheet(QString::fromUtf8("image: url(:/res7/image 8.png);\n"
"background-color: rgb(255, 255, 255);"));
        lineEdit_centre = new QLineEdit(centralwidget);
        lineEdit_centre->setObjectName("lineEdit_centre");
        lineEdit_centre->setGeometry(QRect(260, 190, 113, 28));
        lineEdit_centre->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(250, 250, 250);"));
        pushButton_8 = new QPushButton(centralwidget);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(0, 440, 71, 61));
        pushButton_8->setStyleSheet(QString::fromUtf8("image: url(:/res/image 2.png);\n"
"background-color: rgb(255, 255, 255);"));
        dateEdit_examen = new QDateEdit(centralwidget);
        dateEdit_examen->setObjectName("dateEdit_examen");
        dateEdit_examen->setGeometry(QRect(260, 290, 111, 29));
        timeEdit_examen = new QTimeEdit(centralwidget);
        timeEdit_examen->setObjectName("timeEdit_examen");
        timeEdit_examen->setGeometry(QRect(260, 350, 118, 29));
        tableView_examen = new QTableView(centralwidget);
        tableView_examen->setObjectName("tableView_examen");
        tableView_examen->setGeometry(QRect(450, 80, 671, 351));
        tableView_examen->setStyleSheet(QString::fromUtf8(""));
        id_examen = new QLineEdit(centralwidget);
        id_examen->setObjectName("id_examen");
        id_examen->setGeometry(QRect(260, 100, 113, 28));
        id_examen->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(250, 250, 250);"));
        label_15 = new QLabel(centralwidget);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(140, 100, 111, 20));
        label_15->setStyleSheet(QString::fromUtf8("font: 600 12pt \"Yu Gothic UI\";\n"
"color: rgb(0, 0, 127);"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1732, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
#if QT_CONFIG(whatsthis)
        MainWindow->setWhatsThis(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        label->setText(QString());
        label_9->setText(QString());
        pushButton_add->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        pushButton_modif->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        pushButton_delete->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Mati\303\250re", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Date", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Centre", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        lineEdit_type->setText(QString());
        label_14->setText(QCoreApplication::translate("MainWindow", "Heure", nullptr));
        pushButton_5->setText(QString());
        pushButton_6->setText(QString());
        pushButton_7->setText(QString());
        pushButton_9->setText(QString());
        pushButton_10->setText(QString());
        pushButton_8->setText(QString());
        label_15->setText(QCoreApplication::translate("MainWindow", "id_examen", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
