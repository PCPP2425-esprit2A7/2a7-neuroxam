#ifndef MATERIELWINDOW_H
#define MATERIELWINDOW_H

#include <QWidget>
#include "materielManager.h"
#include "ui_materielwindow.h"

// Forward declaration
namespace Ui {
class materielwindow;  // Case sensitive - must match exactly what's in your .ui file
}

class materielwindow : public QWidget
{
    Q_OBJECT

public:
    explicit materielwindow(QWidget *parent = nullptr);
    ~materielwindow();

private slots:
    void on_addButton_clicked();
    void on_loadButton_clicked();
    void on_editButton_clicked();
    void on_deleteButton_clicked();
    void on_searchButton_clicked();
    void on_resetButton_clicked();
    void on_sortButton_clicked();
    void on_pdfButton_clicked();
    void on_tab1_p1_clicked();
    void on_tab2_p1_clicked();
    void on_tab1_p2_clicked();
    void on_tab2_p2_clicked();
    void on_allouerButton_clicked();
    void on_clearButton_clicked();
    void on_optimiserButton_clicked();

private:
    Ui::materielwindow *ui;  // Must match exactly what's in your .ui file
    MaterielManager manager;
    void loadMaterielsIntoTable();
    void drawStatistics();
    int loadedMaterielId = -1;
    int countEtat(const QString& etat);
    int countDisponibilite(const QString& disponibilite);
    QStringList getCenterNames() const;
};

#endif // MATERIELWINDOW_H
