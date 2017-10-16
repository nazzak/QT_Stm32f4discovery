#include "mywindow.h"
#include <QPushButton>
#include <algorithm>
#include <QSerialPort>

#include "serial.h"

MyWindow::MyWindow(QWidget *parent) : QWidget(parent)
{
    m_ledState[4]='\0';
    init();
    connection();
    allLedOff();
}

void MyWindow::init()
{
    m_styleSheetMap[3] = QPair<QString, QString>("color: white; background-color: orange; border-color: orange;","color: orange;");
    m_styleSheetMap[4] = QPair<QString, QString>("color: white; background-color: green; border-color: green;", "color: green;");
    m_styleSheetMap[5] = QPair<QString, QString>("color: white; background-color: red; border-color: red;", "color: red;");
    m_styleSheetMap[6] = QPair<QString, QString>("color: white; background-color: blue; border-color: blue;", "color: blue;");

    m_defaultStyleSheet.first = "border-style: solid; border-width:1px; border-radius:30px; max-width:60px; max-height:60px; min-width:60px; min-height:60px;";
    m_defaultStyleSheet.second = "background-color: white; border-color: white; border-style: solid; border-width:1px; border-radius:30px; max-width:60px; max-height:60px; min-width:60px; min-height:60px;";


    m_com = new Serial(this);

    for(int i=0;i<5;++i){
        m_tabButton[i] = new QPushButton(this);
    }

    m_tabButton[0]->setText("LED3");
    m_tabButton[1]->setText("LED4");
    m_tabButton[2]->setText("LED5");
    m_tabButton[3]->setText("LED6");
    m_tabButton[4]->setText("Running Light");

    m_tabButton[3]->move(100,50);
    m_tabButton[1]->move(150,100);
    m_tabButton[0]->move(100,150);
    m_tabButton[2]->move(50,100);
    m_tabButton[4]->setGeometry(30,250,200,40);

    m_ledState[0]=m_ledState[1]=m_ledState[2]=m_ledState[3]='0';
}

void MyWindow::connection(){
    for (int i = 0; i<5 ; ++i) {
        connect(m_tabButton[i], &QPushButton::clicked,this, &MyWindow::handleButton);
    }

    connect(m_com->m_serial, &QSerialPort::readyRead, this, &MyWindow::handleReadyRead);
}

void MyWindow::handleButton() {

    QPushButton* button = qobject_cast<QPushButton*>(sender());

    for(int i = 0; i<4; ++i){
        if( button == m_tabButton[i] )
        {
            if(m_ledState[i]=='0') m_ledState[i] = '1';
            else if(m_ledState[i]=='1') m_ledState[i] = '0';

            m_com->m_serial->write(m_ledState);
        }
    }

    if( button == m_tabButton[4] )
    {
        m_com->m_serial->write("2222");
    }
}

void MyWindow::ledOn(const int &select)
{
    m_tabButton[select - 3]->setStyleSheet(m_defaultStyleSheet.first + m_styleSheetMap[select].first);
}
void MyWindow::ledOff(const int &select)
{
    m_tabButton[select - 3]->setStyleSheet(m_defaultStyleSheet.second + m_styleSheetMap[select].second);
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
    QByteArray _data = m_com->m_serial->readAll();
    while (m_com->m_serial->waitForReadyRead(30))
            _data += m_com->m_serial->readAll();

    char *_read = _data.data();

    for (int i = 0; i < 4; ++i){
        if(_read[i]=='1')
        {
            m_ledState[i]='1';
            ledOn(i+3);
        }
        else
        {
            ledOff(i+3);
            m_ledState[i]='0';
        }
    }
}

MyWindow::~MyWindow()
{
    delete m_com;
    for(int i=0;i<5;++i){
        if(m_tabButton[i]!=nullptr)
        {
            delete m_tabButton[i];
            m_tabButton[i] = nullptr;
        }
    }

    m_com = nullptr;
}

