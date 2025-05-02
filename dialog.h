#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "arduino.h"
#include "centre.h"
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void updateTemperature();
    void onSliderValueChanged(int value);


    void on_rp_clicked();

private:
    Ui::Dialog *ui;
    Arduino arduino;
    QTimer *timer;
};

#endif // DIALOG_H
