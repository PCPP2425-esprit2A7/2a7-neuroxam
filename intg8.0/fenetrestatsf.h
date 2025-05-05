#ifndef FENETRESTATSF_H
#define FENETRESTATSF_H

#include <QDialog>

namespace Ui {
class FenetreStatsF;
}

class FenetreStatsF : public QDialog
{
    Q_OBJECT

public:
    explicit FenetreStatsF(QWidget *parent = nullptr);
    ~FenetreStatsF();

private:
    Ui::FenetreStatsF *ui;
    void dessinerCamembert();  // Affiche les stats
};

#endif // FENETRESTATSF_H
