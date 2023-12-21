#include "CMainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CMainWindow w;
    w.initial();
    w.show();
    int exec = a.exec();
    w.unInitial();
    return exec;
}
