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
#include <QtWidgets/QCalendarWidget>
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
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget;
    QVBoxLayout *verticalLayout_5;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QFrame *frame;
    QPushButton *pushButton_2;
    QPushButton *mexam;
    QPushButton *etud;
    QPushButton *materl;
    QPushButton *pushButton_6;
    QPushButton *formation;
    QPushButton *pushButton_9;
    QLabel *label;
    QPushButton *emp;
    QGroupBox *groupBox_3;
    QPushButton *pdf;
    QLineEdit *idedit;
    QPushButton *ard;
    QWidget *widget_2;
    QPushButton *ajoute_3;
    QLineEdit *facilities_3;
    QLineEdit *directeur_3;
    QLabel *label_40;
    QLabel *label_41;
    QLabel *label_42;
    QLabel *label_43;
    QLineEdit *capacite_3;
    QLabel *label_44;
    QLineEdit *adresse_3;
    QLabel *label_45;
    QLineEdit *nom_3;
    QComboBox *status_3;
    QPushButton *modifier_3;
    QLineEdit *nomeror_3;
    QLineEdit *adseror_3;
    QLineEdit *drteror_3;
    QLineEdit *cpteror_3;
    QPushButton *sup_3;
    QComboBox *trie_3;
    QPushButton *tri_3;
    QLineEdit *temp_2;
    QLabel *label_46;
    QLineEdit *cherche;
    QLabel *label_23;
    QPushButton *stat;
    QTableView *aff;
    QPushButton *chat;
    QPushButton *next;
    QPushButton *cherchebut;
    QPushButton *recuperer;
    QGroupBox *groupBox_4;
    QPushButton *cherchebut_3;
    QLabel *label_25;
    QPushButton *pdf_3;
    QLineEdit *cherche_3;
    QLineEdit *idedit_3;
    QPushButton *stat_3;
    QWidget *widget_4;
    QPushButton *ajoute_4;
    QLineEdit *centre_examen_2;
    QLineEdit *matiere_2;
    QLabel *label_47;
    QLabel *label_48;
    QLabel *label_49;
    QLineEdit *type_examen_2;
    QLabel *label_50;
    QLabel *label_51;
    QPushButton *modifier_4;
    QLineEdit *heure_examen_2;
    QDateEdit *date_examen_2;
    QLabel *label_52;
    QLineEdit *email_2;
    QPushButton *btn_ouvrirEmailDialog__2;
    QPushButton *sup_4;
    QPushButton *tri_4;
    QTableView *aff_3;
    QPushButton *recuperer_3;
    QComboBox *trie_4;
    QCalendarWidget *calendar_examen_2;
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
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        verticalLayout_5 = new QVBoxLayout(widget);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        stackedWidget = new QStackedWidget(widget);
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
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox{background-image: url(:/res/resources/background.png);}\n"
""));
        frame = new QFrame(groupBox);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, -10, 251, 1231));
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
""));
        pushButton_2 = new QPushButton(frame);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(30, 350, 201, 41));
        pushButton_2->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/res/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        mexam = new QPushButton(frame);
        mexam->setObjectName("mexam");
        mexam->setGeometry(QRect(30, 410, 201, 41));
        mexam->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/res/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        etud = new QPushButton(frame);
        etud->setObjectName("etud");
        etud->setGeometry(QRect(30, 470, 201, 41));
        etud->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/res/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        materl = new QPushButton(frame);
        materl->setObjectName("materl");
        materl->setGeometry(QRect(30, 530, 201, 41));
        materl->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/res/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        pushButton_6 = new QPushButton(frame);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(30, 650, 201, 41));
        pushButton_6->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/res/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        formation = new QPushButton(frame);
        formation->setObjectName("formation");
        formation->setGeometry(QRect(30, 590, 201, 41));
        formation->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/res/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        pushButton_9 = new QPushButton(frame);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setGeometry(QRect(30, 230, 201, 41));
        pushButton_9->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/res/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 90, 171, 111));
        label->setStyleSheet(QString::fromUtf8("\n"
"image: url(:/res/resources/image_2025-01-29_201537391-removebg-preview.png);"));
        emp = new QPushButton(frame);
        emp->setObjectName("emp");
        emp->setGeometry(QRect(30, 290, 201, 41));
        emp->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"background-image: url(:/res/resources/background.png);\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setEnabled(true);
        groupBox_3->setGeometry(QRect(-20, 0, 1721, 931));
        pdf = new QPushButton(groupBox_3);
        pdf->setObjectName("pdf");
        pdf->setGeometry(QRect(860, 355, 131, 41));
        pdf->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white;\n"
"background-image: url(:/res/resources/background.png);"));
        idedit = new QLineEdit(groupBox_3);
        idedit->setObjectName("idedit");
        idedit->setGeometry(QRect(1080, 225, 171, 31));
        idedit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        ard = new QPushButton(groupBox_3);
        ard->setObjectName("ard");
        ard->setGeometry(QRect(660, 675, 141, 41));
        ard->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white;\n"
"background-image: url(:/res/resources/background.png);"));
        widget_2 = new QWidget(groupBox_3);
        widget_2->setObjectName("widget_2");
        widget_2->setGeometry(QRect(340, 20, 631, 321));
        ajoute_3 = new QPushButton(widget_2);
        ajoute_3->setObjectName("ajoute_3");
        ajoute_3->setGeometry(QRect(320, 0, 131, 41));
        ajoute_3->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white;\n"
"background-image: url(:/res/resources/background.png);"));
        facilities_3 = new QLineEdit(widget_2);
        facilities_3->setObjectName("facilities_3");
        facilities_3->setGeometry(QRect(150, 220, 141, 21));
        facilities_3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);\n"
""));
        directeur_3 = new QLineEdit(widget_2);
        directeur_3->setObjectName("directeur_3");
        directeur_3->setGeometry(QRect(150, 110, 141, 26));
        directeur_3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);\n"
"\n"
""));
        label_40 = new QLabel(widget_2);
        label_40->setObjectName("label_40");
        label_40->setGeometry(QRect(20, 270, 111, 31));
        QFont font;
        font.setFamilies({QString::fromUtf8("Perpetua")});
        font.setPointSize(12);
        font.setBold(true);
        font.setItalic(true);
        font.setUnderline(false);
        label_40->setFont(font);
        label_40->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        label_41 = new QLabel(widget_2);
        label_41->setObjectName("label_41");
        label_41->setGeometry(QRect(20, 170, 151, 31));
        label_41->setFont(font);
        label_41->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        label_42 = new QLabel(widget_2);
        label_42->setObjectName("label_42");
        label_42->setGeometry(QRect(20, 50, 121, 31));
        label_42->setFont(font);
        label_42->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        label_43 = new QLabel(widget_2);
        label_43->setObjectName("label_43");
        label_43->setGeometry(QRect(40, 0, 71, 31));
        label_43->setFont(font);
        label_43->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        capacite_3 = new QLineEdit(widget_2);
        capacite_3->setObjectName("capacite_3");
        capacite_3->setGeometry(QRect(150, 170, 141, 26));
        capacite_3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);\n"
""));
        label_44 = new QLabel(widget_2);
        label_44->setObjectName("label_44");
        label_44->setGeometry(QRect(20, 230, 121, 21));
        label_44->setFont(font);
        label_44->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        adresse_3 = new QLineEdit(widget_2);
        adresse_3->setObjectName("adresse_3");
        adresse_3->setGeometry(QRect(150, 50, 141, 26));
        adresse_3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);\n"
"\n"
""));
        label_45 = new QLabel(widget_2);
        label_45->setObjectName("label_45");
        label_45->setGeometry(QRect(20, 110, 111, 31));
        label_45->setFont(font);
        label_45->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        nom_3 = new QLineEdit(widget_2);
        nom_3->setObjectName("nom_3");
        nom_3->setGeometry(QRect(150, 0, 141, 26));
        nom_3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);\n"
"\n"
""));
        status_3 = new QComboBox(widget_2);
        status_3->addItem(QString());
        status_3->addItem(QString());
        status_3->setObjectName("status_3");
        status_3->setGeometry(QRect(150, 270, 141, 26));
        status_3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        modifier_3 = new QPushButton(widget_2);
        modifier_3->setObjectName("modifier_3");
        modifier_3->setGeometry(QRect(320, 60, 131, 41));
        modifier_3->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white;\n"
"background-image: url(:/res/resources/background.png);"));
        nomeror_3 = new QLineEdit(widget_2);
        nomeror_3->setObjectName("nomeror_3");
        nomeror_3->setGeometry(QRect(30, 30, 261, 16));
        nomeror_3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:none;\n"
"color: rgb(255, 12, 12);"));
        nomeror_3->setReadOnly(true);
        adseror_3 = new QLineEdit(widget_2);
        adseror_3->setObjectName("adseror_3");
        adseror_3->setGeometry(QRect(30, 80, 261, 16));
        adseror_3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:none;\n"
"color: rgb(255, 12, 12);"));
        adseror_3->setReadOnly(true);
        drteror_3 = new QLineEdit(widget_2);
        drteror_3->setObjectName("drteror_3");
        drteror_3->setGeometry(QRect(30, 140, 261, 16));
        drteror_3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:none;\n"
"color: rgb(255, 12, 12);"));
        drteror_3->setReadOnly(true);
        cpteror_3 = new QLineEdit(widget_2);
        cpteror_3->setObjectName("cpteror_3");
        cpteror_3->setGeometry(QRect(30, 200, 261, 16));
        cpteror_3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:none;\n"
"color: rgb(255, 12, 12);"));
        cpteror_3->setReadOnly(true);
        sup_3 = new QPushButton(widget_2);
        sup_3->setObjectName("sup_3");
        sup_3->setGeometry(QRect(320, 120, 131, 41));
        sup_3->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white;\n"
"background-image: url(:/res/resources/background.png);"));
        trie_3 = new QComboBox(widget_2);
        trie_3->addItem(QString());
        trie_3->addItem(QString());
        trie_3->addItem(QString());
        trie_3->setObjectName("trie_3");
        trie_3->setGeometry(QRect(480, 210, 121, 31));
        trie_3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        tri_3 = new QPushButton(widget_2);
        tri_3->setObjectName("tri_3");
        tri_3->setGeometry(QRect(480, 260, 131, 41));
        tri_3->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white;\n"
"background-image: url(:/res/resources/background.png);"));
        temp_2 = new QLineEdit(widget_2);
        temp_2->setObjectName("temp_2");
        temp_2->setGeometry(QRect(320, 270, 141, 26));
        temp_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);\n"
"\n"
""));
        label_46 = new QLabel(widget_2);
        label_46->setObjectName("label_46");
        label_46->setGeometry(QRect(290, 230, 241, 21));
        label_46->setFont(font);
        label_46->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        cherche = new QLineEdit(groupBox_3);
        cherche->setObjectName("cherche");
        cherche->setGeometry(QRect(460, 350, 201, 41));
        cherche->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        label_23 = new QLabel(groupBox_3);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(320, 345, 151, 41));
        label_23->setFont(font);
        label_23->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        stat = new QPushButton(groupBox_3);
        stat->setObjectName("stat");
        stat->setGeometry(QRect(1040, 350, 131, 41));
        stat->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white;\n"
"background-image: url(:/res/resources/background.png);"));
        aff = new QTableView(groupBox_3);
        aff->setObjectName("aff");
        aff->setGeometry(QRect(330, 401, 841, 251));
        aff->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        chat = new QPushButton(groupBox_3);
        chat->setObjectName("chat");
        chat->setGeometry(QRect(510, 675, 131, 41));
        chat->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white;\n"
"background-image: url(:/res/resources/background.png);"));
        next = new QPushButton(groupBox_3);
        next->setObjectName("next");
        next->setGeometry(QRect(1220, 665, 61, 41));
        next->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white;\n"
"background-image: url(:/res/resources/background.png);"));
        cherchebut = new QPushButton(groupBox_3);
        cherchebut->setObjectName("cherchebut");
        cherchebut->setGeometry(QRect(670, 355, 131, 41));
        cherchebut->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white;\n"
"background-image: url(:/res/resources/background.png);"));
        recuperer = new QPushButton(groupBox_3);
        recuperer->setObjectName("recuperer");
        recuperer->setGeometry(QRect(1080, 285, 171, 41));
        recuperer->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white;\n"
"background-image: url(:/res/resources/background.png);"));
        groupBox_4 = new QGroupBox(groupBox);
        groupBox_4->setObjectName("groupBox_4");
        groupBox_4->setGeometry(QRect(-15, -5, 1321, 891));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setUnderline(false);
        groupBox_4->setFont(font1);
        groupBox_4->setStyleSheet(QString::fromUtf8("QGroupBox{\n"
"	background-image: url(:/res/resources/background.png);\n"
"}\n"
""));
        cherchebut_3 = new QPushButton(groupBox_4);
        cherchebut_3->setObjectName("cherchebut_3");
        cherchebut_3->setGeometry(QRect(685, 390, 141, 41));
        cherchebut_3->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white;\n"
"background-image: url(:/res/resources/background.png);"));
        label_25 = new QLabel(groupBox_4);
        label_25->setObjectName("label_25");
        label_25->setGeometry(QRect(335, 390, 151, 41));
        label_25->setFont(font);
        label_25->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        pdf_3 = new QPushButton(groupBox_4);
        pdf_3->setObjectName("pdf_3");
        pdf_3->setGeometry(QRect(845, 390, 141, 41));
        pdf_3->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white;\n"
"background-image: url(:/res/resources/background.png);"));
        cherche_3 = new QLineEdit(groupBox_4);
        cherche_3->setObjectName("cherche_3");
        cherche_3->setGeometry(QRect(475, 390, 201, 41));
        cherche_3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(6, 6, 4);"));
        idedit_3 = new QLineEdit(groupBox_4);
        idedit_3->setObjectName("idedit_3");
        idedit_3->setGeometry(QRect(1065, 260, 171, 31));
        idedit_3->setStyleSheet(QString::fromUtf8("color: rgb(6, 6, 6);\n"
"background-color: rgb(255, 255, 255);"));
        stat_3 = new QPushButton(groupBox_4);
        stat_3->setObjectName("stat_3");
        stat_3->setGeometry(QRect(1005, 390, 131, 41));
        stat_3->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white;\n"
"background-image: url(:/res/resources/background.png);"));
        widget_4 = new QWidget(groupBox_4);
        widget_4->setObjectName("widget_4");
        widget_4->setGeometry(QRect(315, 40, 661, 331));
        ajoute_4 = new QPushButton(widget_4);
        ajoute_4->setObjectName("ajoute_4");
        ajoute_4->setGeometry(QRect(380, 20, 111, 41));
        ajoute_4->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white;\n"
"background-image: url(:/res/resources/background.png);"));
        centre_examen_2 = new QLineEdit(widget_4);
        centre_examen_2->setObjectName("centre_examen_2");
        centre_examen_2->setGeometry(QRect(190, 250, 161, 31));
        centre_examen_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(6, 6, 6);\n"
""));
        matiere_2 = new QLineEdit(widget_4);
        matiere_2->setObjectName("matiere_2");
        matiere_2->setGeometry(QRect(190, 140, 161, 26));
        matiere_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);\n"
"\n"
""));
        label_47 = new QLabel(widget_4);
        label_47->setObjectName("label_47");
        label_47->setGeometry(QRect(30, 190, 161, 31));
        label_47->setFont(font);
        label_47->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        label_48 = new QLabel(widget_4);
        label_48->setObjectName("label_48");
        label_48->setGeometry(QRect(0, 70, 191, 31));
        label_48->setFont(font);
        label_48->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        label_49 = new QLabel(widget_4);
        label_49->setObjectName("label_49");
        label_49->setGeometry(QRect(-60, 10, 251, 31));
        label_49->setFont(font);
        label_49->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        type_examen_2 = new QLineEdit(widget_4);
        type_examen_2->setObjectName("type_examen_2");
        type_examen_2->setGeometry(QRect(190, 200, 161, 26));
        type_examen_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(11, 11, 11);\n"
""));
        label_50 = new QLabel(widget_4);
        label_50->setObjectName("label_50");
        label_50->setGeometry(QRect(10, 250, 171, 31));
        label_50->setFont(font);
        label_50->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        label_51 = new QLabel(widget_4);
        label_51->setObjectName("label_51");
        label_51->setGeometry(QRect(50, 130, 101, 31));
        label_51->setFont(font);
        label_51->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        modifier_4 = new QPushButton(widget_4);
        modifier_4->setObjectName("modifier_4");
        modifier_4->setGeometry(QRect(380, 80, 111, 41));
        modifier_4->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white;\n"
"background-image: url(:/res/resources/background.png);"));
        heure_examen_2 = new QLineEdit(widget_4);
        heure_examen_2->setObjectName("heure_examen_2");
        heure_examen_2->setGeometry(QRect(190, 80, 161, 26));
        heure_examen_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);\n"
"\n"
""));
        date_examen_2 = new QDateEdit(widget_4);
        date_examen_2->setObjectName("date_examen_2");
        date_examen_2->setGeometry(QRect(190, 20, 161, 26));
        date_examen_2->setStyleSheet(QString::fromUtf8("color: rgb(7, 7, 7);\n"
"background-color: rgb(255, 255, 255);"));
        label_52 = new QLabel(widget_4);
        label_52->setObjectName("label_52");
        label_52->setGeometry(QRect(-40, 300, 261, 31));
        label_52->setFont(font);
        label_52->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        email_2 = new QLineEdit(widget_4);
        email_2->setObjectName("email_2");
        email_2->setGeometry(QRect(190, 300, 161, 26));
        email_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);\n"
"\n"
""));
        btn_ouvrirEmailDialog__2 = new QPushButton(widget_4);
        btn_ouvrirEmailDialog__2->setObjectName("btn_ouvrirEmailDialog__2");
        btn_ouvrirEmailDialog__2->setGeometry(QRect(370, 300, 71, 31));
        btn_ouvrirEmailDialog__2->setStyleSheet(QString::fromUtf8("image: url(:/res/resources/email.png);\n"
"background-color: rgb(255, 255, 255);"));
        sup_4 = new QPushButton(widget_4);
        sup_4->setObjectName("sup_4");
        sup_4->setGeometry(QRect(380, 140, 111, 41));
        sup_4->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white;\n"
"background-image: url(:/res/resources/background.png);"));
        tri_4 = new QPushButton(widget_4);
        tri_4->setObjectName("tri_4");
        tri_4->setGeometry(QRect(490, 270, 101, 41));
        tri_4->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white;\n"
"background-image: url(:/res/resources/background.png);"));
        aff_3 = new QTableView(groupBox_4);
        aff_3->setObjectName("aff_3");
        aff_3->setGeometry(QRect(385, 450, 841, 251));
        aff_3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        recuperer_3 = new QPushButton(groupBox_4);
        recuperer_3->setObjectName("recuperer_3");
        recuperer_3->setGeometry(QRect(1095, 310, 121, 41));
        recuperer_3->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white;\n"
"background-image: url(:/res/resources/background.png);"));
        trie_4 = new QComboBox(groupBox_4);
        trie_4->addItem(QString());
        trie_4->addItem(QString());
        trie_4->setObjectName("trie_4");
        trie_4->setGeometry(QRect(805, 260, 121, 31));
        trie_4->setStyleSheet(QString::fromUtf8("color: rgb(9, 9, 9);\n"
"background-color: rgb(255, 255, 255);"));
        calendar_examen_2 = new QCalendarWidget(groupBox_4);
        calendar_examen_2->setObjectName("calendar_examen_2");
        calendar_examen_2->setGeometry(QRect(890, 30, 401, 211));
        calendar_examen_2->setStyleSheet(QString::fromUtf8(""));
        groupBox_4->raise();
        groupBox_3->raise();
        frame->raise();

        verticalLayout->addWidget(groupBox);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        horizontalLayout = new QHBoxLayout(page_2);
        horizontalLayout->setObjectName("horizontalLayout");
        groupBox_2 = new QGroupBox(page_2);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setStyleSheet(QString::fromUtf8("QGroupBox{\n"
"	background-image: url(:/res/resources/background.png);}"));
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
"background-image: url(:/res/resources/background.png);"));

        horizontalLayout->addWidget(groupBox_2);

        stackedWidget->addWidget(page_2);

        verticalLayout_5->addWidget(stackedWidget);


        horizontalLayout_2->addWidget(widget);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QString());
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\360\237\217\253 Centre", nullptr));
        mexam->setText(QCoreApplication::translate("MainWindow", "\360\237\223\235Examen", nullptr));
        etud->setText(QCoreApplication::translate("MainWindow", "\360\237\216\223 Etudiant", nullptr));
        materl->setText(QCoreApplication::translate("MainWindow", "\360\237\247\260 Mat\303\251riel", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", " \360\237\224\223 Deconnexion", nullptr));
        formation->setText(QCoreApplication::translate("MainWindow", "\360\237\223\232 Formation", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "\360\237\217\240 Home", nullptr));
        label->setText(QString());
        emp->setText(QCoreApplication::translate("MainWindow", "\360\237\221\250\342\200\215\360\237\222\274 Employ\303\251", nullptr));
        groupBox_3->setTitle(QString());
        pdf->setText(QCoreApplication::translate("MainWindow", "\360\237\223\204 Exporter PDF", nullptr));
        idedit->setPlaceholderText(QCoreApplication::translate("MainWindow", "taper id", nullptr));
        ard->setText(QCoreApplication::translate("MainWindow", "	\360\237\224\245Temp\303\251rature", nullptr));
        ajoute_3->setText(QCoreApplication::translate("MainWindow", "\342\236\225 Ajouter ", nullptr));
        label_40->setText(QCoreApplication::translate("MainWindow", "\342\234\205 Statut :", nullptr));
        label_41->setText(QCoreApplication::translate("MainWindow", "\360\237\223\212 Capacit\303\251 :", nullptr));
        label_42->setText(QCoreApplication::translate("MainWindow", "\360\237\223\215 Adresse :", nullptr));
        label_43->setText(QCoreApplication::translate("MainWindow", "\360\237\217\267\357\270\217 Nom :", nullptr));
        label_44->setText(QCoreApplication::translate("MainWindow", "\360\237\233\240\357\270\217 Facilit\303\251 :", nullptr));
        label_45->setText(QCoreApplication::translate("MainWindow", "\360\237\221\250\342\200\215\360\237\222\274 Directeur :", nullptr));
        status_3->setItemText(0, QCoreApplication::translate("MainWindow", "0", nullptr));
        status_3->setItemText(1, QCoreApplication::translate("MainWindow", "1", nullptr));

        modifier_3->setText(QCoreApplication::translate("MainWindow", "\342\234\217\357\270\217 Modifier", nullptr));
        sup_3->setText(QCoreApplication::translate("MainWindow", "\342\235\214 Supprimer", nullptr));
        trie_3->setItemText(0, QCoreApplication::translate("MainWindow", "id", nullptr));
        trie_3->setItemText(1, QCoreApplication::translate("MainWindow", "status", nullptr));
        trie_3->setItemText(2, QCoreApplication::translate("MainWindow", "capacite", nullptr));

        tri_3->setText(QCoreApplication::translate("MainWindow", "\360\237\224\203 Trier", nullptr));
        label_46->setText(QCoreApplication::translate("MainWindow", "\360\237\224\245Temp\303\251rature Max :", nullptr));
        cherche->setText(QString());
        cherche->setPlaceholderText(QString());
        label_23->setText(QCoreApplication::translate("MainWindow", "\360\237\224\215 Rechercher :", nullptr));
        stat->setText(QCoreApplication::translate("MainWindow", "\360\237\223\212 Statistiques", nullptr));
        chat->setText(QCoreApplication::translate("MainWindow", "\360\237\222\254 Discussion", nullptr));
        next->setText(QCoreApplication::translate("MainWindow", ">", nullptr));
        cherchebut->setText(QCoreApplication::translate("MainWindow", "\360\237\224\215 Chercher", nullptr));
        recuperer->setText(QCoreApplication::translate("MainWindow", "\360\237\224\201 R\303\251cup\303\251rer", nullptr));
        groupBox_4->setTitle(QString());
        cherchebut_3->setText(QCoreApplication::translate("MainWindow", "\360\237\224\215 Chercher", nullptr));
        label_25->setText(QCoreApplication::translate("MainWindow", "\360\237\224\215 Rechercher", nullptr));
        pdf_3->setText(QCoreApplication::translate("MainWindow", "\360\237\223\204 Exporter PDF", nullptr));
        cherche_3->setText(QString());
        cherche_3->setPlaceholderText(QString());
        idedit_3->setPlaceholderText(QCoreApplication::translate("MainWindow", "taper id", nullptr));
        stat_3->setText(QCoreApplication::translate("MainWindow", "\360\237\223\212 Statistiques", nullptr));
        ajoute_4->setText(QCoreApplication::translate("MainWindow", "\342\236\225 Ajouter ", nullptr));
        label_47->setText(QCoreApplication::translate("MainWindow", "\360\237\223\235 Type d'examen ", nullptr));
        label_48->setText(QCoreApplication::translate("MainWindow", "\342\217\260 Heure de l'examen", nullptr));
        label_49->setText(QCoreApplication::translate("MainWindow", "	\360\237\223\205 Date de l'examen", nullptr));
        label_50->setText(QCoreApplication::translate("MainWindow", "\360\237\217\253 Centre d'examen", nullptr));
        label_51->setText(QCoreApplication::translate("MainWindow", "\360\237\223\230 Mati\303\250re", nullptr));
        modifier_4->setText(QCoreApplication::translate("MainWindow", "\342\234\217\357\270\217 Modifier", nullptr));
        label_52->setText(QCoreApplication::translate("MainWindow", "	\360\237\223\247 Email du centre", nullptr));
        btn_ouvrirEmailDialog__2->setText(QString());
        sup_4->setText(QCoreApplication::translate("MainWindow", "\342\235\214 Supprimer", nullptr));
        tri_4->setText(QCoreApplication::translate("MainWindow", "\360\237\224\203 Trier", nullptr));
        recuperer_3->setText(QCoreApplication::translate("MainWindow", "\360\237\224\201 R\303\251cup\303\251rer", nullptr));
        trie_4->setItemText(0, QCoreApplication::translate("MainWindow", "id_examen", nullptr));
        trie_4->setItemText(1, QCoreApplication::translate("MainWindow", "date_examen", nullptr));

        groupBox_2->setTitle(QString());
        back->setText(QCoreApplication::translate("MainWindow", "<", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
