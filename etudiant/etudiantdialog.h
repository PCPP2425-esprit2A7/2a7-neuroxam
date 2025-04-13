#ifndef ETUDIANTDIALOG_H
#define ETUDIANTDIALOG_H

#include <QDialog>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QDate>
#include <QChartView>
#include <QPieSeries>
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class EtudiantDialog; }
QT_END_NAMESPACE

class EtudiantDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EtudiantDialog(QWidget *parent = nullptr);
    ~EtudiantDialog();

private slots:
    void on_addButton_clicked();
    void on_updateButton_clicked();
    void on_deleteButton_clicked();
    void on_clearButton_clicked();
    void on_searchButton_clicked();
    void on_sortButton_clicked();
    void on_browseButton_clicked();
    void on_studentTableView_clicked(const QModelIndex &index);
    void on_refreshStatsButton_clicked();
    void on_exportPdfButton_clicked();

private:
    Ui::EtudiantDialog *ui;
    QSqlTableModel *model;
    QChart *genderChart;
    QChartView *chartView;

    void loadStudents();
    void clearInputs();
    void loadStudentToForm(int studentId);
    void setupChart();
    void updateGenderStats();
    bool validateInputs();
};

#endif // ETUDIANTDIALOG_H 