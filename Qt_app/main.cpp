#include "mywindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyWindow App;
    App.setGeometry(500,100,260,300);
    App.show();

    return a.exec();
}
