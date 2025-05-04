#ifndef ARDUINO_H
#define ARDUINO_H

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>

class Arduino
{
public:
    Arduino();
    int connect_arduino(); // Connecter le PC à Arduino
    int close_arduino(); // Fermer la connexion
    void write_to_arduino(QByteArray); // Envoyer des données vers Arduino
    QByteArray read_from_arduino(); // Recevoir des données de la carte Arduino
    QSerialPort* getserial(); // Accesseur
    QString getarduino_port_name();
    void write_to_arduino(const QString &command);

    QByteArray get_data() const; // Ajouter un accesseur pour récupérer "data"

private:
    QSerialPort *serial;
    static const quint16 arduino_uno_vendor_id = 9025;
    static const quint16 arduino_uno_producy_id = 67;
    QString arduino_port_name;
    bool arduino_is_available;
    QByteArray data; // Contient les données lues à partir d'Arduino
};

#endif // ARDUINO_H
