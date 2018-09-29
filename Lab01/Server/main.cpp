#include <QApplication>

#include "./serverapplication.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ServerApplication server;

    server.start();

    return a.exec();
}
