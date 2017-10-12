#include <QSerialPort>
#include <QSerialPortInfo>

#include "serial.h"

Serial::Serial(QWidget *parent)
{
    m_serial = new QSerialPort(this);

    m_serial->setPortName(MY_SERIAL_PORT);
    m_serial->setBaudRate(QSerialPort::Baud115200);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->open(QIODevice::ReadWrite);
}

Serial::~Serial()
{
    m_serial->close();
    delete m_serial;
    m_serial = Q_NULLPTR;
}
