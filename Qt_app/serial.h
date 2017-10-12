#ifndef SERIAL_H
#define SERIAL_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QWidget>

#define MY_SERIAL_PORT "tty.usbserial-A703FUO1"

class Serial : public QWidget
{
public:

    Serial(QWidget *parent = 0);

    QSerialPort *m_serial;
    QString *m_readData;

    ~Serial();

};

#endif // SERIAL_H
