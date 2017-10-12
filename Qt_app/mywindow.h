#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>

#include "serial.h"

class MyWindow : public QWidget
{
    Q_OBJECT

public:
    MyWindow(QWidget *parent = 0);
    QPushButton *m_tabButton [4];
    QPushButton *m_pushChen;

    Serial *m_com;

    char m_ledState[4];

    ~MyWindow();

private slots:
    void handleButtonLED3(void);
    void handleButtonLED4(void);
    void handleButtonLED5(void);
    void handleButtonLED6(void);
    void handleButtonChen(void);

    void handleReadyRead();

private:
    void ledOn(int);
    void ledOff(int);
    void allLedOff(void);


};

#endif // MAINWINDOW_H
