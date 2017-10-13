#ifndef SERIAL_H
#define SERIAL_H

#include <QWidget>

/*
* Has to be changed
*/
#define MY_SERIAL_PORT "tty.usbserial-A703FUO1"

class Serial : public QWidget
{
public:

    Serial(QWidget *parent = nullptr);

    QSerialPort *m_serial;

    ~Serial();

};

#endif // SERIAL_H
