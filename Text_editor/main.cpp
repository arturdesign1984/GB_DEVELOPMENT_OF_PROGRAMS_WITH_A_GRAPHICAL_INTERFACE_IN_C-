#include "mainwindow.h"

#include <QApplication>
#include <QComboBox>
//#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    qDebug() << w.styleSheet();
    w.show();
    return a.exec();
}
