#include "mainwindow.h"

#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Diego Fabián Ledesma Motta - 1928161 - Proyecto 1");
    w.show();
    return a.exec();
}
