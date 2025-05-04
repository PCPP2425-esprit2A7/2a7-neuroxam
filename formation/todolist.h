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

private:
    Ui::TodoList *ui;
    QStandardItemModel *model;

    void chargerTachesDepuisFormations();           // 🔄 Nouvelle méthode basée sur FORMATION
    void mettreAJourStatistiques();                 // 📊 Affiche le total des tâches simulées
    QString detecterCategorie(const QString &texte); // 🧠 Classe les tâches automatiquement
    QString evaluerPriorite(const QDate &date);      // 🔥 Urgence des tâches en fonction de la date
};

#endif // TODOLIST_H
