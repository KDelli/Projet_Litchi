#include "OS/consoleIHM.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ConsoleIHM w;
    w.show();
    
    return a.exec();
}
