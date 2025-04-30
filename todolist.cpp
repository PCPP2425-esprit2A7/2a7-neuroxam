#include "todolist.h"
#include "ui_todolist.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

TodoList::TodoList(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TodoList)
    , model(new QStandardItemModel(this))
{
    ui->setupUi(this);
    this->setWindowTitle("📝 Liste des Tâches");
    this->resize(700, 500);

    model->setHorizontalHeaderLabels({"Tâche", "Date limite", "Catégorie", "Priorité"});
    ui->tableViewTaches->setModel(model);

    connect(ui->btnAjouterTache, &QPushButton::clicked, this, [=]() {
        QString texte = ui->lineEditTache->text().trimmed();
        QDate date = ui->dateEditLimite->date();
        if (texte.isEmpty()) {
            QMessageBox::warning(this, "Champ vide", "Veuillez saisir une tâche.");
            return;
        }
        QString categorie = detecterCategorie(texte);
        QString priorite = evaluerPriorite(date);

        QSqlQuery insert;
        insert.prepare("INSERT INTO TACHES (TEXTE, DATE_LIMITE, TERMINE) VALUES (:texte, TO_DATE(:date_str, 'DD/MM/YYYY'), 0)");
        insert.bindValue(":texte", texte);
        insert.bindValue(":date_str", date.toString("dd/MM/yyyy"));
        insert.exec();

        ui->lineEditTache->clear();
        ui->dateEditLimite->setDate(QDate::currentDate());
        chargerTachesDepuisBase();
    });

    connect(ui->btnTerminerTache, &QPushButton::clicked, this, [=]() {
        QModelIndex index = ui->tableViewTaches->currentIndex();
        if (!index.isValid()) return;

        QString texte = model->item(index.row(), 0)->text();
        QSqlQuery update;
        update.prepare("UPDATE TACHES SET TERMINE = 1 WHERE TEXTE = :texte");
        update.bindValue(":texte", texte);
        update.exec();
        chargerTachesDepuisBase();
    });

    connect(ui->btnSupprimerTache, &QPushButton::clicked, this, [=]() {
        QModelIndex index = ui->tableViewTaches->currentIndex();
        if (!index.isValid()) return;
        QString texte = model->item(index.row(), 0)->text();
        QSqlQuery del;
        del.prepare("DELETE FROM TACHES WHERE TEXTE = :texte");
        del.bindValue(":texte", texte);
        del.exec();
        chargerTachesDepuisBase();
    });

    connect(ui->checkBoxActives, &QCheckBox::stateChanged, this, [=]() {
        chargerTachesDepuisBase();
    });

    chargerFormationsPrevues();
    chargerTachesDepuisBase();
}

TodoList::~TodoList() {
    delete ui;
}

void TodoList::chargerTachesDepuisBase()
{
    model->removeRows(0, model->rowCount());
    QString req = "SELECT TEXTE, TO_CHAR(DATE_LIMITE, 'DD/MM/YYYY'), TERMINE FROM TACHES";
    if (ui->checkBoxActives->isChecked()) req += " WHERE TERMINE = 0";
    QSqlQuery query(req);
    while (query.next()) {
        QString texte = query.value(0).toString();
        QDate date = QDate::fromString(query.value(1).toString(), "dd/MM/yyyy");
        bool termine = query.value(2).toInt() == 1;

        QList<QStandardItem*> row;
        row << new QStandardItem(texte);
        row << new QStandardItem(date.toString("dd/MM/yyyy"));
        row << new QStandardItem(detecterCategorie(texte));
        row << new QStandardItem(termine ? "✅ Terminé" : evaluerPriorite(date));

        if (termine) {
            for (auto *item : row) {
                QFont f = item->font(); f.setStrikeOut(true); item->setFont(f);
            }
        }
        model->appendRow(row);
    }
    mettreAJourStatistiques();
}

void TodoList::mettreAJourStatistiques()
{
    QSqlQuery q("SELECT (SELECT COUNT(*) FROM TACHES WHERE TERMINE=0), (SELECT COUNT(*) FROM TACHES WHERE TERMINE=1) FROM DUAL");
    if (q.next()) {
        ui->labelStatsTaches->setText(QString("📊 Actives: %1 | ✅ Terminées: %2").arg(q.value(0).toInt()).arg(q.value(1).toInt()));
    }
}

void TodoList::chargerFormationsPrevues()
{
    QSqlQuery query("SELECT SUJET, DATE_FORMATION FROM FORMATION WHERE STATUT = 'Prévue'");
    while (query.next()) {
        QString sujet = query.value(0).toString();
        QDate date = query.value(1).toDate();
        QStringList taches = {
            QString("📘 %1 — Préparer salle").arg(sujet),
            QString("📘 %1 — Envoyer convocations").arg(sujet),
            QString("📘 %1 — Imprimer documents").arg(sujet),
            QString("📘 %1 — Vérifier participants").arg(sujet),
            QString("📘 %1 — Créer QR code accès").arg(sujet)
        };
        for (const QString &tache : taches) {
            QSqlQuery check;
            check.prepare("SELECT COUNT(*) FROM TACHES WHERE TEXTE = :t");
            check.bindValue(":t", tache);
            check.exec(); check.next();
            if (check.value(0).toInt() == 0) {
                QSqlQuery ins;
                ins.prepare("INSERT INTO TACHES (TEXTE, DATE_LIMITE, TERMINE) VALUES (:t, TO_DATE(:d, 'DD/MM/YYYY'), 0)");
                ins.bindValue(":t", tache);
                ins.bindValue(":d", date.toString("dd/MM/yyyy"));
                ins.exec();
            }
        }
    }
}

QString TodoList::detecterCategorie(const QString &texte)
{
    QString t = texte.toLower();
    QMap<QString, QStringList> cat = {
        {"🏢 Travail", {"réunion","client","contrat","projet"}},
        {"🎓 Études", {"cours","td","examen"}},
        {"🏠 Perso", {"famille","linge","maman"}},
        {"🧘 Bien-être", {"repos","yoga","sieste"}},
        {"🛒 Courses", {"acheter","pain","pharmacie"}},
        {"📅 Admin", {"banque","facture","impôt"}},
        {"💡 Créatif", {"dessiner","musique","créatif"}},
        {"🛠 Maintenance", {"réparer","bricoler"}},
        {"🎉 Social", {"fête","amis","sortie"}}
    };
    for (auto it = cat.begin(); it != cat.end(); ++it)
        for (const QString &mot : it.value()) if (t.contains(mot)) return it.key();
    return "📌 Autre";
}

QString TodoList::evaluerPriorite(const QDate &date)
{
    int j = QDate::currentDate().daysTo(date);
    if (j < 0) return "🟠 En retard";
    if (j == 0) return "🔴 Aujourd’hui";
    if (j <= 2) return "🟡 Urgent";
    return "🟢 Basse";
}
