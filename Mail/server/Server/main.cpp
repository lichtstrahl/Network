#include <QApplication>

#include "server.h"
#include "communicator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Server w;
    Communicator c;

    QObject::connect(&c, SIGNAL(sendsMessage(const QString &, const QColor &)), &w, SLOT(print(const QString &, const QColor &)));

    w.show();
    c.launch();

    return a.exec();
}
