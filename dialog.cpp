#include "dialog.h"
#include "ui_dialog.h"
#include <QTimer>
#include <QDebug>
#include "arduino.h"
#include "centre.h"
#include <QMessageBox>
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    // Initialize Arduino
    if(arduino.connect_arduino() == 0) {
        qDebug() << "Arduino connected successfully";
    } else {
        qDebug() << "Failed to connect to Arduino";
    }

    // Setup timer for temperature updates
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Dialog::updateTemperature);
    timer->start(2000); // Update every 2 seconds

    // Connect slider signal
    connect(ui->slider, &QSlider::valueChanged, this, &Dialog::onSliderValueChanged);

    // Set slider range (0-255 for PWM)
    ui->slider->setRange(0, 255);
    ui->slider->setValue(0);
}

Dialog::~Dialog()
{
    arduino.close_arduino();
    delete ui;
}

void Dialog::updateTemperature()
{
    if (arduino.getserial()->isReadable()) {
        QByteArray data = arduino.read_from_arduino();
        QString strData(data);

        if (strData.startsWith("TEMP:")) {
            QString tempValue = strData.mid(5).trimmed();
            ui->tmp->setText(tempValue + " °C");




            float maxTemp = ui->ctmp->text().toFloat(); // ✅ Correction ici
            float currentTemp = tempValue.toFloat();    // ✅ Correction ici

            qDebug() << "Temp Actuelle =" << currentTemp << ", MaxTemp Centre =" << maxTemp;

            if (currentTemp > maxTemp) {
                arduino.write_to_arduino(QString("START"));
                qDebug() << "Envoyé START car Temp actuelle > MaxTemp";
            } else {
                arduino.write_to_arduino(QString("STOP"));
                qDebug() << "Envoyé STOP car Temp actuelle <= MaxTemp";
            }
        }
    }
}


void Dialog::onSliderValueChanged(int value)
{
    ui->vitesse->setText(QString::number(value));

    // Send speed command to Arduino
    if(value == 0) {
        arduino.write_to_arduino(QString("STOP"));
    } else {
        // Convert slider value to PWM command
        QString cmd = "SPEED:" + QString::number(value);
        arduino.write_to_arduino(cmd);
    }
}



void Dialog::on_rp_clicked()
{
    QString idText = ui->id->text();

    bool ok;
    int id = idText.toInt(&ok);

    if (!ok || id <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide.");
        return;
    }
    if (!centre::exists(id)) {
        QMessageBox::warning(this, "Erreur", "Centre non trouvé.");
        return;
    }

    centre c = centre::read(id);
    ui->name->setText(c.getNom());
    ui->ctmp->setText(QString::number(c.gettemp()));
}

