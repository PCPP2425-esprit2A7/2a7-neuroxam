#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QMessageBox>
#include <QDate>
#include <QPrinter>
#include <QPainter>
#include <QPrintDialog>
#include <QPixmap>
#include "etudiantservice.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void loadStudents(const QString &sortBy = "");
    void onAddStudent();
    void onUpdateStudent();
    void onDeleteStudent();
    void onSortStudents(const QString &criteria);
    void onSearch();
    void onShowStats();
    void onSavePDF();
    void onSaveStudentPDF();
    void onBrowseImage();
    void onLoadStudentDetails(int studentId);
    void clearFields();
    void onOpenChatDialog();

private:
    Ui::MainWindow *ui;
    EtudiantService service;
    QStandardItemModel *model;
    QString currentPhotoPath;
    int currentStudentId;
    void setupTable();
    void setupConnections();
    void setupValidators();
};

#endif // MAINWINDOW_H
