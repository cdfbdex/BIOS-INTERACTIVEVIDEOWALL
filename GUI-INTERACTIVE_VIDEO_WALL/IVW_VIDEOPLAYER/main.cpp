#include <QtGui/QApplication>
#include "IVW_mainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IVW_mainWindow w;
    w.show();
    return a.exec();
}
