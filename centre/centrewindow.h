#ifndef CENTREWINDOW_H
#define CENTREWINDOW_H

#include "centre.h"
#include "recommendation.h"
#include <QMainWindow>
#include <QtQuickWidgets/QQuickWidget>
#include <QGeoCoordinate>
#include <QVBoxLayout>
#include <QWidget>


namespace Ui {
class centrewindow;
}

class centrewindow : public QWidget
{
    Q_OBJECT

public:
    centrewindow(QWidget *parent = nullptr);
    ~centrewindow();

private slots:


    void on_modifier_2_clicked();

    void on_sup_clicked();

    void on_recuperer_clicked();

    void on_tri_clicked();

    void on_cherchebut_clicked();

    void on_pdf_clicked();
    void verifierNom();
    void verifierads();
    void verifierdtc();

    void on_ajoute_2_clicked();

    void on_stat_clicked();


    void onMapClicked(double latitude, double longitude);


    void on_next_clicked();

    void on_back_clicked();
    void onChatSendClicked();
    void displayRecommendations(const QVector<centre>& recommendations);

    void on_chat_clicked();
    void onExitChatClicked();


    void on_ard_clicked();

private:
    Ui::centrewindow *ui;
    centre c;
    QQuickWidget *mapWidget;
    void setupMap();
    void loadCentresToMap();
    RecommendationSystem *recommender;
    void setupChatUI();
    QVBoxLayout *chatLayout = nullptr;
};
#endif // CENTREWINDOW_H
