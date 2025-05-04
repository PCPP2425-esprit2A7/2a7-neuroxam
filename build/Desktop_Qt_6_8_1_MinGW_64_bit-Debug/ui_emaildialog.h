/********************************************************************************
** Form generated from reading UI file 'emaildialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMAILDIALOG_H
#define UI_EMAILDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EmailDialog
{
public:
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit_email;
    QTextEdit *textEdit_message;
    QPushButton *btn_envoyer;
    QLabel *label_3;
    QDateEdit *dateEdit_dateExamen;
    QPushButton *btn_annuler;

    void setupUi(QDialog *EmailDialog)
    {
        if (EmailDialog->objectName().isEmpty())
            EmailDialog->setObjectName("EmailDialog");
        EmailDialog->resize(1031, 696);
        EmailDialog->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        formLayoutWidget = new QWidget(EmailDialog);
        formLayoutWidget->setObjectName("formLayoutWidget");
        formLayoutWidget->setGeometry(QRect(140, 100, 711, 511));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(formLayoutWidget);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName("label_2");
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        lineEdit_email = new QLineEdit(formLayoutWidget);
        lineEdit_email->setObjectName("lineEdit_email");
        lineEdit_email->setStyleSheet(QString::fromUtf8("background-color: rgb(230, 235, 255);\n"
"color: rgb(0, 0, 0);"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit_email);

        textEdit_message = new QTextEdit(formLayoutWidget);
        textEdit_message->setObjectName("textEdit_message");
        textEdit_message->setStyleSheet(QString::fromUtf8("background-color: rgb(230, 235, 255);\n"
"\n"
"color: rgb(0, 0, 0);"));

        formLayout->setWidget(1, QFormLayout::FieldRole, textEdit_message);

        btn_envoyer = new QPushButton(formLayoutWidget);
        btn_envoyer->setObjectName("btn_envoyer");
        btn_envoyer->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(34, 10, 213);\n"
"\n"
""));

        formLayout->setWidget(4, QFormLayout::FieldRole, btn_envoyer);

        label_3 = new QLabel(formLayoutWidget);
        label_3->setObjectName("label_3");
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_3);

        dateEdit_dateExamen = new QDateEdit(formLayoutWidget);
        dateEdit_dateExamen->setObjectName("dateEdit_dateExamen");
        dateEdit_dateExamen->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(230, 235, 255);"));

        formLayout->setWidget(3, QFormLayout::FieldRole, dateEdit_dateExamen);

        btn_annuler = new QPushButton(formLayoutWidget);
        btn_annuler->setObjectName("btn_annuler");
        btn_annuler->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(34, 10, 213);\n"
""));

        formLayout->setWidget(5, QFormLayout::FieldRole, btn_annuler);


        retranslateUi(EmailDialog);

        QMetaObject::connectSlotsByName(EmailDialog);
    } // setupUi

    void retranslateUi(QDialog *EmailDialog)
    {
        EmailDialog->setWindowTitle(QCoreApplication::translate("EmailDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("EmailDialog", "Email", nullptr));
        label_2->setText(QCoreApplication::translate("EmailDialog", "Message", nullptr));
        btn_envoyer->setText(QCoreApplication::translate("EmailDialog", "Envoyer", nullptr));
        label_3->setText(QCoreApplication::translate("EmailDialog", "Date", nullptr));
        btn_annuler->setText(QCoreApplication::translate("EmailDialog", "Annuler", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EmailDialog: public Ui_EmailDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMAILDIALOG_H
