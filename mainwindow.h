#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "materielManager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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

private:
    Ui::MainWindow *ui;
    MaterielManager manager;
    void loadMaterielsIntoTable();
    void drawStatistics();
    int loadedMaterielId = -1;
    int countEtat(const QString& etat);
    int countDisponibilite(const QString& disponibilite);
    QStringList getCenterNames() const;

};

#endif // MAINWINDOW_H
