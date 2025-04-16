#include "allocationdialog.h"
#include "ui_allocationdialog.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QMessageBox>
#include "materiel.h"

allocationdialog::allocationdialog(MaterielManager &m, const QStringList &centers, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::allocationdialog)
    , manager(m)
{
    ui->setupUi(this);
    setWindowTitle("Allocation de matériels");

    QStringList etatOptions = {"Excellent", "Bon", "Mauvais", "Hors Service"};
    QStringList dispoOptions = {"Disponible", "En Utilisation", "En Répartation", "Indisponible"};

    equipmentInputs = {
        {"Ordinateur", ui->ordinateurLineEdit},
        {"Casque Audio", ui->casqueLineEdit},
        {"Camera", ui->cameraLineEdit},
        {"Scanner", ui->scannerLineEdit},
        {"Imprimante", ui->imprimanteLineEdit},
        {"Clavier", ui->clavierLineEdit},
        {"Souris", ui->sourisLineEdit},
        {"Ecran", ui->ecranLineEdit},
        {"Routeur", ui->routeurLineEdit},
        {"Climatiseur", ui->climatiseurLineEdit}
    };

    equipmentEtats = {
        {"Ordinateur", ui->ordinateurEtat},
        {"Casque Audio", ui->casqueaudioEtat},
        {"Camera", ui->cameraEtat},
        {"Scanner", ui->scannerEtat},
        {"Imprimante", ui->imprimanteEtat},
        {"Clavier", ui->clavierEtat},
        {"Souris", ui->sourisEtat},
        {"Ecran", ui->ecranEtat},
        {"Routeur", ui->routeurEtat},
        {"Climatiseur", ui->climatiseurEtat}
    };

    equipmentDisponibilites = {
        {"Ordinateur", ui->ordinateurDispo},
        {"Casque Audio", ui->casqueaudioDispo},
        {"Camera", ui->cameraDispo},
        {"Scanner", ui->scannerDispo},
        {"Imprimante", ui->imprimanteDispo},
        {"Clavier", ui->clavierDispo},
        {"Souris", ui->sourisDispo},
        {"Ecran", ui->ecranDispo},
        {"Routeur", ui->routeurDispo},
        {"Climatiseur", ui->climatiseurDispo}
    };

    for (const QString &key : equipmentEtats.keys()) {
        equipmentEtats[key]->addItems(etatOptions);
        equipmentDisponibilites[key]->addItems(dispoOptions);
    }

    ui->centerComboBox->addItems(centers);
    currentCenter = ui->centerComboBox->currentText();
    loadInputsForCenter(currentCenter);
}

allocationdialog::~allocationdialog()
{
    delete ui;
}

void allocationdialog::on_centerComboBox_currentTextChanged(const QString &center)
{
    saveInputsForCenter(currentCenter);
    currentCenter = center;
    loadInputsForCenter(center);
}

QJsonObject allocationdialog::loadJson()
{
    QFile file("allocation.json");
    if (!file.open(QIODevice::ReadOnly)) return QJsonObject();

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    return doc.object();
}

void allocationdialog::saveJson(const QJsonObject &obj)
{
    QFile file("allocation.json");
    if (!file.open(QIODevice::WriteOnly)) return;

    QJsonDocument doc(obj);
    file.write(doc.toJson());
}

void allocationdialog::loadInputsForCenter(const QString &center)
{
    QJsonObject data = loadJson();
    QJsonObject centerObj = data[center].toObject();

    for (const QString &key : equipmentInputs.keys()) {
        QJsonObject eqObj = centerObj.value(key).toObject();

        int val = eqObj.value("quantite").toInt();
        QString etat = eqObj.value("etat").toString("Excellent");
        QString dispo = eqObj.value("disponibilite").toString("Disponible");

        equipmentInputs[key]->setText(val == 0 ? "" : QString::number(val));
        equipmentEtats[key]->setCurrentText(etat);
        equipmentDisponibilites[key]->setCurrentText(dispo);
    }
}

void allocationdialog::saveInputsForCenter(const QString &center)
{
    QJsonObject data = loadJson();
    QJsonObject centerObj;

    for (const QString &key : equipmentInputs.keys()) {
        bool ok = false;
        int val = equipmentInputs[key]->text().toInt(&ok);
        QString etat = equipmentEtats[key]->currentText();
        QString dispo = equipmentDisponibilites[key]->currentText();

        QJsonObject eqObj;
        if (ok) eqObj["quantite"] = val;
        eqObj["etat"] = etat;
        eqObj["disponibilite"] = dispo;

        centerObj[key] = eqObj;
    }

    data[center] = centerObj;
    saveJson(data);
}


void allocationdialog::autoFillMissingEquipment(const QString &center,
                                                const QMap<QString, int> &requested,
                                                const QMap<QString, QString> &etats,
                                                const QMap<QString, QString> &dispos,
                                                bool ignoreReparation,
                                                bool ignoreIndisponible)
{
    QMap<QString, int> existing;
    std::vector<Materiel> allMateriels = manager.getAllMateriels();

    for (const Materiel &m : allMateriels) {
        if (m.getLocalisation() != center)
            continue;

        if (ignoreReparation && m.getDisponibilite() == "En Réparation")
            continue;

        if (ignoreIndisponible && m.getDisponibilite() == "Indisponible")
            continue;

        existing[m.getType().toLower()] += 1;
    }

    for (const QString &type : requested.keys()) {
        int needed = requested[type];
        int alreadyThere = existing.value(type.toLower(), 0);
        int missing = needed - alreadyThere;

        QString etat = etats.value(type, "Excellent");
        QString dispo = dispos.value(type, "Disponible");

        for (int i = 0; i < missing; ++i) {
            Materiel m(type, etat, center, dispo);
            manager.addMateriel(m);
        }
    }
}


void allocationdialog::on_confirmerButton_clicked()
{
    saveInputsForCenter(currentCenter);

    QJsonObject data = loadJson();
    QJsonObject centerObj = data[currentCenter].toObject();

    QMap<QString, int> requested;
    QMap<QString, QString> etats;
    QMap<QString, QString> dispos;

    for (const QString &key : equipmentInputs.keys()) {
        QString inputText = equipmentInputs[key]->text().trimmed();

        if (inputText.isEmpty()) continue;  // skip if nothing entered

        bool ok = false;
        int value = inputText.toInt(&ok);

        if (!ok || value < 0) {
            QMessageBox::warning(this, "Entrée invalide", QString("Veuillez entrer un entier positif pour \"%1\".").arg(key));
            return;
        }

        requested[key] = value;

        etats[key] = equipmentEtats.contains(key) ? equipmentEtats[key]->currentText() : "Excellent";
        dispos[key] = equipmentDisponibilites.contains(key) ? equipmentDisponibilites[key]->currentText() : "Disponible";
    }



    bool ignoreReparation = ui->checkReparation->isChecked();
    bool ignoreIndisponible = ui->checkIndisponible->isChecked();

    autoFillMissingEquipment(currentCenter, requested, etats, dispos, ignoreReparation, ignoreIndisponible);

    saveJson(data);
    emit allocationConfirmed();
    accept();
}


void allocationdialog::on_prevButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void allocationdialog::on_nextButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void allocationdialog::on_resetButton_clicked()
{
    QFile file("allocation.json");
    if (file.exists()) {
        file.remove();
    }

    for (auto *spin : equipmentInputs.values()) {
        spin->setText("");
    }

    for (auto *etatBox : equipmentEtats.values()) {
        etatBox->setCurrentText("Excellent");
    }

    for (auto *dispoBox : equipmentDisponibilites.values()) {
        dispoBox->setCurrentText("Disponible");
    }

    QMessageBox::information(this, "Réinitialisé", "Les données ont été réinitialisées.");
}

