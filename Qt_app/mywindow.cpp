#include "mywindow.h"

MyWindow::MyWindow(QWidget *parent) : QWidget(parent)
{

    m_com = new Serial(this);

    for(int i=0;i<4;++i){
        m_tabButton[i] = new QPushButton(this);
    }

    m_tabButton[0]->setText("LED3");
    m_tabButton[1]->setText("LED4");
    m_tabButton[2]->setText("LED5");
    m_tabButton[3]->setText("LED6");

    m_pushChen = new QPushButton("Running Light",this);

    m_tabButton[3]->move(100,50);
    m_tabButton[1]->move(150,100);
    m_tabButton[0]->move(100,150);
    m_tabButton[2]->move(50,100);

    m_pushChen->setGeometry(30,250,200,30);

    m_ledState[0]=m_ledState[1]=m_ledState[2]=m_ledState[3]='0';

    connect(m_tabButton[0], &QPushButton::clicked,this, &MyWindow::handleButtonLED3);
    connect(m_tabButton[1], &QPushButton::clicked,this, &MyWindow::handleButtonLED4);
    connect(m_tabButton[2], &QPushButton::clicked,this, &MyWindow::handleButtonLED5);
    connect(m_tabButton[3], &QPushButton::clicked,this, &MyWindow::handleButtonLED6);
    connect(m_pushChen, &QPushButton::clicked,this, &MyWindow::handleButtonChen);

    connect(m_com->m_serial, &QSerialPort::readyRead, this, &MyWindow::handleReadyRead);

    allLedOff();

}

MyWindow::~MyWindow()
{
    delete m_com;
    delete m_pushChen;
    for(int i=0;i<4;++i){
        delete m_tabButton[i];
    }

    m_com = Q_NULLPTR;
    m_tabButton[0] = m_tabButton[1] = m_tabButton[2] = m_tabButton[3] = m_pushChen = Q_NULLPTR;
}

void MyWindow::handleButtonLED3(void)
{
    if(m_ledState[0]=='0') m_ledState[0] = '1';
    else if(m_ledState[0]=='1') m_ledState[0] = '0';

    m_com->m_serial->write(m_ledState);
}
void MyWindow::handleButtonLED4(void)
{
    if(m_ledState[1]=='0') m_ledState[1] = '1';
    else if(m_ledState[1]=='1') m_ledState[1] = '0';

    m_com->m_serial->write(m_ledState);
}
void MyWindow::handleButtonLED5(void)
{
    if(m_ledState[2]=='0') m_ledState[2] = '1';
    else if(m_ledState[2]=='1') m_ledState[2] = '0';

    m_com->m_serial->write(m_ledState);
}
void MyWindow::handleButtonLED6(void)
{
    if(m_ledState[3]=='0') m_ledState[3] = '1';
    else if(m_ledState[3]=='1') m_ledState[3] = '0';

    m_com->m_serial->write(m_ledState);
}
void MyWindow::handleButtonChen(void)
{
    m_com->m_serial->write("2222");
}

void MyWindow::ledOn(int select)
{
    switch (select) {
    case 3:
        m_tabButton[0]->setStyleSheet("color: white; "
                                      "background-color: orange;"
                                      "border-style: solid;"
                                      "border-width:1px;"
                                      "border-radius:30px;"
                                      "border-color: orange;"
                                      "max-width:60px;"
                                      "max-height:60px;"
                                      "min-width:60px;"
                                      "min-height:60px;");
        break;
    case 4:
        m_tabButton[1]->setStyleSheet("color: white; "
                                      "background-color: green;"
                                      "border-style: solid;"
                                      "border-width:1px;"
                                      "border-radius:30px;"
                                      "border-color: green;"
                                      "max-width:60px;"
                                      "max-height:60px;"
                                      "min-width:60px;"
                                      "min-height:60px;");
        break;
    case 5:
        m_tabButton[2]->setStyleSheet("color: white; "
                                      "background-color: red;"
                                      "border-style: solid;"
                                      "border-width:1px;"
                                      "border-radius:30px;"
                                      "border-color: red;"
                                      "max-width:60px;"
                                      "max-height:60px;"
                                      "min-width:60px;"
                                      "min-height:60px;");
        break;
    case 6:
        m_tabButton[3]->setStyleSheet("color: white; "
                                      "background-color: blue;"
                                      "border-style: solid;"
                                      "border-width:1px;"
                                      "border-radius:30px;"
                                      "border-color: blue;"
                                      "max-width:60px;"
                                      "max-height:60px;"
                                      "min-width:60px;"
                                      "min-height:60px;");
        break;
    }
}
void MyWindow::ledOff(int select)
{
    switch (select) {
    case 3:
        m_tabButton[0]->setStyleSheet("color: orange; "
                                      "background-color: white;"
                                      "border-style: solid;"
                                      "border-width:1px;"
                                      "border-radius:30px;"
                                      "border-color: white;"
                                      "max-width:60px;"
                                      "max-height:60px;"
                                      "min-width:60px;"
                                      "min-height:60px;");
        break;
    case 4:
        m_tabButton[1]->setStyleSheet("color: green; "
                                      "background-color: white;"
                                      "border-style: solid;"
                                      "border-width:1px;"
                                      "border-radius:30px;"
                                      "border-color: white;"
                                      "max-width:60px;"
                                      "max-height:60px;"
                                      "min-width:60px;"
                                      "min-height:60px;");
        break;
    case 5:
        m_tabButton[2]->setStyleSheet("color: red; "
                                      "background-color: white;"
                                      "border-style: solid;"
                                      "border-width:1px;"
                                      "border-radius:30px;"
                                      "border-color: white;"
                                      "max-width:60px;"
                                      "max-height:60px;"
                                      "min-width:60px;"
                                      "min-height:60px;");
        break;
    case 6:
        m_tabButton[3]->setStyleSheet("color: blue; "
                                      "background-color: white;"
                                      "border-style: solid;"
                                      "border-width:1px;"
                                      "border-radius:30px;"
                                      "border-color: white;"
                                      "max-width:60px;"
                                      "max-height:60px;"
                                      "min-width:60px;"
                                      "min-height:60px;");
        break;
    }
}

void MyWindow::allLedOff()
{
    ledOff(3);
    ledOff(4);
    ledOff(5);
    ledOff(6);
}

void MyWindow::handleReadyRead()
{
    QByteArray _data;
    _data.append(m_com->m_serial->readAll());
    char *_read;
    _read = _data.data();

    if(_read[0]=='1')
    {
        m_ledState[0]='1';
        ledOn(3);
    }
    else
    {
        ledOff(3);
        m_ledState[0]='0';
    }

    if(_read[1]=='1')
    {
        ledOn(4);
        m_ledState[1]='1';
    }
    else
    {
        ledOff(4);
        m_ledState[1]='0';
    }

    if(_read[2]=='1')
    {
        ledOn(5);
        m_ledState[2]='1';
    }
    else
    {
        ledOff(5);
        m_ledState[2]='0';
    }

    if(_read[3]=='1')
    {
        ledOn(6);
        m_ledState[3]='1';
    }
    else
    {
        ledOff(6);
        m_ledState[3]='0';
    }
}

