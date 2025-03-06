#include "ajouter.h"
#include "ui_ajouter.h"

ajouter::ajouter(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ajouter)
{

    ui->setupUi(this);
    QPixmap background(":/resources/background.png");
    if (background.isNull()) {
        qDebug() << "⚠️ Erreur: Impossible de charger l'image de fond!";
    }
    QPalette palette;
    palette.setBrush(QPalette::Window, background);
    this->setPalette(palette);
}

ajouter::~ajouter()
{
    delete ui;
}
