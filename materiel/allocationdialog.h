#ifndef ALLOCATIONDIALOG_H
#define ALLOCATIONDIALOG_H

#include <QDialog>
#include <QMap>
#include <QLineEdit>
#include <QComboBox>
#include <QJsonObject>
#include "materielmanager.h"

namespace Ui {
class allocationdialog;
}

class allocationdialog : public QDialog
{
    Q_OBJECT

public:
    explicit allocationdialog(MaterielManager &m, const QStringList &centers, QWidget *parent = nullptr);
    ~allocationdialog();
    static QJsonObject loadJson();


signals:
    void allocationConfirmed();

private slots:
    void on_centerComboBox_currentTextChanged(const QString &center);
    void on_confirmerButton_clicked();
    void on_prevButton_clicked();
    void on_nextButton_clicked();

    void on_resetButton_clicked();

private:
    Ui::allocationdialog *ui;
    MaterielManager &manager;
    QString currentCenter;

    QMap<QString, QLineEdit*> equipmentInputs;
    QMap<QString, QComboBox*> equipmentEtats;
    QMap<QString, QComboBox*> equipmentDisponibilites;

    void loadInputsForCenter(const QString &center);
    void saveInputsForCenter(const QString &center);
    void saveJson(const QJsonObject &obj);
    void autoFillMissingEquipment(const QString &center,
                                  const QMap<QString, int> &requested,
                                  const QMap<QString, QString> &etats,
                                  const QMap<QString, QString> &dispos,
                                  bool ignoreReparation,
                                  bool ignoreIndisponible);
};

#endif // ALLOCATIONDIALOG_H
