#include "dialogrecherche.h"
#include "ui_dialogrecherche.h"
#include "formation.h"
#include <QListWidgetItem>
#include <QSqlQueryModel>
#include <QKeyEvent>
#include <QMessageBox>
#include <QRegularExpression>
#include <QDebug>

DialogRecherche::DialogRecherche(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogRecherche)
{
    ui->setupUi(this);
    ui->listWidgetSuggestions->clear();

    // Boutons
    connect(ui->btnFermer, &QPushButton::clicked, this, &DialogRecherche::reject);
    connect(ui->btnReset, &QPushButton::clicked, this, [=]() {
        ui->lineEditSujet->clear();
        ui->listWidgetSuggestions->clear();
        ui->lineEditSujet->setFocus();
    });

    // Lancer recherche dynamique dès saisie
    connect(ui->lineEditSujet, &QLineEdit::textChanged, this, &DialogRecherche::actualiserSuggestions);
}

DialogRecherche::~DialogRecherche()
{
    delete ui;
}

QString DialogRecherche::getSujetSelectionne() const
{
    return sujetSelectionne;
}

void DialogRecherche::actualiserSuggestions()
{
    ui->listWidgetSuggestions->clear();
    QString texte = ui->lineEditSujet->text().trimmed();

    if (texte.length() < 1) return;

    Formation f;
    QSqlQueryModel *model = f.rechercherMulticritere(texte);

    for (int i = 0; i < model->rowCount(); ++i) {
        QString id = model->data(model->index(i, 0)).toString();
        QString sujet = model->data(model->index(i, 1)).toString();
        QString statut = model->data(model->index(i, 5)).toString();

        QListWidgetItem *item = new QListWidgetItem(QString("📘 %1 - %2 [%3]").arg(id, sujet, statut));
        ui->listWidgetSuggestions->addItem(item);
    }
}

void DialogRecherche::on_listWidgetSuggestions_itemClicked(QListWidgetItem *item)
{
    if (!item) return;

    QString text = item->text();
    QRegularExpression regex("📘 \\d+ - (.+) \\[.*\\]");
    QRegularExpressionMatch match = regex.match(text);

    if (match.hasMatch()) {
        sujetSelectionne = match.captured(1);
        accept();
    }
}

void DialogRecherche::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        reject();
    } else if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        QListWidgetItem *current = ui->listWidgetSuggestions->currentItem();
        if (current) {
            on_listWidgetSuggestions_itemClicked(current);
        } else if (ui->listWidgetSuggestions->count() == 0) {
            QMessageBox::information(this, "Aucun résultat", "❌ Aucun élément trouvé.");
        }
    } else if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_R) {
        ui->btnReset->click();
    } else {
        QDialog::keyPressEvent(event);
    }
}
