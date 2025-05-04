#ifndef FENETRESIGNATURES_H
#define FENETRESIGNATURES_H

#include <QDialog>

namespace Ui {
class FenetreSignatures;
}

class FenetreSignatures : public QDialog
{
    Q_OBJECT

public:
    explicit FenetreSignatures(QWidget *parent = nullptr);
    ~FenetreSignatures();

    void actualiserTable();  // ✅ doit être public

private:
    Ui::FenetreSignatures *ui;
};

#endif // FENETRESIGNATURES_H
