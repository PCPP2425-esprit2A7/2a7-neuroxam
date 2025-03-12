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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_2;
    QFrame *frame;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QLabel *label_3;
    QGroupBox *groupBox;
    QLabel *nom_7;
    QLabel *prenom2;
    QLabel *email1;
    QLabel *password2;
    QLabel *numero_telephone1;
    QLabel *date;
    QLineEdit *nom;
    QLineEdit *numero_telephone;
    QLineEdit *email;
    QLineEdit *prenom;
    QLineEdit *password;
    QPushButton *ajoute;
    QPushButton *modifier;
    QLineEdit *idedit;
    QPushButton *recuperer;
    QPushButton *supprimer;
    QLineEdit *telephoneError;
    QLineEdit *prenomError;
    QDateEdit *date_dembauche;
    QLabel *label_5;
    QTableView *aff;
    QLineEdit *nomeror;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(880, 941);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(-700, -630, 1701, 2181));
        label->setStyleSheet(QString::fromUtf8("image: url(:/res/resources/back.jpeg);"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(-590, -720, 1681, 2351));
        label_2->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix1/resources/back.jpeg);"));
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(-10, -20, 191, 1041));
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
""));
        pushButton_2 = new QPushButton(frame);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(10, 350, 151, 41));
        pushButton_2->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        pushButton_3 = new QPushButton(frame);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(10, 410, 161, 41));
        pushButton_3->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        pushButton_4 = new QPushButton(frame);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(10, 470, 161, 41));
        pushButton_4->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        pushButton_5 = new QPushButton(frame);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(10, 530, 161, 41));
        pushButton_5->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        pushButton_6 = new QPushButton(frame);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(10, 650, 161, 41));
        pushButton_6->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        pushButton_7 = new QPushButton(frame);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(10, 590, 161, 41));
        pushButton_7->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        pushButton_8 = new QPushButton(frame);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(10, 290, 151, 41));
        pushButton_8->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        pushButton_9 = new QPushButton(frame);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setGeometry(QRect(10, 230, 151, 41));
        pushButton_9->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(30, 100, 111, 121));
        label_3->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix1/resources/475038336_657821386805867_9178055062394887346_n__1_-removebg-preview.png);"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(210, 30, 341, 531));
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center;  /* Center the title */\n"
"    padding: 0 10px;\n"
"    the title */\n"
"    color: black;\n"
"    font-weight: bold;\n"
"    border-radius: 4px;\n"
"}\n"
"QGroupBox {\n"
"    background-color: transparent;  /* Transparent to blend with the rest of the interface */\n"
"    border: 2px solid rgba(rgb(25, 25, 25));  /* Yellow border to match the rest */\n"
"    border-radius: 8px;\n"
"    margin-top: 10px;\n"
"    padding: 10px;\n"
"}\n"
""));
        nom_7 = new QLabel(groupBox);
        nom_7->setObjectName("nom_7");
        nom_7->setGeometry(QRect(20, 70, 61, 31));
        QFont font;
        font.setFamilies({QString::fromUtf8("Perpetua")});
        font.setPointSize(12);
        font.setBold(true);
        font.setItalic(true);
        font.setUnderline(false);
        nom_7->setFont(font);
        nom_7->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        prenom2 = new QLabel(groupBox);
        prenom2->setObjectName("prenom2");
        prenom2->setGeometry(QRect(20, 110, 61, 31));
        prenom2->setFont(font);
        prenom2->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        email1 = new QLabel(groupBox);
        email1->setObjectName("email1");
        email1->setGeometry(QRect(20, 150, 61, 31));
        email1->setFont(font);
        email1->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        password2 = new QLabel(groupBox);
        password2->setObjectName("password2");
        password2->setGeometry(QRect(20, 190, 81, 31));
        password2->setFont(font);
        password2->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        numero_telephone1 = new QLabel(groupBox);
        numero_telephone1->setObjectName("numero_telephone1");
        numero_telephone1->setGeometry(QRect(20, 230, 161, 31));
        numero_telephone1->setFont(font);
        numero_telephone1->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        date = new QLabel(groupBox);
        date->setObjectName("date");
        date->setGeometry(QRect(20, 270, 151, 31));
        date->setFont(font);
        date->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        nom = new QLineEdit(groupBox);
        nom->setObjectName("nom");
        nom->setGeometry(QRect(90, 70, 231, 26));
        nom->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"\n"
""));
        numero_telephone = new QLineEdit(groupBox);
        numero_telephone->setObjectName("numero_telephone");
        numero_telephone->setGeometry(QRect(180, 240, 141, 26));
        numero_telephone->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"\n"
""));
        email = new QLineEdit(groupBox);
        email->setObjectName("email");
        email->setGeometry(QRect(110, 150, 211, 26));
        email->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"\n"
""));
        prenom = new QLineEdit(groupBox);
        prenom->setObjectName("prenom");
        prenom->setGeometry(QRect(110, 110, 211, 26));
        prenom->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"\n"
""));
        password = new QLineEdit(groupBox);
        password->setObjectName("password");
        password->setGeometry(QRect(120, 190, 201, 26));
        password->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"\n"
""));
        ajoute = new QPushButton(groupBox);
        ajoute->setObjectName("ajoute");
        ajoute->setGeometry(QRect(20, 320, 131, 41));
        ajoute->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white;\n"
"background-image: url(:/resources/background.png);"));
        ajoute->setCheckable(true);
        ajoute->setChecked(true);
        modifier = new QPushButton(groupBox);
        modifier->setObjectName("modifier");
        modifier->setGeometry(QRect(180, 320, 131, 41));
        modifier->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white;\n"
"background-image: url(:/resources/background.png);"));
        idedit = new QLineEdit(groupBox);
        idedit->setObjectName("idedit");
        idedit->setGeometry(QRect(60, 400, 201, 41));
        recuperer = new QPushButton(groupBox);
        recuperer->setObjectName("recuperer");
        recuperer->setGeometry(QRect(20, 470, 131, 41));
        recuperer->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white;\n"
"background-image: url(:/resources/background.png);"));
        supprimer = new QPushButton(groupBox);
        supprimer->setObjectName("supprimer");
        supprimer->setGeometry(QRect(170, 470, 131, 41));
        supprimer->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white;\n"
"background-image: url(:/resources/background.png);"));
        telephoneError = new QLineEdit(groupBox);
        telephoneError->setObjectName("telephoneError");
        telephoneError->setGeometry(QRect(20, 250, 141, 16));
        telephoneError->setStyleSheet(QString::fromUtf8("background-color: none;\n"
"border:none;\n"
"color: rgb(255, 12, 12);"));
        telephoneError->setReadOnly(true);
        prenomError = new QLineEdit(groupBox);
        prenomError->setObjectName("prenomError");
        prenomError->setGeometry(QRect(10, 140, 181, 16));
        prenomError->setStyleSheet(QString::fromUtf8("background-color: none;\n"
"border:none;\n"
"color: rgb(255, 12, 12);"));
        prenomError->setReadOnly(true);
        date_dembauche = new QDateEdit(groupBox);
        date_dembauche->setObjectName("date_dembauche");
        date_dembauche->setGeometry(QRect(180, 280, 110, 26));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(610, 180, 251, 311));
        label_5->setStyleSheet(QString::fromUtf8("image: url(:/res/resources/image-removebg-preview (5).png);"));
        aff = new QTableView(centralwidget);
        aff->setObjectName("aff");
        aff->setGeometry(QRect(200, 610, 641, 231));
        nomeror = new QLineEdit(centralwidget);
        nomeror->setObjectName("nomeror");
        nomeror->setGeometry(QRect(620, 610, 261, 16));
        nomeror->setStyleSheet(QString::fromUtf8("background-color: none;\n"
"border:none;\n"
"color: rgb(255, 12, 12);"));
        nomeror->setReadOnly(true);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 880, 26));
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
        label->setText(QString());
        label_2->setText(QString());
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "centre", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "examan", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "etudiant", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "matirail", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "  Deconnexion", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "formation", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "Employes", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "home", nullptr));
        label_3->setText(QString());
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "employe", nullptr));
        nom_7->setText(QCoreApplication::translate("MainWindow", "nom :", nullptr));
        prenom2->setText(QCoreApplication::translate("MainWindow", "prenom:", nullptr));
        email1->setText(QCoreApplication::translate("MainWindow", "email:", nullptr));
        password2->setText(QCoreApplication::translate("MainWindow", "password:", nullptr));
        numero_telephone1->setText(QCoreApplication::translate("MainWindow", "numero_telephone: ", nullptr));
        date->setText(QCoreApplication::translate("MainWindow", "date_dembauche: ", nullptr));
        ajoute->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        modifier->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        idedit->setPlaceholderText(QCoreApplication::translate("MainWindow", "taper id", nullptr));
        recuperer->setText(QCoreApplication::translate("MainWindow", "recuperer", nullptr));
        supprimer->setText(QCoreApplication::translate("MainWindow", "supprimer", nullptr));
        label_5->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
