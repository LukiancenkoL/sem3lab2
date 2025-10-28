#include "mainwindow.h"

#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/Resources/icon/icon.ico"));
    mainWindow w;
    w.show();
    return a.exec();
}
