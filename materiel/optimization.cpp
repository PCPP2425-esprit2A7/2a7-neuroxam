#include "optimization.h"
#include "ui_optimization.h"

optimization::optimization(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::optimization)
{
    ui->setupUi(this);
    setWindowTitle("Optimisation");
}

optimization::~optimization()
{
    delete ui;
}

bool isUsable(const Materiel &m) {
    return (m.getDisponibilite() == "Disponible" || m.getDisponibilite() == "En Utilisation") &&
           m.getEtat() != "Hors Service";
}


RedistributionResult optimizeTypeDistribution(const QString &type,
                                              const QJsonObject &data,
                                              std::vector<Materiel> &allMateriels,
                                              MaterielManager &manager)
{
    RedistributionResult result;
    result.type = type;

    struct CenterNeed {
        QString name;
        int current;
        int needed;
        int original;
        int gap() const { return needed - current; }
    };

    QList<CenterNeed> centers;
    QMap<QString, int> centerTypeCount;

    for (const Materiel &m : allMateriels) {
        if (m.getType().toLower() == type.toLower() && isUsable(m)) {
            centerTypeCount[m.getLocalisation()]++;
        }
    }

    for (const QString &center : data.keys()) {
        QJsonObject centerObj = data[center].toObject();
        if (!centerObj.contains(type)) continue;

        int needed = centerObj.value(type).toObject().value("quantite").toInt();
        int current = 0;
        int original = centerTypeCount.value(center, 0);

        centers.append({center, current, needed, original});
    }

    int totalAvailable = 0;
    for (const Materiel &m : allMateriels) {
        if (m.getType().toLower() == type.toLower() && isUsable(m)) {
            totalAvailable++;
        }
    }

    while (totalAvailable > 0) {
        std::sort(centers.begin(), centers.end(), [](const CenterNeed &a, const CenterNeed &b) {
            return a.gap() > b.gap();
        });

        if (centers.first().gap() <= 0)
            break;

        CenterNeed &receiver = centers.first();
        receiver.current++;
        receiver.needed--;
        totalAvailable--;

    }

    for (const Materiel &m : allMateriels) {
        if (m.getType().toLower() == type.toLower() && isUsable(m)) {
            manager.deleteMateriel(m.getId());
        }
    }

    for (const CenterNeed &c : centers) {
        for (int i = 0; i < c.current; i++) {
            Materiel newMateriel(type, "Bon", c.name, "Disponible");
            manager.addMateriel(newMateriel);

        }
        result.changes.append({c.name, c.original, c.current});
    }

    return result;
}




void optimization::setResults(const RedistributionResult &result)
{
    ui->typeLabel->setText(result.type);

    ui->changesListWidget->clear();

    for (const RedistributionChange &change : result.changes) {
        QString changeText = QString("%1, %2 -> %3")
        .arg(change.center)
            .arg(change.from)
            .arg(change.to);
        ui->changesListWidget->addItem(changeText);
    }
}


