#ifndef SERIAL_H
#define SERIAL_H

#include <QWidget>

/*
 * MY_SERIAL_PORT need to be updated
 */
#define MY_SERIAL_PORT "tty.usbserial-A703FUO1"

class QSerialPort;

class Serial : public QWidget
{
public:
    
    Serial(QWidget *parent = nullptr);
    ~Serial();
    
    QSerialPort *m_serial;
};

#endif // SERIAL_H
