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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox_2;
    QPushButton *cherchebut;
    QLabel *label_23;
    QPushButton *sup;
    QPushButton *pdf;
    QLineEdit *cherche;
    QLineEdit *idedit;
    QFrame *frame;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QLabel *label;
    QPushButton *stat;
    QWidget *widget;
    QPushButton *ajoute;
    QLineEdit *centre_examen;
    QLineEdit *matiere;
    QLabel *label_32;
    QLabel *label_28;
    QLabel *label_27;
    QLineEdit *type_examen;
    QLabel *label_30;
    QLabel *label_29;
    QPushButton *modifier;
    QLineEdit *heure_examen;
    QDateEdit *date_examen;
    QTableView *aff;
    QPushButton *recuperer;
    QPushButton *tri;
    QComboBox *trie;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1248, 728);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        QFont font;
        font.setPointSize(12);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        groupBox_2->setFont(font);
        groupBox_2->setStyleSheet(QString::fromUtf8("QGroupBox{\n"
"	background-image: url(:/res/resources/background.png);\n"
"}\n"
""));
        cherchebut = new QPushButton(groupBox_2);
        cherchebut->setObjectName("cherchebut");
        cherchebut->setGeometry(QRect(580, 380, 131, 41));
        cherchebut->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white;\n"
"background-image: url(:/res/resources/background.png);"));
        label_23 = new QLabel(groupBox_2);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(240, 380, 151, 41));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Perpetua")});
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setItalic(true);
        font1.setUnderline(false);
        label_23->setFont(font1);
        label_23->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        sup = new QPushButton(groupBox_2);
        sup->setObjectName("sup");
        sup->setGeometry(QRect(990, 260, 91, 41));
        sup->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white;\n"
"background-image: url(:/res/resources/background.png);"));
        pdf = new QPushButton(groupBox_2);
        pdf->setObjectName("pdf");
        pdf->setGeometry(QRect(950, 330, 131, 41));
        pdf->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white;\n"
"background-image: url(:/res/resources/background.png);"));
        cherche = new QLineEdit(groupBox_2);
        cherche->setObjectName("cherche");
        cherche->setGeometry(QRect(340, 380, 201, 41));
        cherche->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(6, 6, 4);"));
        idedit = new QLineEdit(groupBox_2);
        idedit->setObjectName("idedit");
        idedit->setGeometry(QRect(890, 185, 171, 51));
        idedit->setStyleSheet(QString::fromUtf8("color: rgb(6, 6, 6);\n"
"background-color: rgb(255, 255, 255);"));
        frame = new QFrame(groupBox_2);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, -50, 231, 861));
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
""));
        pushButton_2 = new QPushButton(frame);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(10, 350, 201, 41));
        pushButton_2->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/res/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        pushButton_3 = new QPushButton(frame);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(10, 410, 201, 41));
        pushButton_3->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/res/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        pushButton_4 = new QPushButton(frame);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(10, 470, 201, 41));
        pushButton_4->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/res/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        pushButton_5 = new QPushButton(frame);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(10, 530, 201, 41));
        pushButton_5->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/res/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        pushButton_6 = new QPushButton(frame);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(10, 650, 201, 41));
        pushButton_6->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/res/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        pushButton_7 = new QPushButton(frame);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(10, 590, 201, 41));
        pushButton_7->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/res/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        pushButton_8 = new QPushButton(frame);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(10, 290, 201, 41));
        pushButton_8->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/res/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        pushButton_9 = new QPushButton(frame);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setGeometry(QRect(10, 230, 201, 41));
        pushButton_9->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/res/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 90, 171, 111));
        label->setStyleSheet(QString::fromUtf8("\n"
"image: url(:/res/resources/image_2025-01-29_201537391-removebg-preview.png);"));
        stat = new QPushButton(groupBox_2);
        stat->setObjectName("stat");
        stat->setGeometry(QRect(950, 380, 131, 41));
        stat->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white;\n"
"background-image: url(:/res/resources/background.png);"));
        widget = new QWidget(groupBox_2);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(240, 70, 631, 271));
        ajoute = new QPushButton(widget);
        ajoute->setObjectName("ajoute");
        ajoute->setGeometry(QRect(450, 190, 131, 41));
        ajoute->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white;\n"
"background-image: url(:/res/resources/background.png);"));
        centre_examen = new QLineEdit(widget);
        centre_examen->setObjectName("centre_examen");
        centre_examen->setGeometry(QRect(360, 80, 201, 81));
        centre_examen->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(6, 6, 6);\n"
""));
        matiere = new QLineEdit(widget);
        matiere->setObjectName("matiere");
        matiere->setGeometry(QRect(160, 140, 141, 26));
        matiere->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);\n"
"\n"
""));
        label_32 = new QLabel(widget);
        label_32->setObjectName("label_32");
        label_32->setGeometry(QRect(20, 200, 101, 31));
        label_32->setFont(font1);
        label_32->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        label_28 = new QLabel(widget);
        label_28->setObjectName("label_28");
        label_28->setGeometry(QRect(10, 80, 111, 31));
        label_28->setFont(font1);
        label_28->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        label_27 = new QLabel(widget);
        label_27->setObjectName("label_27");
        label_27->setGeometry(QRect(10, 30, 111, 31));
        label_27->setFont(font1);
        label_27->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        type_examen = new QLineEdit(widget);
        type_examen->setObjectName("type_examen");
        type_examen->setGeometry(QRect(160, 200, 141, 26));
        type_examen->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(11, 11, 11);\n"
""));
        label_30 = new QLabel(widget);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(370, 40, 151, 31));
        label_30->setFont(font1);
        label_30->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        label_29 = new QLabel(widget);
        label_29->setObjectName("label_29");
        label_29->setGeometry(QRect(20, 140, 101, 31));
        label_29->setFont(font1);
        label_29->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        modifier = new QPushButton(widget);
        modifier->setObjectName("modifier");
        modifier->setGeometry(QRect(330, 190, 101, 41));
        modifier->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white;\n"
"background-image: url(:/res/resources/background.png);"));
        heure_examen = new QLineEdit(widget);
        heure_examen->setObjectName("heure_examen");
        heure_examen->setGeometry(QRect(160, 80, 141, 26));
        heure_examen->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);\n"
"\n"
""));
        date_examen = new QDateEdit(widget);
        date_examen->setObjectName("date_examen");
        date_examen->setGeometry(QRect(170, 30, 110, 26));
        date_examen->setStyleSheet(QString::fromUtf8("color: rgb(7, 7, 7);\n"
"background-color: rgb(255, 255, 255);"));
        aff = new QTableView(groupBox_2);
        aff->setObjectName("aff");
        aff->setGeometry(QRect(240, 431, 841, 251));
        aff->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        recuperer = new QPushButton(groupBox_2);
        recuperer->setObjectName("recuperer");
        recuperer->setGeometry(QRect(880, 260, 101, 41));
        recuperer->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white;\n"
"background-image: url(:/res/resources/background.png);"));
        tri = new QPushButton(groupBox_2);
        tri->setObjectName("tri");
        tri->setGeometry(QRect(760, 380, 131, 41));
        tri->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white;\n"
"background-image: url(:/res/resources/background.png);"));
        trie = new QComboBox(groupBox_2);
        trie->addItem(QString());
        trie->addItem(QString());
        trie->setObjectName("trie");
        trie->setGeometry(QRect(760, 350, 121, 21));
        trie->setStyleSheet(QString::fromUtf8("color: rgb(9, 9, 9);\n"
"background-color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(groupBox_2);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox_2->setTitle(QString());
        cherchebut->setText(QCoreApplication::translate("MainWindow", "Chercher", nullptr));
        label_23->setText(QCoreApplication::translate("MainWindow", "Chercher  : ", nullptr));
        sup->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        pdf->setText(QCoreApplication::translate("MainWindow", "PDF", nullptr));
        cherche->setText(QString());
        cherche->setPlaceholderText(QString());
        idedit->setPlaceholderText(QCoreApplication::translate("MainWindow", "taper id", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Centre", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Examen", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Etudiant", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "Materiel", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "  Deconnexion", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "Formation", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "Employes", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "Home", nullptr));
        label->setText(QString());
        stat->setText(QCoreApplication::translate("MainWindow", "statistique", nullptr));
        ajoute->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        label_32->setText(QCoreApplication::translate("MainWindow", "type_examen", nullptr));
        label_28->setText(QCoreApplication::translate("MainWindow", "heure_examen", nullptr));
        label_27->setText(QCoreApplication::translate("MainWindow", "date_examen", nullptr));
        label_30->setText(QCoreApplication::translate("MainWindow", "centre_examen", nullptr));
        label_29->setText(QCoreApplication::translate("MainWindow", "matiere", nullptr));
        modifier->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        recuperer->setText(QCoreApplication::translate("MainWindow", "recuperer", nullptr));
        tri->setText(QCoreApplication::translate("MainWindow", "tri", nullptr));
        trie->setItemText(0, QCoreApplication::translate("MainWindow", "id_examen", nullptr));
        trie->setItemText(1, QCoreApplication::translate("MainWindow", "date_examen", nullptr));

    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
