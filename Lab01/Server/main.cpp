#include "serverscreen.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ServerScreen w;
    w.show();

    return a.exec();
}
