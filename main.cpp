#include "mainwindow.h"
#include <QApplication>
#include <cstdlib>
#include <ctime>

int main(int argc, char *argv[])
{
    std::srand(std::time(NULL));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
