/********************************************************************************
** Form generated from reading UI file 'dialogid.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGID_H
#define UI_DIALOGID_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogID
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QSpinBox *spinBoxID;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogID)
    {
        if (DialogID->objectName().isEmpty())
            DialogID->setObjectName("DialogID");
        DialogID->resize(360, 160);
        DialogID->setStyleSheet(QString::fromUtf8("\n"
"    QDialog {\n"
"      background-color: #f5f8fa;\n"
"    }\n"
"    QLabel {\n"
"      font-size: 14pt;\n"
"      font-weight: bold;\n"
"      color: #032e5b;\n"
"    }\n"
"    QSpinBox {\n"
"      font-size: 14pt;\n"
"      padding: 6px;\n"
"      border: 2px solid #42a5f5;\n"
"      border-radius: 6px;\n"
"      background-color: #e3f2fd;\n"
"    }\n"
"    QDialogButtonBox QPushButton {\n"
"      font-size: 13pt;\n"
"      padding: 6px 18px;\n"
"      border-radius: 8px;\n"
"      background-color: #0C3C78;\n"
"      color: white;\n"
"    }\n"
"    QDialogButtonBox QPushButton:hover {\n"
"      background-color: #145DA0;\n"
"    }\n"
"   "));
        verticalLayout = new QVBoxLayout(DialogID);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(DialogID);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        spinBoxID = new QSpinBox(DialogID);
        spinBoxID->setObjectName("spinBoxID");
        spinBoxID->setMinimum(1);
        spinBoxID->setMaximum(999999);
        spinBoxID->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(spinBoxID);

        buttonBox = new QDialogButtonBox(DialogID);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setStandardButtons(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);
        buttonBox->setCenterButtons(true);

        verticalLayout->addWidget(buttonBox);

        verticalLayout->setStretch(1, 1);

        retranslateUi(DialogID);

        QMetaObject::connectSlotsByName(DialogID);
    } // setupUi

    void retranslateUi(QDialog *DialogID)
    {
        DialogID->setWindowTitle(QCoreApplication::translate("DialogID", "\360\237\224\216 Rechercher une Formation", nullptr));
        label->setText(QCoreApplication::translate("DialogID", "Entrez l'ID de la formation  :", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogID: public Ui_DialogID {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGID_H
