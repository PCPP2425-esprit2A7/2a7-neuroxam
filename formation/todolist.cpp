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
    this->setWindowTitle("📝 Liste des Tâches (automatique)");
    this->resize(700, 500);

    model->setHorizontalHeaderLabels({"Tâche", "Date limite", "Catégorie", "Priorité"});
    ui->tableViewTaches->setModel(model);

    // Désactiver les boutons inutiles
    ui->btnAjouterTache->setEnabled(false);
    ui->btnTerminerTache->setEnabled(false);
    ui->btnSupprimerTache->setEnabled(false);
    ui->checkBoxActives->setEnabled(false);

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

void TodoList::mettreAJourStatistiques()
{
    int total = model->rowCount();
    ui->labelStatsTaches->setText(QString("📊 Tâches simulées (basées sur FORMATION) : %1").arg(total));
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
