#include "todolist.h"
#include "ui_todolist.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFont>
#include <QBrush>

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
    ui->tableViewTaches->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewTaches->setSelectionMode(QAbstractItemView::SingleSelection);

    connect(ui->btnAjouterTache, &QPushButton::clicked, this, &TodoList::ajouterTache);
    connect(ui->btnTerminerTache, &QPushButton::clicked, this, &TodoList::terminerTache);
    connect(ui->btnSupprimerTache, &QPushButton::clicked, this, &TodoList::supprimerTache);
    connect(ui->checkBoxActives, &QCheckBox::toggled, this, &TodoList::filtrerTachesActives);

    chargerTachesDepuisFormations();
}

TodoList::~TodoList() {
    delete ui;
}

void TodoList::chargerTachesDepuisFormations()
{
    model->removeRows(0, model->rowCount());

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
            QList<QStandardItem*> ligne;
            ligne << new QStandardItem(tache);
            ligne << new QStandardItem(date.toString("dd/MM/yyyy"));
            ligne << new QStandardItem(detecterCategorie(tache));
            ligne << new QStandardItem(evaluerPriorite(date));
            model->appendRow(ligne);
        }
    }

    mettreAJourStatistiques();
}

void TodoList::ajouterTache()
{
    QString texte = ui->lineEditTache->text().trimmed();
    QDate date = ui->dateEditLimite->date();
    if (texte.isEmpty()) return;

    QList<QStandardItem*> ligne;
    ligne << new QStandardItem(texte);
    ligne << new QStandardItem(date.toString("dd/MM/yyyy"));
    ligne << new QStandardItem(detecterCategorie(texte));
    ligne << new QStandardItem(evaluerPriorite(date));

    model->appendRow(ligne);
    ui->lineEditTache->clear();
    mettreAJourStatistiques();
}

void TodoList::terminerTache()
{
    QModelIndex index = ui->tableViewTaches->currentIndex();
    if (!index.isValid()) return;

    int row = index.row();
    QStandardItem *item = model->item(row, 0); // Colonne "Tâche"
    if (item) {
        QFont font = item->font();
        font.setStrikeOut(true);  // ✅ Barrez le texte
        item->setFont(font);
        item->setForeground(QBrush(Qt::gray));
    }

    mettreAJourStatistiques();
}

void TodoList::supprimerTache()
{
    QModelIndex index = ui->tableViewTaches->currentIndex();
    if (index.isValid()) {
        model->removeRow(index.row());
        mettreAJourStatistiques();
    }
}

void TodoList::filtrerTachesActives(bool actifSeulement)
{
    for (int i = 0; i < model->rowCount(); ++i) {
        QStandardItem *item = model->item(i, 0);
        bool estBarree = item->font().strikeOut();
        ui->tableViewTaches->setRowHidden(i, actifSeulement && estBarree);
    }
}

void TodoList::mettreAJourStatistiques()
{
    int total = model->rowCount();
    int terminees = 0;
    for (int i = 0; i < total; ++i) {
        if (model->item(i, 0)->font().strikeOut()) ++terminees;
    }
    int actives = total - terminees;
    ui->labelStatsTaches->setText(QString("📊 Actives: %1 | ✅ Terminées: %2").arg(actives).arg(terminees));
}

QString TodoList::detecterCategorie(const QString &texte)
{
    QString t = texte.toLower();
    QMap<QString, QStringList> categories = {
        {"🏢 Travail", {"réunion", "client", "contrat", "projet"}},
        {"🎓 Études", {"cours", "td", "examen"}},
        {"🏠 Perso", {"famille", "linge", "maman"}},
        {"🧘 Bien-être", {"repos", "yoga", "sieste"}},
        {"🛒 Courses", {"acheter", "pain", "pharmacie"}},
        {"📅 Admin", {"banque", "facture", "impôt"}},
        {"💡 Créatif", {"dessiner", "musique", "créatif"}},
        {"🛠 Maintenance", {"réparer", "bricoler"}},
        {"🎉 Social", {"fête", "amis", "sortie"}}
    };

    for (auto it = categories.begin(); it != categories.end(); ++it)
        for (const QString &mot : it.value())
            if (t.contains(mot)) return it.key();

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
