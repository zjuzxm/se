#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <iostream>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
     QApplication app(argc, argv);

    MainWindow mainWin;
    mainWin.resize(650, 600);

    mainWin.show();
    return app.exec();
}
