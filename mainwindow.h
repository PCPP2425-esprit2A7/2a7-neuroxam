#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "materielwindow.h"
#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int current_section = 0; // 0->home, 1->employe, 2->centre, 3->exam, 4->etudiant, 5->materiel, 6->formation
    void reset_button_color();


private slots:
    // Navigation slots
    void on_homeButton_clicked();
    void on_materielButton_clicked();
    void on_examButton_clicked();
    void on_centreButton_clicked();
    void on_employeButton_clicked();
    // etudiant
    void on_disconnectButton_clicked();


    void on_formationButton_clicked();

private:
    Ui::MainWindow *ui;
    materielwindow *materielWidget;

signals:
    void disconnected();
};


#endif // MAINWINDOW_H
