/********************************************************************************
** Form generated from reading UI file 'optimization.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIMIZATION_H
#define UI_OPTIMIZATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_optimization
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *typeLabel;
    QListWidget *changesListWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *optimization)
    {
        if (optimization->objectName().isEmpty())
            optimization->setObjectName("optimization");
        optimization->resize(490, 409);
        optimization->setStyleSheet(QString::fromUtf8("background-color: #0a246a"));
        verticalLayout = new QVBoxLayout(optimization);
        verticalLayout->setObjectName("verticalLayout");
        typeLabel = new QLabel(optimization);
        typeLabel->setObjectName("typeLabel");
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        typeLabel->setFont(font);
        typeLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(typeLabel);

        changesListWidget = new QListWidget(optimization);
        changesListWidget->setObjectName("changesListWidget");
        changesListWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        changesListWidget->setAlternatingRowColors(true);

        verticalLayout->addWidget(changesListWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(optimization);

        QMetaObject::connectSlotsByName(optimization);
    } // setupUi

    void retranslateUi(QDialog *optimization)
    {
        optimization->setWindowTitle(QCoreApplication::translate("optimization", "Equipment Optimization", nullptr));
        typeLabel->setText(QCoreApplication::translate("optimization", "Equipment Type", nullptr));
    } // retranslateUi

};

namespace Ui {
    class optimization: public Ui_optimization {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIMIZATION_H
