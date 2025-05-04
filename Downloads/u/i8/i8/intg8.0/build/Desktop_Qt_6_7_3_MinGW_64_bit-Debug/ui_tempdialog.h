/********************************************************************************
** Form generated from reading UI file 'tempdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEMPDIALOG_H
#define UI_TEMPDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QGroupBox *groupBox;
    QLineEdit *tmp;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *name;
    QLabel *label_3;
    QLineEdit *ctmp;
    QLabel *label_4;
    QLineEdit *vitesse;
    QSlider *slider;
    QLabel *label_5;
    QLineEdit *id;
    QPushButton *rp;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName("Dialog");
        Dialog->resize(856, 587);
        groupBox = new QGroupBox(Dialog);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(-90, -30, 951, 631));
        QFont font;
        font.setFamilies({QString::fromUtf8("Perpetua")});
        font.setPointSize(20);
        groupBox->setFont(font);
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox{background-image: url(:/res/resources/background.png);}"));
        tmp = new QLineEdit(groupBox);
        tmp->setObjectName("tmp");
        tmp->setGeometry(QRect(580, 240, 211, 41));
        tmp->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        tmp->setReadOnly(true);
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setGeometry(QRect(250, 240, 311, 41));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Perpetua")});
        font1.setPointSize(16);
        label->setFont(font1);
        label->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(330, 160, 251, 41));
        label_2->setFont(font1);
        label_2->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        name = new QLineEdit(groupBox);
        name->setObjectName("name");
        name->setGeometry(QRect(580, 160, 211, 41));
        name->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(280, 320, 281, 41));
        label_3->setFont(font1);
        label_3->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        ctmp = new QLineEdit(groupBox);
        ctmp->setObjectName("ctmp");
        ctmp->setGeometry(QRect(580, 320, 211, 41));
        ctmp->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        ctmp->setReadOnly(false);
        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(310, 400, 271, 41));
        label_4->setFont(font1);
        label_4->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;\n"
""));
        vitesse = new QLineEdit(groupBox);
        vitesse->setObjectName("vitesse");
        vitesse->setGeometry(QRect(580, 400, 211, 41));
        vitesse->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        vitesse->setReadOnly(true);
        slider = new QSlider(groupBox);
        slider->setObjectName("slider");
        slider->setGeometry(QRect(360, 470, 531, 41));
        slider->setOrientation(Qt::Orientation::Horizontal);
        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(350, 80, 301, 41));
        label_5->setFont(font1);
        label_5->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        id = new QLineEdit(groupBox);
        id->setObjectName("id");
        id->setGeometry(QRect(580, 90, 211, 41));
        id->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        id->setReadOnly(false);
        rp = new QPushButton(groupBox);
        rp->setObjectName("rp");
        rp->setGeometry(QRect(802, 90, 121, 41));
        rp->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white;\n"
"background-image: url(:/res/resources/background.png);"));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Dialog", "GroupBox", nullptr));
        label->setText(QCoreApplication::translate("Dialog", "\360\237\214\241\357\270\217 Temp\303\251rature en temps r\303\251el :", nullptr));
        label_2->setText(QCoreApplication::translate("Dialog", "\360\237\217\242 Nom du Centre :", nullptr));
        label_3->setText(QCoreApplication::translate("Dialog", "\360\237\224\245 Temp\303\251rature Maximale :", nullptr));
        label_4->setText(QCoreApplication::translate("Dialog", "\360\237\222\250 Vitesse du Ventilateur :", nullptr));
        label_5->setText(QCoreApplication::translate("Dialog", "\360\237\206\224 ID du Centre :", nullptr));
        rp->setText(QCoreApplication::translate("Dialog", "R\303\251cup\303\251rer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEMPDIALOG_H
