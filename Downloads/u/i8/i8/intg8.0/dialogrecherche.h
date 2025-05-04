#ifndef DIALOGRECHERCHE_H
#define DIALOGRECHERCHE_H
#include <QListWidgetItem>

#include <QDialog>
#include <QDate>

namespace Ui {
class DialogRecherche;
}

class DialogRecherche : public QDialog
{
    Q_OBJECT

public:
    explicit DialogRecherche(QWidget *parent = nullptr);
    ~DialogRecherche();

    QString getSujetSelectionne() const;

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void on_listWidgetSuggestions_itemClicked(QListWidgetItem *item);
    void actualiserSuggestions();

private:
    Ui::DialogRecherche *ui;
    QString sujetSelectionne;
};

#endif // DIALOGRECHERCHE_H
