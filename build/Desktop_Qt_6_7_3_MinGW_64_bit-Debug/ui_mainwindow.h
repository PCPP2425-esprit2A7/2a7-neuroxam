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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_5;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QLabel *label_23;
    QPushButton *stat;
    QLineEdit *idedit;
    QPushButton *recuperer;
    QPushButton *cherchebut;
    QLineEdit *cherche;
    QTableView *aff;
    QPushButton *pdf;
    QWidget *widget;
    QPushButton *ajoute_2;
    QLineEdit *facilities_2;
    QLineEdit *directeur_2;
    QLabel *label_33;
    QLabel *label_34;
    QLabel *label_35;
    QLabel *label_36;
    QLineEdit *capacite_2;
    QLabel *label_37;
    QLineEdit *adresse_2;
    QLabel *label_38;
    QLineEdit *nom_2;
    QComboBox *status_2;
    QPushButton *modifier_2;
    QLineEdit *nomeror_2;
    QLineEdit *adseror_2;
    QLineEdit *drteror_2;
    QLineEdit *cpteror_2;
    QPushButton *sup;
    QComboBox *trie;
    QPushButton *tri;
    QLineEdit *temp;
    QLabel *label_39;
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
    QPushButton *next;
    QPushButton *chat;
    QPushButton *ard;
    QWidget *page_2;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox_2;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_6;
    QPushButton *back;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1305, 881);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_5 = new QVBoxLayout(centralwidget);
        verticalLayout_5->setSpacing(1);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(1, 1, 1, 0);
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        page = new QWidget();
        page->setObjectName("page");
        page->setStyleSheet(QString::fromUtf8("page{background-image: url(:/resources/background.png);}\n"
""));
        verticalLayout = new QVBoxLayout(page);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(page);
        groupBox->setObjectName("groupBox");
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox{background-image: url(:/resources/background.png);}\n"
""));
        label_23 = new QLabel(groupBox);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(290, 340, 151, 41));
        QFont font;
        font.setFamilies({QString::fromUtf8("Perpetua")});
        font.setPointSize(12);
        font.setBold(true);
        font.setItalic(true);
        font.setUnderline(false);
        label_23->setFont(font);
        label_23->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        stat = new QPushButton(groupBox);
        stat->setObjectName("stat");
        stat->setGeometry(QRect(1010, 345, 131, 41));
        stat->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white;\n"
"background-image: url(:/resources/background.png);"));
        idedit = new QLineEdit(groupBox);
        idedit->setObjectName("idedit");
        idedit->setGeometry(QRect(1050, 220, 171, 31));
        idedit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        recuperer = new QPushButton(groupBox);
        recuperer->setObjectName("recuperer");
        recuperer->setGeometry(QRect(1050, 280, 171, 41));
        recuperer->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white;\n"
"background-image: url(:/resources/background.png);"));
        cherchebut = new QPushButton(groupBox);
        cherchebut->setObjectName("cherchebut");
        cherchebut->setGeometry(QRect(640, 350, 131, 41));
        cherchebut->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white;\n"
"background-image: url(:/resources/background.png);"));
        cherche = new QLineEdit(groupBox);
        cherche->setObjectName("cherche");
        cherche->setGeometry(QRect(430, 345, 201, 41));
        cherche->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        aff = new QTableView(groupBox);
        aff->setObjectName("aff");
        aff->setGeometry(QRect(300, 396, 841, 251));
        aff->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        pdf = new QPushButton(groupBox);
        pdf->setObjectName("pdf");
        pdf->setGeometry(QRect(830, 350, 131, 41));
        pdf->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white;\n"
"background-image: url(:/resources/background.png);"));
        widget = new QWidget(groupBox);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(310, 15, 631, 321));
        ajoute_2 = new QPushButton(widget);
        ajoute_2->setObjectName("ajoute_2");
        ajoute_2->setGeometry(QRect(320, 0, 131, 41));
        ajoute_2->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white;\n"
"background-image: url(:/resources/background.png);"));
        facilities_2 = new QLineEdit(widget);
        facilities_2->setObjectName("facilities_2");
        facilities_2->setGeometry(QRect(150, 220, 141, 21));
        facilities_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);\n"
""));
        directeur_2 = new QLineEdit(widget);
        directeur_2->setObjectName("directeur_2");
        directeur_2->setGeometry(QRect(150, 110, 141, 26));
        directeur_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);\n"
"\n"
""));
        label_33 = new QLabel(widget);
        label_33->setObjectName("label_33");
        label_33->setGeometry(QRect(20, 270, 111, 31));
        label_33->setFont(font);
        label_33->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        label_34 = new QLabel(widget);
        label_34->setObjectName("label_34");
        label_34->setGeometry(QRect(20, 170, 151, 31));
        label_34->setFont(font);
        label_34->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        label_35 = new QLabel(widget);
        label_35->setObjectName("label_35");
        label_35->setGeometry(QRect(20, 50, 121, 31));
        label_35->setFont(font);
        label_35->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        label_36 = new QLabel(widget);
        label_36->setObjectName("label_36");
        label_36->setGeometry(QRect(40, 0, 71, 31));
        label_36->setFont(font);
        label_36->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        capacite_2 = new QLineEdit(widget);
        capacite_2->setObjectName("capacite_2");
        capacite_2->setGeometry(QRect(150, 170, 141, 26));
        capacite_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);\n"
""));
        label_37 = new QLabel(widget);
        label_37->setObjectName("label_37");
        label_37->setGeometry(QRect(20, 230, 121, 21));
        label_37->setFont(font);
        label_37->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        adresse_2 = new QLineEdit(widget);
        adresse_2->setObjectName("adresse_2");
        adresse_2->setGeometry(QRect(150, 50, 141, 26));
        adresse_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);\n"
"\n"
""));
        label_38 = new QLabel(widget);
        label_38->setObjectName("label_38");
        label_38->setGeometry(QRect(20, 110, 111, 31));
        label_38->setFont(font);
        label_38->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        nom_2 = new QLineEdit(widget);
        nom_2->setObjectName("nom_2");
        nom_2->setGeometry(QRect(150, 0, 141, 26));
        nom_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);\n"
"\n"
""));
        status_2 = new QComboBox(widget);
        status_2->addItem(QString());
        status_2->addItem(QString());
        status_2->setObjectName("status_2");
        status_2->setGeometry(QRect(150, 270, 141, 26));
        status_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        modifier_2 = new QPushButton(widget);
        modifier_2->setObjectName("modifier_2");
        modifier_2->setGeometry(QRect(320, 60, 131, 41));
        modifier_2->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white;\n"
"background-image: url(:/resources/background.png);"));
        nomeror_2 = new QLineEdit(widget);
        nomeror_2->setObjectName("nomeror_2");
        nomeror_2->setGeometry(QRect(30, 30, 261, 16));
        nomeror_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:none;\n"
"color: rgb(255, 12, 12);"));
        nomeror_2->setReadOnly(true);
        adseror_2 = new QLineEdit(widget);
        adseror_2->setObjectName("adseror_2");
        adseror_2->setGeometry(QRect(30, 80, 261, 16));
        adseror_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:none;\n"
"color: rgb(255, 12, 12);"));
        adseror_2->setReadOnly(true);
        drteror_2 = new QLineEdit(widget);
        drteror_2->setObjectName("drteror_2");
        drteror_2->setGeometry(QRect(30, 140, 261, 16));
        drteror_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:none;\n"
"color: rgb(255, 12, 12);"));
        drteror_2->setReadOnly(true);
        cpteror_2 = new QLineEdit(widget);
        cpteror_2->setObjectName("cpteror_2");
        cpteror_2->setGeometry(QRect(30, 200, 261, 16));
        cpteror_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:none;\n"
"color: rgb(255, 12, 12);"));
        cpteror_2->setReadOnly(true);
        sup = new QPushButton(widget);
        sup->setObjectName("sup");
        sup->setGeometry(QRect(320, 120, 131, 41));
        sup->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white;\n"
"background-image: url(:/resources/background.png);"));
        trie = new QComboBox(widget);
        trie->addItem(QString());
        trie->addItem(QString());
        trie->addItem(QString());
        trie->setObjectName("trie");
        trie->setGeometry(QRect(480, 210, 121, 31));
        trie->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        tri = new QPushButton(widget);
        tri->setObjectName("tri");
        tri->setGeometry(QRect(480, 260, 131, 41));
        tri->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white;\n"
"background-image: url(:/resources/background.png);"));
        temp = new QLineEdit(widget);
        temp->setObjectName("temp");
        temp->setGeometry(QRect(320, 270, 141, 26));
        temp->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);\n"
"\n"
""));
        label_39 = new QLabel(widget);
        label_39->setObjectName("label_39");
        label_39->setGeometry(QRect(290, 230, 241, 21));
        label_39->setFont(font);
        label_39->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        frame = new QFrame(groupBox);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, -10, 281, 1231));
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
""));
        pushButton_2 = new QPushButton(frame);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(30, 350, 201, 41));
        pushButton_2->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        pushButton_3 = new QPushButton(frame);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(30, 410, 201, 41));
        pushButton_3->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        pushButton_4 = new QPushButton(frame);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(30, 470, 201, 41));
        pushButton_4->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        pushButton_5 = new QPushButton(frame);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(30, 530, 201, 41));
        pushButton_5->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        pushButton_6 = new QPushButton(frame);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(30, 650, 201, 41));
        pushButton_6->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        pushButton_7 = new QPushButton(frame);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(30, 590, 201, 41));
        pushButton_7->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        pushButton_8 = new QPushButton(frame);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(30, 290, 201, 41));
        pushButton_8->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        pushButton_9 = new QPushButton(frame);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setGeometry(QRect(30, 230, 201, 41));
        pushButton_9->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 90, 171, 111));
        label->setStyleSheet(QString::fromUtf8("\n"
"image: url(:/resources/image_2025-01-29_201537391-removebg-preview.png);"));
        next = new QPushButton(groupBox);
        next->setObjectName("next");
        next->setGeometry(QRect(1190, 660, 61, 41));
        next->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white;\n"
"background-image: url(:/resources/background.png);"));
        chat = new QPushButton(groupBox);
        chat->setObjectName("chat");
        chat->setGeometry(QRect(480, 670, 131, 41));
        chat->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white;\n"
"background-image: url(:/resources/background.png);"));
        ard = new QPushButton(groupBox);
        ard->setObjectName("ard");
        ard->setGeometry(QRect(630, 670, 141, 41));
        ard->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white;\n"
"background-image: url(:/resources/background.png);"));

        verticalLayout->addWidget(groupBox);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        horizontalLayout = new QHBoxLayout(page_2);
        horizontalLayout->setObjectName("horizontalLayout");
        groupBox_2 = new QGroupBox(page_2);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setStyleSheet(QString::fromUtf8("QGroupBox{\n"
"	background-image: url(:/resources/background.png);}"));
        verticalLayoutWidget = new QWidget(groupBox_2);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(49, 159, 1041, 471));
        verticalLayout_6 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        back = new QPushButton(groupBox_2);
        back->setObjectName("back");
        back->setGeometry(QRect(1170, 650, 61, 41));
        back->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white;\n"
"background-image: url(:/resources/background.png);"));

        horizontalLayout->addWidget(groupBox_2);

        stackedWidget->addWidget(page_2);

        verticalLayout_5->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QString());
        label_23->setText(QCoreApplication::translate("MainWindow", "\360\237\224\215 Rechercher :", nullptr));
        stat->setText(QCoreApplication::translate("MainWindow", "\360\237\223\212 Statistiques", nullptr));
        idedit->setPlaceholderText(QCoreApplication::translate("MainWindow", "taper id", nullptr));
        recuperer->setText(QCoreApplication::translate("MainWindow", "\360\237\224\201 R\303\251cup\303\251rer", nullptr));
        cherchebut->setText(QCoreApplication::translate("MainWindow", "\360\237\224\215 Chercher", nullptr));
        cherche->setText(QString());
        cherche->setPlaceholderText(QString());
        pdf->setText(QCoreApplication::translate("MainWindow", "\360\237\223\204 Exporter PDF", nullptr));
        ajoute_2->setText(QCoreApplication::translate("MainWindow", "\342\236\225 Ajouter ", nullptr));
        label_33->setText(QCoreApplication::translate("MainWindow", "\342\234\205 Statut :", nullptr));
        label_34->setText(QCoreApplication::translate("MainWindow", "\360\237\223\212 Capacit\303\251 :", nullptr));
        label_35->setText(QCoreApplication::translate("MainWindow", "\360\237\223\215 Adresse :", nullptr));
        label_36->setText(QCoreApplication::translate("MainWindow", "\360\237\217\267\357\270\217 Nom :", nullptr));
        label_37->setText(QCoreApplication::translate("MainWindow", "\360\237\233\240\357\270\217 Facilit\303\251 :", nullptr));
        label_38->setText(QCoreApplication::translate("MainWindow", "\360\237\221\250\342\200\215\360\237\222\274 Directeur :", nullptr));
        status_2->setItemText(0, QCoreApplication::translate("MainWindow", "0", nullptr));
        status_2->setItemText(1, QCoreApplication::translate("MainWindow", "1", nullptr));

        modifier_2->setText(QCoreApplication::translate("MainWindow", "\342\234\217\357\270\217 Modifier", nullptr));
        sup->setText(QCoreApplication::translate("MainWindow", "\342\235\214 Supprimer", nullptr));
        trie->setItemText(0, QCoreApplication::translate("MainWindow", "id", nullptr));
        trie->setItemText(1, QCoreApplication::translate("MainWindow", "status", nullptr));
        trie->setItemText(2, QCoreApplication::translate("MainWindow", "capacite", nullptr));

        tri->setText(QCoreApplication::translate("MainWindow", "\360\237\224\203 Trier", nullptr));
        label_39->setText(QCoreApplication::translate("MainWindow", "\360\237\224\245Temp\303\251rature Max :", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\360\237\217\253 Centre", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "\360\237\223\235Examen", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "\360\237\216\223 Etudiant", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "\360\237\247\260 Mat\303\251riel", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", " \360\237\224\223 Deconnexion", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "\360\237\223\232 Formation", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "\360\237\221\250\342\200\215\360\237\222\274 Employ\303\251", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "\360\237\217\240 Home", nullptr));
        label->setText(QString());
        next->setText(QCoreApplication::translate("MainWindow", ">", nullptr));
        chat->setText(QCoreApplication::translate("MainWindow", "\360\237\222\254 Discussion", nullptr));
        ard->setText(QCoreApplication::translate("MainWindow", "	\360\237\224\245Temp\303\251rature", nullptr));
        groupBox_2->setTitle(QString());
        back->setText(QCoreApplication::translate("MainWindow", "<", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
