#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MAIN_WINDOW.show();
    MAIN_WINDOW.init();
    return a.exec();
}
