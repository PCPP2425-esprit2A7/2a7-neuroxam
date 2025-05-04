#ifndef TODOLIST_H
#define TODOLIST_H

#include <QDialog>
#include <QStandardItemModel>
#include <QDate>

namespace Ui {
class TodoList;
}

class TodoList : public QDialog
{
    Q_OBJECT

public:
    explicit TodoList(QWidget *parent = nullptr);
    ~TodoList();

private slots:
    void ajouterTache();                    // ➕ Ajout d'une tâche manuelle
    void terminerTache();                  // ✔️ Marquer une tâche comme terminée
    void supprimerTache();                 // 🗑️ Supprimer une tâche
    void filtrerTachesActives(bool actif); // 🔍 Filtrer les tâches terminées

private:
    void chargerTachesDepuisFormations();  // 📥 Charger depuis FORMATION
    void mettreAJourStatistiques();        // 📊 Statistiques affichées
    QString detecterCategorie(const QString &texte);
    QString evaluerPriorite(const QDate &date);

    Ui::TodoList *ui;
    QStandardItemModel *model;
};

#endif // TODOLIST_H
