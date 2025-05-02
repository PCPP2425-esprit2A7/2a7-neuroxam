#ifndef TMPDIALOG_H
#define TMPDIALOG_H

#include <QDialog>
#include "arduino.h"
#include "centre.h"
namespace Ui {
class TDialog;
}

class TDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TDialog(QWidget *parent = nullptr);
    ~TDialog();

private slots:
    void updateTemperature();
    void onSliderValueChanged(int value);


    void on_rp_clicked();

private:
    Ui::TDialog *ui;
    Arduino arduino;
    QTimer *timer;
};

#endif // TMPDIALOG_H
