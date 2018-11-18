#include <QTcpSocket>
#include <QHostAddress>
#include <QDataStream>
#include <QDebug>

#include "communicator.h"

Communicator::Communicator(QObject *parent) : QObject(parent), socket(new QTcpSocket())
{
}

Communicator::~Communicator()
{
    socket->disconnectFromHost();
    delete socket;
}

void Communicator::launch()
{
    connect(socket, SIGNAL(readyRead()), SLOT(serverResponse()));

    socket->connectToHost(QHostAddress(hostname), port);
}

void Communicator::serverResponse()
{
    QByteArray data = socket->readAll();
    QDataStream in(data);

    QString message;
    in >> message;
    qDebug() << message;
}
