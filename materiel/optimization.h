#ifndef OPTIMIZATION_H
#define OPTIMIZATION_H

#include <QDialog>
#include "materielManager.h"
#include <QJsonObject>

namespace Ui {
class optimization;
}


struct RedistributionChange {
    QString center;
    int from;
    int to;
};

struct RedistributionResult {
    QString type;
    QList<RedistributionChange> changes;
};

class optimization : public QDialog
{
    Q_OBJECT

public:
    explicit optimization(QWidget *parent = nullptr);
    ~optimization();
    void setResults(const RedistributionResult &result);

private:
    Ui::optimization *ui;
};


RedistributionResult optimizeTypeDistribution(const QString &type,
                                              const QJsonObject &data,
                                              std::vector<Materiel> &allMateriels,
                                              MaterielManager &manager);

bool isUsable(const Materiel &m);


#endif // OPTIMIZATION_H
