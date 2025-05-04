/********************************************************************************
** Form generated from reading UI file 'logdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGDIALOG_H
#define UI_LOGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QLabel *label;
    QLabel *label_4;
    QGroupBox *groupBox_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QPushButton *Login;
    QPushButton *forgotPasswordBtn;
    QPushButton *Login_2;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName("Dialog");
        Dialog->resize(877, 698);
        label = new QLabel(Dialog);
        label->setObjectName("label");
        label->setGeometry(QRect(-80, -350, 1421, 1421));
        label->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix1/resources/back.jpeg);"));
        label_4 = new QLabel(Dialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(200, 0, 591, 241));
        label_4->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix1/resources/475038336_657821386805867_9178055062394887346_n__1_-removebg-preview.png);"));
        groupBox_2 = new QGroupBox(Dialog);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(290, 220, 441, 291));
        groupBox_2->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    background-color: rgba(255, 255, 255, 0.08);  /* presque blanc translucide */\n"
"    border: 1px solid rgba(0, 180, 255, 0.4);\n"
"    border-radius: 20px;\n"
"    padding: 20px;\n"
"}\n"
"\n"
"\n"
"QGroupBox:title {\n"
"    color: white;\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center;\n"
"    padding: 0 3px;\n"
"}\n"
""));
        lineEdit = new QLineEdit(groupBox_2);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(60, 70, 301, 41));
        lineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"     border: 1px solid rgba(0, 180, 255, 0.4);\n"
"    border-radius: 20px;\n"
"color: rgb(0, 0, 0);\n"
"\n"
"    border-radius: 5px;\n"
"    padding: 10px;\n"
"    font-size: 14px;"));
        lineEdit_2 = new QLineEdit(groupBox_2);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(60, 120, 301, 41));
        lineEdit_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"     border: 1px solid rgba(0, 180, 255, 0.4);\n"
"\n"
"color: rgb(0, 0, 0);\n"
" \n"
"    border-radius: 5px;\n"
"    padding: 10px;\n"
"    font-size: 14px;"));
        Login = new QPushButton(groupBox_2);
        Login->setObjectName("Login");
        Login->setGeometry(QRect(250, 230, 181, 41));
        Login->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #003366;\n"
"    color: white;\n"
"    border-radius: 10px;\n"
"    padding: 10px;\n"
"    font-weight: bold;\n"
"    letter-spacing: 1px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #005599;\n"
"}\n"
""));
        forgotPasswordBtn = new QPushButton(groupBox_2);
        forgotPasswordBtn->setObjectName("forgotPasswordBtn");
        forgotPasswordBtn->setGeometry(QRect(200, 170, 161, 31));
        Login_2 = new QPushButton(groupBox_2);
        Login_2->setObjectName("Login_2");
        Login_2->setGeometry(QRect(40, 230, 181, 41));
        Login_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #003366;\n"
"    color: white;\n"
"    border-radius: 10px;\n"
"    padding: 10px;\n"
"    font-weight: bold;\n"
"    letter-spacing: 1px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #005599;\n"
"}\n"
""));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        label->setText(QString());
        label_4->setText(QString());
        groupBox_2->setTitle(QCoreApplication::translate("Dialog", "            GroupBox", nullptr));
        lineEdit->setInputMask(QString());
        lineEdit->setPlaceholderText(QCoreApplication::translate("Dialog", "E-mail", nullptr));
        lineEdit_2->setPlaceholderText(QCoreApplication::translate("Dialog", "Mot de passe", nullptr));
        Login->setText(QCoreApplication::translate("Dialog", "Se connecter", nullptr));
        forgotPasswordBtn->setText(QCoreApplication::translate("Dialog", "Mot de passe oubli\303\251 ?", nullptr));
        Login_2->setText(QCoreApplication::translate("Dialog", "Connexion Faciale", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGDIALOG_H
