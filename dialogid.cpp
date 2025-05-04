#include "dialogid.h"
#include "ui_dialogid.h"

DialogID::DialogID(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogID)
{
    ui->setupUi(this);
    setWindowTitle("Entrez l'ID de la formation");

    // Connexion des boutons OK et Annuler
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &DialogID::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &DialogID::reject);
}

DialogID::~DialogID()
{
    delete ui;
}

int DialogID::getID() const
{
    return ui->spinBoxID->value();
}
