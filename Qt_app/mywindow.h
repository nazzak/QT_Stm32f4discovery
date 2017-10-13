#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMap>
#include <QPair>


class QPushButton;
class Serial;

class MyWindow : public QWidget
{
    Q_OBJECT

public:
    MyWindow(QWidget *parent = 0);
    QPushButton *m_tabButton [5];
    QPair<QString, QString> m_defaultStyleSheet;
    QMap<int, QPair<QString, QString>> m_styleSheetMap;
    ~MyWindow();

private slots:
    void handleButton();
    void handleReadyRead();

private:

    char m_ledState[4];
    Serial *m_com;

    void ledOn(const int &select);
    void ledOff(const int &select);
    void allLedOff();

    void init();
    void connection();


};

#endif // MAINWINDOW_H
