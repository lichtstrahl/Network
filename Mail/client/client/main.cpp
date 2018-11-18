#include <QApplication>

#include "mailclient.h"
#include "communicator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MailClient w;
    Communicator c;

    c.launch();
    w.show();

    return a.exec();
}
