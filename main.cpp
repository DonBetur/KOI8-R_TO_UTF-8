#include "mainwindow.h"
#include <QTextDecoder>
#include <QApplication>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QFileDialog>
#include <QDesktopServices>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowFlags(w.windowFlags()&~Qt::WindowMaximizeButtonHint);
    w.show();
    //w.show();
    return a.exec();
}
