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

    void chargerTachesDepuisBase();
    void mettreAJourStatistiques();
    void chargerFormationsPrevues();

    QString detecterCategorie(const QString &texte);
    QString evaluerPriorite(const QDate &date);
};

#endif // TODOLIST_H
