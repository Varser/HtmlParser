#include "mainwindow.h"
#include <QApplication>
#include <QThread>
#include <objectsthree.h>
int main(int argc, char *argv[])
{
    ObjectsThree three(QString("https://www.google.com.ua/search?sourceid=chrome-psyapi2&ion=1&espv=2&ie=UTF-8&client=ubuntu&q=QString&oq=QString&aqs=chrome..69i57j0l5.5911j0j4"), QString("QString"));
    three.start();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
