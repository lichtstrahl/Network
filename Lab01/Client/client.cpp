#include <QDebug>
#include "client.h"

const int port = 6006;

Client::Client()
{
    textSocket.bind(QHostAddress::Any, port);
    connect(&textSocket, SIGNAL(readyRead()), this, SLOT(onDataRead()));
}

void Client::onDataRead()
{
    qDebug() << "Client data read";
}
