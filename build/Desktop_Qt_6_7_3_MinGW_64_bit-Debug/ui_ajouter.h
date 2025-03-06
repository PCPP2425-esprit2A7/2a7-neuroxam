/********************************************************************************
** Form generated from reading UI file 'ajouter.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AJOUTER_H
#define UI_AJOUTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_ajouter
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_5;

    void setupUi(QDialog *ajouter)
    {
        if (ajouter->objectName().isEmpty())
            ajouter->setObjectName("ajouter");
        ajouter->resize(1024, 581);
        buttonBox = new QDialogButtonBox(ajouter);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(650, 530, 341, 32));
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);
        label = new QLabel(ajouter);
        label->setObjectName("label");
        label->setGeometry(QRect(80, 80, 121, 20));
        label_2 = new QLabel(ajouter);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(80, 160, 63, 20));
        label_3 = new QLabel(ajouter);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(80, 250, 63, 20));
        label_4 = new QLabel(ajouter);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(80, 330, 63, 20));
        label_5 = new QLabel(ajouter);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(80, 410, 63, 20));
        lineEdit = new QLineEdit(ajouter);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(220, 80, 201, 26));
        lineEdit_2 = new QLineEdit(ajouter);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(220, 160, 201, 26));
        lineEdit_3 = new QLineEdit(ajouter);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(220, 250, 201, 26));
        lineEdit_4 = new QLineEdit(ajouter);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setGeometry(QRect(220, 330, 201, 26));
        lineEdit_5 = new QLineEdit(ajouter);
        lineEdit_5->setObjectName("lineEdit_5");
        lineEdit_5->setGeometry(QRect(220, 410, 201, 26));

        retranslateUi(ajouter);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, ajouter, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, ajouter, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(ajouter);
    } // setupUi

    void retranslateUi(QDialog *ajouter)
    {
        ajouter->setWindowTitle(QCoreApplication::translate("ajouter", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("ajouter", "nom de centre", nullptr));
        label_2->setText(QCoreApplication::translate("ajouter", "adresse", nullptr));
        label_3->setText(QCoreApplication::translate("ajouter", "directeur ", nullptr));
        label_4->setText(QCoreApplication::translate("ajouter", "capacite", nullptr));
        label_5->setText(QCoreApplication::translate("ajouter", "status", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ajouter: public Ui_ajouter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AJOUTER_H
